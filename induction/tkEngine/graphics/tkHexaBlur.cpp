/*!
 *@brief	�Z�p�`�u���[�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkHexaBlur.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

namespace tkEngine {
	void CHexaBlur::Init(CShaderResourceView& srcTexture, bool isScaleup)
	{
		D3D11_TEXTURE2D_DESC texDesc;
		m_srcTexture = &srcTexture;
		m_srcTexture->GetTextureDesc(texDesc);

		for (auto& rt : m_renderTarget) {
			DXGI_SAMPLE_DESC multiSampleDesc;
			multiSampleDesc.Count = 1;
			multiSampleDesc.Quality = 0;

			rt.Create(
				isScaleup == true ? texDesc.Width * 2 : texDesc.Width,
				isScaleup == true ? texDesc.Height * 2 : texDesc.Height,
				1,
				1,
				texDesc.Format,
				DXGI_FORMAT_UNKNOWN,
				multiSampleDesc
			);
		}
		//�V�F�[�_�[���������B
		m_vs.Load("shader/hexaBlur.fx", "VSMain", CShader::EnType::VS);
		m_psVerticalDiagonalBlur.Load("shader/hexaBlur.fx", "PSVerticalDiagonalBlur", CShader::EnType::PS);
		m_psCombineVerticalDiagonalBlur.Load("shader/hexaBlur.fx", "PSCombineVerticalDiagonalBlur", CShader::EnType::PS);
		m_psRhomboidBlur.Load("shader/hexaBlur.fx", "PSRhomboidBlur", CShader::EnType::PS);
		//�萔�o�b�t�@���������B
		m_cb.Create(nullptr, sizeof(SCBParam));
	}
	void CHexaBlur::Execute(CRenderContext& rc, std::function<void(CRenderContext& rc, EnRenderPass)> onPreDraw)
	{
		if (m_srcTexture == nullptr) {
			//�\�[�X�e�N�X�`�����w�肳��Ă��Ȃ����S���@�B
			return;
		}
		CGraphicsEngine& ge = Engine().GetGraphicsEngine();
		ge.BeginGPUEvent(L"CHexaBlur::Execute");

		D3D11_TEXTURE2D_DESC texDesc;
		m_srcTexture->GetTextureDesc(texDesc);
		SCBParam cbParam;
		cbParam.texSize.x = texDesc.Width;
		cbParam.texSize.y = texDesc.Height;
		cbParam.radius = m_radius;	
		//VRAM��̒萔�o�b�t�@���X�V�B
		rc.UpdateSubresource(m_cb, &cbParam);
		//b0���W�X�^�ɒ萔�o�b�t�@�̃A�h���X��ݒ�B
		rc.PSSetConstantBuffer(0, m_cb);

		//�|�X�g�G�t�F�N�g�̑S��ʕ`��̋@�\���g�������̂ŁA�|�X�g�G�t�F�N�g��
		//�C���X�^���X���擾����B
		auto& postEffect = GraphicsEngine().GetPostEffect();

		//�����_�����O�X�e�[�g�ƃ����_�����O�^�[�Q�b�g��ޔ�������B
		rc.PushRenderState();
		rc.PushRenderTargets();

		rc.PSSetSampler(0, *CPresetSamplerState::clamp_clamp_clamp_linear);
		rc.OMSetBlendState(AlphaBlendState::disable);
		//�����A�΂߃u���[
		{
			CRenderTarget* rts[] = {
				&m_renderTarget[enRenderTarget_VerticalBlur],
				&m_renderTarget[enRenderTarget_DiagonalBlur]
			};
			CChangeRenderTarget chgRt(rc, 2, rts);
			rc.PSSetShaderResource(0, *m_srcTexture);
			rc.VSSetShader(m_vs);
			rc.PSSetShader(m_psVerticalDiagonalBlur);
			float color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			rc.ClearRenderTargetView(0, color);
			rc.ClearRenderTargetView(1, color);
			if (onPreDraw != nullptr) {
				onPreDraw(rc, enRenderPass_VerticalDiagonalBlur);
			}
			postEffect.DrawFullScreenQuad(rc);
		}
		//�����u���[�Ǝ΂߃u���[����������B
	/*	{
			CChangeRenderTarget chgRt(rc, m_renderTarget[enRenderTarget_VerticalDiagonalBlur]);
			rc.PSSetShaderResource(0, m_renderTarget[enRenderTarget_VerticalBlur].GetRenderTargetSRV());
			rc.PSSetShaderResource(1, m_renderTarget[enRenderTarget_DiagonalBlur].GetRenderTargetSRV());
			rc.VSSetShader(m_vs);
			rc.PSSetShader(m_psCombineVerticalDiagonalBlur);
			if (onPreDraw != nullptr) {
				onPreDraw(rc, enRenderPass_CombineVerticalDiagonalBlur);
			}
			postEffect.DrawFullScreenQuad(rc);
		}*/
		//�Z�p�`�u���[���쐬����B
		{
			CChangeRenderTarget chgRt(rc, m_renderTarget[enRenderTarget_RhomboidBlur]);
			rc.PSSetShaderResource(0, m_renderTarget[enRenderTarget_VerticalBlur].GetRenderTargetSRV());
			rc.PSSetShaderResource(1, m_renderTarget[enRenderTarget_DiagonalBlur].GetRenderTargetSRV());
			rc.VSSetShader(m_vs);
			rc.PSSetShader(m_psRhomboidBlur);
			if (onPreDraw != nullptr) {
				onPreDraw(rc, enRenderPass_RhomboidBlur);
			}
			postEffect.DrawFullScreenQuad(rc);
		}
		//�����_�����O�X�e�[�g�ƃ����_�����O�^�[�Q�b�g��߂��B
		rc.PopRenderState(true);
		rc.PopRenderTargets(true);

		ge.EndGPUEvent();
	}
}