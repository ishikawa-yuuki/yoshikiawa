/*!
 * @brief	�����_�����O�R���e�L�X�g�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkRenderContext.h"
#include "tkEngine/graphics/tkRenderTarget.h"

namespace tkEngine{
	void CRenderContext::Init(ID3D11DeviceContext* pD3DDeviceContext, ID3D11DeviceContext* pD3DDeferredDeviceContext)
	{
		TK_ASSERT(pD3DDeviceContext != nullptr, "pD3DDeviceContext��NULL�ł��B�쐬���Ă���Ă�łˁB");
		m_pD3DImmidiateDeviceContext = pD3DDeviceContext;
		if (pD3DDeferredDeviceContext != nullptr) {
			//�f�B�t�@�[�h�R���e�L�X�g���w�肳��Ă���ꍇ�͂�������g���B
			m_pD3DDeviceContext = pD3DDeferredDeviceContext;
		}
		else {
			m_pD3DDeviceContext = m_pD3DImmidiateDeviceContext;
		}
	}
	void CRenderContext::OMSetRenderTargets(unsigned int NumViews, CRenderTarget* renderTarget[])
	{
		TK_ASSERT(NumViews <= MRT_MAX, "NumViews is invalid");
		
		ZeroMemory(m_renderTargetViews, sizeof(m_renderTargetViews));
		

		ID3D11RenderTargetView* renderTargetViews[MRT_MAX] = { nullptr };
		ID3D11DepthStencilView*	depthStencilView = nullptr;

		if (renderTarget != nullptr) {
			memcpy(m_renderTargetViews, renderTarget, sizeof(CRenderTarget*) * NumViews);
			if (m_renderTargetViews[0] != nullptr) {
				depthStencilView = m_renderTargetViews[0]->GetDepthStencilView();
				for (unsigned int i = 0; i < NumViews; i++) {
					renderTargetViews[i] = m_renderTargetViews[i]->GetRenderTargetView();
				}
			}
		}
		m_pD3DDeviceContext->OMSetRenderTargets(NumViews, renderTargetViews, depthStencilView);
		m_numRenderTargetView = NumViews;
	}
}