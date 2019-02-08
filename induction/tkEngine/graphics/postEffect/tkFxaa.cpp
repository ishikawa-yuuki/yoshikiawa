/*!
 *@brief	FXAA
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
namespace tkEngine{
	CFxaa::CFxaa()
	{
	}
	CFxaa::~CFxaa()
	{
		Release();
	}
	void CFxaa::Release()
	{
		m_samplerState.Release();
	}
	void CFxaa::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.aaConfig.isEnable;
		m_vsShader.Load("shader/fxaa.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("shader/fxaa.fx", "PSMain", CShader::EnType::PS);
		//�T���v�����쐬�B
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);
	}
	void CFxaa::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		
		BeginGPUEvent(L"enRenderStep_AntiAlias");

		//�����_�����O�X�e�[�g��ޔ�������B
		rc.PushRenderState();

		//�����_�����O�X�e�[�g��FXAA�p�ɐݒ肷��悤�ɂ���B
		rc.OMSetDepthStencilState(DepthStencilState::disable);
		//���݂̃����_�����O�^�[�Q�b�g���擾�B
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		

		rc.OMSetBlendState(AlphaBlendState::disable);
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		postEffect->ToggleFinalRenderTarget();

		CChangeRenderTarget chgRt(rc, postEffect->GetFinalRenderTarget());
		rc.PSSetSampler(0, m_samplerState);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		
		postEffect->DrawFullScreenQuad(rc);

		rc.PSUnsetShaderResource(0);

		//�����_�����O�X�e�[�g��߂��B
		rc.PopRenderState(true);

		EndGPUEvent();
	}
}
