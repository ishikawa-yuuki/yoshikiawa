/*!
 * @brief	�����_�����O�^�[�Q�b�g�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/graphics/tkRenderTarget.h"


namespace tkEngine{
	CRenderTarget::CRenderTarget()
	{
	}
	CRenderTarget::~CRenderTarget()
	{
		Release();
	}
	bool CRenderTarget::Create(
		int w,
		int h,
		int mipLevel,
		int arraySize,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		DXGI_SAMPLE_DESC multiSampleDesc,
		ID3D11Texture2D* renderTarget,
		ID3D11Texture2D* depthStencil,
		bool isResolveTexture
	)
	{
		Release();
		m_isResolveTexture = isResolveTexture;
		m_width = w;
		m_height = h;
		m_textureFormat = colorFormat;
		m_depthStencliFormat = depthStencilFormat;
		if (multiSampleDesc.Count > 1) {
			//MSAA���L���B
			m_isMSAA = true;
		}
		//�����_�����O�^�[�Q�b�g�̍쐬�B
		D3D11_TEXTURE2D_DESC texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.Width = w;
		texDesc.Height = h;
		texDesc.MipLevels = mipLevel;
		texDesc.ArraySize = arraySize;
		texDesc.Format = colorFormat;
		texDesc.SampleDesc = multiSampleDesc;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		if (m_isMSAA) {
			//MSAA���L���̎���UAV�Ƀo�C���h�ł��Ȃ��H
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		}
		else {
			texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		}
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;
	
		ID3D11Device* pD3DDevice = GraphicsEngine().GetD3DDevice();
		HRESULT hr;
		if (renderTarget == nullptr) {
			hr = pD3DDevice->CreateTexture2D(&texDesc, NULL, &m_renderTarget);
			if (FAILED(hr)) {
				//�����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s�B
				return false;
			}
		}
		else {
			//�����_�����O�^�[�Q�b�g���w�肳��Ă���B
			m_renderTarget = renderTarget;
			m_renderTarget->AddRef();	//�Q�ƃJ�E���^�����Z����B
		}
		//�����_�����O�^�[�Q�b�g�r���[���쐬�B
		D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
		ZeroMemory(&rtDesc, sizeof(rtDesc));
		rtDesc.Format = texDesc.Format;
		if (texDesc.SampleDesc.Count > 1) {
			//MSAA
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else {
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		}
		hr = pD3DDevice->CreateRenderTargetView(m_renderTarget, &rtDesc, &m_renderTargetView);
		if (FAILED(hr)) {
			return false;
		}

		if (depthStencilFormat != DXGI_FORMAT_UNKNOWN) {
			//�f�v�X�X�e���V�����쐬�B
			D3D11_TEXTURE2D_DESC depthTexDesc = texDesc;
			depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthTexDesc.Format = depthStencilFormat;
			if (depthStencil == nullptr) {
				hr = pD3DDevice->CreateTexture2D(&depthTexDesc, NULL, &m_depthStencil);
				if (FAILED(hr)) {
					return false;
				}
			}
			else {
				//�f�v�X�X�e���V�����w�肳��Ă���B
				m_depthStencil = depthStencil;
				m_depthStencil->AddRef();	//�Q�ƃJ�E���^�𑝂₷�B
			}
			//�f�v�X�X�e���V���r���[���쐬�B
			// Create the depth stencil view
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = depthTexDesc.Format;
			if (texDesc.SampleDesc.Count > 1) {
				//MSAA
				descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			else {
				descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			}
			descDSV.Texture2D.MipSlice = 0;
			hr = pD3DDevice->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
			if (FAILED(hr)) {
				return false;
			}
		}
		if (m_isMSAA || m_isResolveTexture) {
			//MSAA���L���̎��́A���]���u���ꂽ�e�N�X�`����SRV�Ƃ��Ďg�p����B
			//���]���u��ƂȂ�e�N�X�`�����쐬����B
			texDesc.SampleDesc.Count = 1;
			texDesc.SampleDesc.Quality = 0;
			hr = pD3DDevice->CreateTexture2D(&texDesc, NULL, &m_resolveTextureMSAA);
			if (FAILED(hr)) {
				//���]���u��̍쐬�Ɏ��s�B
				return false;
			}

			m_renderTargetSRV.Create(m_resolveTextureMSAA);
		}
		else {
			//�����_�����O�^�[�Q�b�g��SRV���쐬�B
			m_renderTargetSRV.Create(m_renderTarget);
			//�����_�����O�^�[�Q�b�g��UAV���쐬�B
			m_renderTargetUAV.Create(m_renderTarget);
		}
		return true;
	}
	void CRenderTarget::Release()
	{
		m_renderTargetSRV.Release();
		m_renderTargetUAV.Release();
		if (m_renderTarget != nullptr) {
			m_renderTarget->Release();
			m_renderTarget = nullptr;
		}
		if (m_renderTargetView != nullptr) {
			m_renderTargetView->Release();
			m_renderTargetView = nullptr;
		}
		if (m_resolveTextureMSAA != nullptr) {
			m_resolveTextureMSAA->Release();
		}
		if(m_depthStencil != nullptr){
			m_depthStencil->Release();
			m_depthStencil = nullptr;
		}
		if(m_depthStencilView != nullptr){
			m_depthStencilView->Release();
			m_depthStencilView = nullptr;
		}
	}
}