/*!
 * @brief	�f�B�U�����O�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDithering.h"
#include "tkEngine/graphics/tkPresetRenderState.h"


namespace tkEngine{
	CDithering::CDithering()
	{
	}
	CDithering::~CDithering()
	{
	}
	void CDithering::Release()
	{
	}
	void CDithering::Init(const SGraphicsConfig& config)
	{
		Release();
		m_isEnable = config.ditheringConfig.isEnable;
		m_vsShader.Load("shader/dithering.fx", "VSMain", CShader::EnType::VS);
		m_psShader.Load("shader/dithering.fx", "PSMain", CShader::EnType::PS);
		//�T���v�����쐬�B
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		m_samplerState.Create(desc);
	}
	void CDithering::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_Dithering");

		//�����_�����O�X�e�[�g���f�B�U�悤�ɂ���B
		rc.OMSetDepthStencilState(DepthStencilState::disable);
		//���݂̃����_�����O�^�[�Q�b�g���擾�B
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B
		postEffect->ToggleFinalRenderTarget();
		CRenderTarget* renderTargets[] = {
			&postEffect->GetFinalRenderTarget()
		};
		rc.OMSetBlendState(AlphaBlendState::disable);
		rc.PSSetSampler(0, m_samplerState);
		rc.OMSetRenderTargets(1, renderTargets);
		rc.PSSetShaderResource(0, rt.GetRenderTargetSRV());
		rc.PSSetShader(m_psShader);
		rc.VSSetShader(m_vsShader);
		postEffect->DrawFullScreenQuad(rc);
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender);
		rc.PSUnsetShaderResource(0);
		EndGPUEvent();
	}
}