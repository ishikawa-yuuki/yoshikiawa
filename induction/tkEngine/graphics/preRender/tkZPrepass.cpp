/*!
 *@brief	ZPrepass
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkZPrepass.h"
#include "tkEngine/graphics/tkCamera.h"

namespace tkEngine{
	namespace {
		static const int RESERVE_SKIN_MODEL_LIST = 512;
	}
	CZPrepass::CZPrepass()
	{
		m_skinModels.reserve(RESERVE_SKIN_MODEL_LIST);
	}
	CZPrepass::~CZPrepass()
	{
	}
	void CZPrepass::Init()
	{
		CGraphicsEngine& ge = GraphicsEngine();
		//�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g�̍쐬�B
		
		m_depthBuffer.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,	//Z�o�b�t�@�͍��Ȃ��B
			ge.GetMainRenderTargetMSAADesc()
		);
		//Z�o�b�t�@�̓��C�������_�����O�^�[�Q�b�g�̂��̂��g�p����B
		m_depthBuffer.SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);
	}
	void CZPrepass::Render(CRenderContext& rc) 
	{
		BeginGPUEvent(L"enRenderStep_ZPrepass");
		rc.PSUnsetShaderResource(8);
		rc.SetRenderStep(enRenderStep_ZPrepass);
		//���݂̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v����B
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//�����_�����O�^�[�Q�b�g��ύX����B
		CRenderTarget* renderTargets[] = {
			&m_depthBuffer
		};
		rc.OMSetRenderTargets(1, renderTargets);
		float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
		rc.ClearRenderTargetView(0, ClearColor);

		for (auto skinModel : m_skinModels) {
			skinModel->Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}
		m_skinModels.clear();
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		EndGPUEvent();
		//MSAA���]���u�B
		m_depthBuffer.ResovleMSAATexture(rc);

		rc.PSSetShaderResource(8, m_depthBuffer.GetRenderTargetSRV());
	}
}