/*!
 * @brief	�T���v���X�e�[�g
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkSamplerState.h"

namespace tkEngine{
	/*!
	 * @brief	�T���v���X�e�[�g���쐬�B
	 */
	bool CSamplerState::Create(const D3D11_SAMPLER_DESC& desc)
	{
		Release();
		HRESULT hr = GraphicsEngine().GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
		if (FAILED(hr)) {
			TK_LOG("Failed CSamplerState::Create\n");
			return false;
		}
		return true;
	}
}