/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/shadow/tkOminiDirectionShadowMap.h"
#include "tkEngine/graphics/preRender/shadow/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine {

	COminiDirectionShadowMap::COminiDirectionShadowMap()
	{
	}

	COminiDirectionShadowMap::~COminiDirectionShadowMap()
	{
		if (m_shadowMap != nullptr) {
			m_shadowMap->Release();
		}
		for (auto& rt : m_renderTargets) {
			rt->Release();
		}
		if (m_depthStencilTexture != nullptr) {
			m_depthStencilTexture->Release();
		}
		if (m_depthStencilView != nullptr) {
			m_depthStencilView->Release();
		}
	}
	bool COminiDirectionShadowMap::InitShadowMapTextures(ID3D11Device* pD3DDevice)
	{
		m_texDesc.Width = 512;
		m_texDesc.Height = 512;
		m_texDesc.MipLevels = 1;
		m_texDesc.ArraySize = NUM_TEXTURE;
		m_texDesc.Format = DXGI_FORMAT_R32_FLOAT;
		m_texDesc.SampleDesc.Count = 1;
		m_texDesc.SampleDesc.Quality = 0;
		m_texDesc.Usage = D3D11_USAGE_DEFAULT;
		m_texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		m_texDesc.CPUAccessFlags = 0;
		m_texDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		auto hr = pD3DDevice->CreateTexture2D(&m_texDesc, nullptr, &m_shadowMap);
		if (FAILED(hr)) {
			//�L���[�u�}�b�v�̍쐬�Ɏ��s�B
			return false;
		}
		//SRV���쐬�B
		if (m_shadowMapSRV.Create(m_shadowMap) == false) {
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitRenderTargetViews(ID3D11Device* pD3DDevice)
	{
		//�����_�����O�^�[�Q�b�g�r���[���쐬����B
		D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
		ZeroMemory(&rtDesc, sizeof(rtDesc));
		rtDesc.Format = m_texDesc.Format;
		
		for (int i = 0; i < NUM_TEXTURE; i++) {
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			rtDesc.Texture2DArray.FirstArraySlice = i;
			rtDesc.Texture2DArray.ArraySize = 1;
			auto hr = pD3DDevice->CreateRenderTargetView(
				m_shadowMap, &rtDesc, &m_renderTargets[i]);
			if (FAILED(hr)) {
				//�����_�����O�^�[�Q�b�g�r���[�̍쐬�Ɏ��s�����B
				return false;
			}
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitDepthStencilTextures(ID3D11Device* pD3DDevice)
	{
		m_depthTexDesc = m_texDesc;
		m_depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		m_depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		auto hr = pD3DDevice->CreateTexture2D(&m_depthTexDesc, nullptr, &m_depthStencilTexture);
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::InitDepthStencilViews(ID3D11Device* pD3DDevice)
	{
		CD3D11_DEPTH_STENCIL_VIEW_DESC descDSV(
			D3D11_DSV_DIMENSION_TEXTURE2D,
			m_depthTexDesc.Format
		);

		auto hr = pD3DDevice->CreateDepthStencilView(
			m_depthStencilTexture, &descDSV, &m_depthStencilView
		);
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
	bool COminiDirectionShadowMap::Init(const SOminiShadowRenderConfig& config)
	{
		if (config.isEnable == false) {
			return true;
		}

		auto pD3DDevice = GraphicsEngine().GetD3DDevice();
		
		//�V���h�E�}�b�v�`��p�̃e�N�X�`�����쐬����B
		if (InitShadowMapTextures(pD3DDevice) == false) {
			//�V���h�E�}�b�v�p�̃e�N�X�`���̍쐬�Ɏ��s�B
			TK_WARNING_MESSAGE_BOX("COminiDirectionShadowMap::InitShadowMapTextures()�Ŏ��s���܂����B");
			return false;
		}
		//�����_�����O�^�[�Q�b�g�r���[���쐬�B
		if (InitRenderTargetViews(pD3DDevice) == false) {
			//�����_�����O�^�[�Q�b�g�r���[�̍쐬�Ɏ��s�B
			TK_WARNING_MESSAGE_BOX("COminiDirectionShadowMap::InitRenderTargetViews()�Ŏ��s���܂����B");
			return false;
		}
		//�f�v�X�X�e���V���e�N�X�`�����쐬����B
		if (InitDepthStencilTextures(pD3DDevice) == false) {
			TK_WARNING_MESSAGE_BOX("COminiDirectionShadowMap::InitDepthStencilTextures()�Ŏ��s���܂����B");
			return false;
		}
		//�f�v�X�X�e���V���r���[���쐬����B
		if (InitDepthStencilViews(pD3DDevice) == false) {
			TK_WARNING_MESSAGE_BOX("COminiDirectionShadowMap::InitDepthStencilViews()�Ŏ��s���܂����B");
			return false;
		}

		//�f�o�t���̒萔�o�b�t�@���쐬����B
		m_ominiDirectionShadowCbGPU.Create(nullptr, sizeof(SOminiDirectionShadowCb));

		m_isInited = config.isEnable;
		m_isEnable = true;
		return true;
	}

	void COminiDirectionShadowMap::Update()
	{
		
	}
	
	void COminiDirectionShadowMap::RenderToShadowMapImp(CRenderContext& rc)
	{
		rc.SetRenderStep(enRenderStep_RenderToShadowMap);

		BeginGPUEvent(L"enRenderStep_COminiDirectionShadowMap::RenderToShadowMap");

		if (IsEnable() == false) {
			return;
		}
		static const CVector3 cameraDirectionTbl[NUM_TEXTURE] = {
			{ 1.0f,  0.0f,  0.0f },	//POSITIVE_X
			{-1.0f,  0.0f,  0.0f },	//NEGATIVE_X
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_Y
			{ 0.0f, -1.0f,  0.0f },	//NEGATIVE_Y
			{ 0.0f,  0.0f,  1.0f },	//POSITIVE_Z
			{ 0.0f,  0.0f, -1.0f },	//NEGATIVE_Z
		};
		static const CVector3 cameraUpTbl[NUM_TEXTURE] = {
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_X
			{ 0.0f,  1.0f,  0.0f },	//NEGATIVE_X
			{ 0.0f,  0.0f, -1.0f },	//POSITIVE_Y
			{ 0.0f,  0.0f,  1.0f },	//NEGATIVE_Y
			{ 0.0f,  1.0f,  0.0f },	//POSITIVE_Z
			{ 0.0f,  1.0f,  0.0f },	//NEGATIVE_Z
		};

		//�S���ʃV���h�E�}�b�v�����W�X�^����O���B
		rc.PSUnsetShaderResource(enSkinModelSRVReg_OminiDirectionShadowMap);

		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);

		for (int i = 0; i < NUM_TEXTURE; i++) {
			BeginGPUEvent(L"Render 3DModel");
			//�J�����s����쐬����B
			CMatrix mView;
			mView.MakeLookAt(
				m_ominiDirectionShadowCbCPU.lightPosition,
				m_ominiDirectionShadowCbCPU.lightPosition + cameraDirectionTbl[i],
				cameraUpTbl[i] );
			//�ˉe�s����쐬����B
			CMatrix mProj;
			mProj.MakeProjectionMatrix(
				CMath::DegToRad(90.0f),
				1.0f,
				m_near,
				m_ominiDirectionShadowCbCPU.distanceAffectedByLight
			);

			m_ominiDirectionShadowCbCPU.lightViewProjMatrix[i] = mView * mProj;


			rc.OMSetRenderTarget(m_renderTargets[i], m_depthStencilView);
			rc.RSSetViewport(
				0.0f, 0.0f,
				(float)m_texDesc.Width,
				(float)m_texDesc.Height
			);
			float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor);
			//
			//�V���h�E�L���X�^�[���h���[
			for (auto& caster : m_shadowCaster) {
				caster->Render(rc, m_ominiDirectionShadowCbCPU.lightViewProjMatrix[i]);
			}

			EndGPUEvent();
		}

		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());

		EndGPUEvent();
	}
	void COminiDirectionShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
		if (IsEnable() == false) {
			return;
		}
		rc.UpdateSubresource(m_ominiDirectionShadowCbGPU, &m_ominiDirectionShadowCbCPU);
		rc.PSSetConstantBuffer(enSkinModelCBReg_OminiDirectionShadow, m_ominiDirectionShadowCbGPU);
		//�L���[�u�}�b�v��]������B
		rc.PSSetShaderResource(enSkinModelSRVReg_OminiDirectionShadowMap, m_shadowMapSRV);
	}
}