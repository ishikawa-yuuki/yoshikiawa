/*!
 * @brief	G-Buffer�̕`��B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkGBufferRender.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"


namespace tkEngine{
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CGBufferRender::CGBufferRender()
	{
	}
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	CGBufferRender::~CGBufferRender()
	{
		m_depthTextureLastFrame->Release();
	}
	/*!
	*@brief	�������B
	*/
	void CGBufferRender::Init(const SGraphicsConfig& config)
	{
		CGraphicsEngine& ge = GraphicsEngine();

		DXGI_SAMPLE_DESC msaaDesc;
		ZeroMemory(&msaaDesc, sizeof(msaaDesc));
		msaaDesc.Count = 1;
		msaaDesc.Quality = 0;

		//�A���x�h�o�b�t�@�̏������B
		m_GBuffer[enGBufferAlbedo].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT,
			msaaDesc
		);
		m_GBuffer[enGBufferAlbedo].SetDepthStencilView(
			ge.GetMainRenderTarget().GetDepthStencilView()
		);
		//�@���o�b�t�@�̏������B
		m_GBuffer[enGBufferNormal].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//�ڃx�N�g���o�b�t�@�̏������B
		m_GBuffer[enGBufferTangent].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//�X�y�L�����o�b�t�@�̏������B
		m_GBuffer[enGBufferSpecular].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//�e�}�b�v�̏������B
		m_GBuffer[enGBufferShadow].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);

		//�[�x�o�b�t�@�̏������B
		m_GBuffer[enGBufferDepth].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
		//���Ȕ����F�o�b�t�@�̏������B
		m_GBuffer[enGBufferEmission].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);
	
		//1�t���[���O�̐[�x�l���L�^���邽�߂̃e�N�X�`�����쐬����B
		D3D11_TEXTURE2D_DESC texDesc;
		ZeroMemory(&texDesc, sizeof(texDesc));
		texDesc.Width = ge.GetFrameBufferWidth();
		texDesc.Height = ge.GetFrameBufferHeight();
		texDesc.MipLevels = 1;
		texDesc.ArraySize = 1;
		texDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		texDesc.SampleDesc = msaaDesc;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.CPUAccessFlags = 0;
		texDesc.MiscFlags = 0;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		ID3D11Device* pD3DDevice = GraphicsEngine().GetD3DDevice();
		HRESULT hr;
		hr = pD3DDevice->CreateTexture2D(&texDesc, NULL, &m_depthTextureLastFrame);
		TK_ASSERT(hr == S_OK, "�Ղ���");
		m_depthTextureLastFrameSRV.Create(m_depthTextureLastFrame);

		//�}�e���A��ID�o�b�t�@�̏������B
		m_GBuffer[enGBufferMateriaID].Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			msaaDesc
		);

		m_shadowBlur.Init(m_GBuffer[enGBufferShadow].GetRenderTargetSRV(), 5.0f, config.shadowRenderConfig);
		
		m_cb.Create(NULL, sizeof(m_cbEntity));
	}
	
	void CGBufferRender::SetGBufferParamToReg(CRenderContext& rc)
	{
		rc.PSSetShaderResource(enSkinModelSRVReg_AlbedoTexture, m_GBuffer[enGBufferAlbedo].GetRenderTargetSRV() );
		rc.PSSetShaderResource(enSkinModelSRVReg_NormalMap, m_GBuffer[enGBufferNormal].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSKinModelSRVReg_Specularmap, m_GBuffer[enGBufferSpecular].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_DepthMap, m_GBuffer[enGBufferDepth].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_Tangent, m_GBuffer[enGBufferTangent].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_MaterialID, m_GBuffer[enGBufferMateriaID].GetRenderTargetSRV());
		rc.PSSetShaderResource(enSkinModelSRVReg_EmissionColor, m_GBuffer[enGBufferEmission].GetRenderTargetSRV());

		if (GraphicsEngine().GetShadowMap().GetSoftShadowLevel() == EnSoftShadowQualityLevel::enNone) {
			//�n�[�h�V���h�E�B
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_GBuffer[enGBufferShadow].GetRenderTargetSRV());
		}
		else {
			//�\�t�g�V���h�E
			rc.PSSetShaderResource(enSkinModelSRVReg_SoftShadowMap, m_shadowBlur.GetResultSRV());
		}
	}
	void CGBufferRender::UnsetGBufferParamFromReg(CRenderContext& rc)
	{
		rc.PSUnsetShaderResource(enSkinModelSRVReg_AlbedoTexture);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_NormalMap);
		rc.PSUnsetShaderResource(enSKinModelSRVReg_Specularmap);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_DepthMap);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_Tangent);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_MaterialID);
		rc.PSUnsetShaderResource(enSkinModelSRVReg_EmissionColor);

		if (GraphicsEngine().GetShadowMap().GetSoftShadowLevel() == EnSoftShadowQualityLevel::enNone) {
			//�n�[�h�V���h�E�B
			rc.PSUnsetShaderResource(enSkinModelSRVReg_SoftShadowMap);
		}
		else {
			//�\�t�g�V���h�E
			rc.PSUnsetShaderResource(enSkinModelSRVReg_SoftShadowMap);
		}
	}
	void CGBufferRender::Render(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_RenderGBuffer");
		EnSoftShadowQualityLevel ssLevel = GraphicsEngine().GetShadowMap().GetSoftShadowLevel();

		rc.CopyResource(m_depthTextureLastFrame, m_GBuffer[enGBufferDepth].GetRenderTarget());
		//�e�𗎂Ƃ����߂̏���]���B
		GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(rc);

		rc.SetRenderStep(enRenderStep_RenderGBuffer);

		m_cbEntity.isPCFShadowMap = ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF;
		rc.UpdateSubresource(m_cb, &m_cbEntity);

		rc.PSSetConstantBuffer(enSkinModelCBReg_GBuffer, m_cb);
		//�����_�����O�^�[�Q�b�g�̃o�b�N�A�b�v���擾����B
		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);

		//�����_�����O�^�[�Q�b�g��ύX����B
		CRenderTarget* renderTargets[enGBufferNum];
		for( int i = 0; i < enGBufferNum ; i++ ){
			renderTargets[i] = &m_GBuffer[i];
		};
		rc.OMSetRenderTargets(enGBufferNum, renderTargets);
		//G�o�b�t�@���N���A�B
		float clearColor[enGBufferNum][4] = { 
			{ 0.5f, 0.5f, 0.5f, 1.0f }, //enGBufferAlbedo
			{ 0.0f, 1.0f, 0.0f, 1.0f }, //enGBufferNormal
			{ 0.0f, 0.0f, 0.0f, 1.0f }, //enGBufferSpecular
			{ 0.0f, 0.0f, 0.0f, 1.0f }, //enGBufferShadow
			{ 1.0f, MainCamera().GetFar() - MainCamera().GetNear(), 1.0f, 1.0f },	//enGBufferDepth
			{ 1.0f, 0.0f, 0.0f, 1.0f },	//enGBufferTangent
			{ 0.0f, 0.0f, 0.0f, 0.0f },	//enGBufferMateriaID
			{ 0.0f, 0.0f, 0.0f, 1.0f },	//enGBufferEmission
		};
		
		for (int i = 0; i < enGBufferNum; i++) {
			rc.ClearRenderTargetView(i, clearColor[i]);
		}

		for (auto& skinModel : m_skinModels) {
			skinModel->Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
		}

		//�����_�����O�^�[�Q�b�g��߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);

		if (ssLevel == EnSoftShadowQualityLevel::eSSSS
			|| ssLevel == EnSoftShadowQualityLevel::eSSSS_PCF
		) {
			//�X�N���[���X�y�[�X�\�t�g�V���h�E�B
			//�e�}�b�v�Ƀu���[��������B
			m_shadowBlur.Execute(rc);
		}

		m_skinModels.clear();

		EndGPUEvent();
	}
}