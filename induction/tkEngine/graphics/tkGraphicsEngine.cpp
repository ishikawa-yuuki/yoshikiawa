/*!
 *@brief	�`��G���W���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkGraphicsEngine.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"

namespace tkEngine{
	CGraphicsEngine::CGraphicsEngine()
	{
	}
	CGraphicsEngine::~CGraphicsEngine()
	{
	}
	void CGraphicsEngine::Release()
	{

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (m_userAnnoation) {
			m_userAnnoation->Release();
			m_userAnnoation = nullptr;
		}
#endif
		if (m_backBufferRT) {
			m_backBufferRT->Release();
			m_backBufferRT = nullptr;
		}
		if (m_pImmediateContext) {
			m_pImmediateContext->ClearState();
			m_pImmediateContext = nullptr;
		}
		m_mainRenderTarget.Release();
		
		if (m_pSwapChain) {
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}
		for (auto& commandList : m_commandList) {
			if (commandList != nullptr) {
				commandList->Release();
				commandList = nullptr;
			}
		}
		if (m_pImmediateContext) {
			m_pImmediateContext->Release();
			m_pImmediateContext = nullptr;
		}
		if (m_pDeferredDeviceContext) {
			m_pDeferredDeviceContext->Release();
			m_pDeferredDeviceContext = nullptr;
		}
		if (m_pd3dDevice) {
			m_pd3dDevice->Release();
			m_pd3dDevice = nullptr;
		}
	}
	/*!
	*@brief	�f�B�t�@�[�h�V�F�[�f�B���O�̏������B
	*/
	void CGraphicsEngine::InitDefferdShading()
	{
		//�f�B�t�@�[�h�V�F�[�f�B���O�p�̃V�F�[�_�[�����[�h�B
		m_vsDefferd.Load("shader/defferdShading.fx", "VSMain", CShader::EnType::VS);
		m_psDefferd.Load("shader/defferdShading.fx", "PSMain", CShader::EnType::PS);
		//�萔�o�b�t�@���������B
		m_cbDefferd.Create(nullptr, sizeof(PSDefferdCb));
	}
	bool CGraphicsEngine::InitD3DDeviceAndSwapChain(HWND hwnd, const SInitParam& initParam)
	{
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		m_frameBufferWidth = initParam.frameBufferWidth;
		m_frameBufferHeight = initParam.frameBufferHeight;
		
		//�X���b�v�`�F�C�����쐬�B
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;							//�X���b�v�`�F�C���̃o�b�t�@���B�ʏ�͂P�B
		sd.BufferDesc.Width = m_frameBufferWidth;	//�t���[���o�b�t�@�̕��B
		sd.BufferDesc.Height = m_frameBufferHeight;	//�t���[���o�b�t�@�̍����B
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�t���[���o�b�t�@�̃t�H�[�}�b�g�BR8G8B8A8��32bit�B
		sd.BufferDesc.RefreshRate.Numerator = 60;			//���j�^�̃��t���b�V�����[�g�B(�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���^�C�~���O�ƂȂ�B)
		sd.BufferDesc.RefreshRate.Denominator = 1;			//�Q�ɂ�����30fps�ɂȂ�B���ƂŎ����B
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�T�[�t�F�X�܂��̓��\�[�X���o�̓����_�[ �^�[�Q�b�g�Ƃ��Ďg�p���܂��B
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;							//�s�N�Z���P�ʂ̃}���`�T���v�����O�̐��BMSAA�͂Ȃ��B
		sd.SampleDesc.Quality = 0;							//MSAA�Ȃ��B
		sd.Windowed = TRUE;

		//���ׂẴh���C�o�^�C�v�ŃX���b�v�`�F�C���̍쐬�������B
		HRESULT hr = E_FAIL;
		for (auto driverType : driverTypes) {
			m_driverType = driverType;
			hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pd3dDevice, &m_featureLevel, &m_pImmediateContext);
			if (SUCCEEDED(hr)) {
				//�X���b�v�`�F�C�����쐬�ł����̂Ń��[�v�𔲂���B
				break;
			}
		}
		if (FAILED(hr)) {
			//�X���b�v�`�F�C�����쐬�ł��Ȃ������B
			return false;
		}
		//�f�o�C�X�̃}���`�X���b�h�T�|�[�g�̋@�\�𒲂ׂ�B
		m_pd3dDevice->CheckFeatureSupport(
			D3D11_FEATURE_THREADING,
			&m_featureDataThreading,
			sizeof(m_featureDataThreading)
			);
		
		
		if (m_featureDataThreading.DriverCommandLists == TRUE) {
			//�f�o�C�Y���f�B�t�@�[�h�R���e�L�X�g�ɑΉ����Ă���̂�
			//�f�B�t�@�[�h�R���e�L�X�g���쐬�B
			m_pd3dDevice->CreateDeferredContext(0, &m_pDeferredDeviceContext);
		}
		return true;
	}
	
	bool CGraphicsEngine::InitBackBuffer()
	{
		//�������ݐ�ɂȂ郌���_�����O�^�[�Q�b�g���쐬�B
		ID3D11Texture2D* pBackBuffer = NULL;
		HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr)) {
			return false;
		}
		hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_backBufferRT);
		if (FAILED(hr)) {
			return false;
		}
		return true;
	}
	bool CGraphicsEngine::InitMainRenderTarget()
	{
		//MSAA�̐ݒ������B	
		ZeroMemory(&m_mainRenderTargetMSAADesc, sizeof(m_mainRenderTargetMSAADesc));
		m_mainRenderTargetMSAADesc.Count = 1;
		m_mainRenderTargetMSAADesc.Quality = 0;

		bool ret = m_mainRenderTarget.Create(
			m_frameBufferWidth,
			m_frameBufferHeight,
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			m_mainRenderTargetMSAADesc,
			nullptr,
			nullptr,
			true
		);
		
		if (!ret) {
			//�쐬���s
			return false;
		}
		return true;
	}
	
	bool CGraphicsEngine::Init(HWND hwnd, const SInitParam& initParam)
	{
		//D3D�f�o�C�X�ƃX���b�v�`�F�C���̍쐬�B
		if (!InitD3DDeviceAndSwapChain(hwnd, initParam)) {
			return false;
		}
		//�o�b�N�o�b�t�@�̍쐬�B
		if (!InitBackBuffer()) {
			return false;
		}
		//���C�������_�����O�^�[�Q�b�g�̏������B
		if (!InitMainRenderTarget()) {
			return false;
		}
		//�����_�����O�R���e�L�X�g�̏������B
		m_renderContext.Init(m_pImmediateContext, m_pDeferredDeviceContext);
		auto deviceContext = m_renderContext.GetD3DDeviceContext();

		CRenderTarget* renderTargets[] = {
			&m_mainRenderTarget
		};
		m_renderContext.OMSetRenderTargets(1, renderTargets);
		//�r���[�|�[�g��ݒ�B
		m_renderContext.RSSetViewport(0.0f, 0.0f, (FLOAT)m_frameBufferWidth, (FLOAT)m_frameBufferHeight);
		//PreRender�̏������B
		m_preRender.Create(initParam.graphicsConfing);
		//PostEffect�̏������B
		m_postEffect.Create(initParam.graphicsConfing);
		//���C�g�Ǘ��҂̏������B
		m_lightManager.Init();

		//�R�s�[�p�̃V�F�[�_�[�����[�h�B
		m_copyVS.Load("shader/copy.fx", "VSMain", CShader::EnType::VS);
		m_copyPS.Load("shader/copy.fx", "PSMain", CShader::EnType::PS);

		m_cb.Create(nullptr, 16);
		//�f�B�t�@�[�h�V�F�[�f�B���O�p�̏��������s���B
		InitDefferdShading();

		//�t�H���g�p�̃f�[�^�̏������B
		m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
		m_spriteFont = std::make_unique<DirectX::SpriteFont>(m_pd3dDevice, L"font/myfile.spritefont");

		//2D�J�����̏������B
		m_2dCamera.SetTarget(CVector3::Zero);
		m_2dCamera.SetPosition({0.0f, 0.0f, -10.0f});
		m_2dCamera.SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
		m_2dCamera.SetNear(0.1f);
		m_2dCamera.SetFar(1000.0f);
		m_2dCamera.Update();
		//�e�탌���_�����O�X�e�[�g������������B
		AlphaBlendState::Init(*this);
		DepthStencilState::Init(*this);
		RasterizerState::Init(*this);
		//�T���v���X�e�[�g������������B
		CPresetSamplerState::Init();
		//�G�t�F�N�g�G���W���̏������B
		m_effectEngine.Init();
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		deviceContext->QueryInterface(__uuidof(ID3DUserDefinedAnnotation), (void**)&m_userAnnoation);
#endif
		return true;

	}
	void CGraphicsEngine::BeginRender()
	{
		auto& commandList = m_commandList[m_commandListNoMainThread];
		//�쐬�����R�}���h�����s�B
		if (commandList != nullptr) {
			m_pImmediateContext->ExecuteCommandList(commandList, FALSE);
			commandList->Release();
			commandList = nullptr;
		}
	}
	void CGraphicsEngine::DefferdShading(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_DefferdShading");
		rc.SetRenderStep(enRenderStep_ForwardRender);
		//���C�g�̏���]���]���B
		LightManager().Render(rc);
		//�e�𗎂Ƃ����߂̏���]���B
		GraphicsEngine().GetShadowMap().SendShadowReceiveParamToGPU(rc);
		GraphicsEngine().GetGBufferRender().SetGBufferParamToReg(rc);
		//�萔�o�b�t�@���X�V�B
		PSDefferdCb cb;
		cb.mViewProjInv.Inverse(MainCamera().GetViewProjectionMatrix());
		rc.UpdateSubresource(m_cbDefferd, &cb);
		//�萔�o�b�t�@��b0�̃��W�X�^�ɐݒ�B
		rc.PSSetConstantBuffer(0, m_cbDefferd);
		//�V�F�[�_�[��ݒ�B
		rc.VSSetShader(m_vsDefferd);
		rc.PSSetShader(m_psDefferd);

		//�f�B�t�@�[�h�����_�����O�p�̃f�v�X�X�e���V���X�e�[�g�B
		ID3D11DepthStencilState* depthStencil = rc.GetDepthStencilState();
		//rc.OMSetDepthStencilState(DepthStencilState::defferedRender, 0);
		rc.OMSetDepthStencilState(DepthStencilState::spriteRender);
		//�|�X�g�G�t�F�N�g�̃t���X�N���[���`��̋@�\���g���B
		m_postEffect.DrawFullScreenQuad(rc);

		GraphicsEngine().GetGBufferRender().UnsetGBufferParamFromReg(rc);

		rc.OMSetDepthStencilState(depthStencil);

		EndGPUEvent();

	}
	void CGraphicsEngine::EndPostEffect(CRenderContext& rc)
	{
		//�o�b�N�o�b�t�@�Ƀ��C�������_�����O�^�[�Q�b�g�̓��e���R�s�[�B
		ID3D11Texture2D* pBackBuffer = NULL;
		m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		ID3D11RenderTargetView* rts[] = {
			m_backBufferRT
		};
		rc.OMSetRenderTargets(1, rts, nullptr);
		rc.VSSetShader(m_copyVS);
		rc.PSSetShader(m_copyPS);
		CVector2 uvOffset;
		uvOffset.x = 0.5f / m_frameBufferWidth;
		uvOffset.y = 0.5f / m_frameBufferHeight;
		rc.UpdateSubresource(m_cb, &uvOffset);
		rc.PSSetConstantBuffer(0, m_cb);

		rc.PSSetShaderResource(0, m_postEffect.GetFinalRenderTarget().GetRenderTargetSRV());
		rc.RSSetState(RasterizerState::spriteRender);
		rc.RSSetViewport(0, 0, m_frameBufferWidth, m_frameBufferHeight);
		//�|�X�g�G�t�F�N�g�̃t���X�N���[���`��̋@�\���g���B
		m_postEffect.DrawFullScreenQuad(rc);
		pBackBuffer->Release();
		rc.PSUnsetShaderResource(0);
	}
	void CGraphicsEngine::EndRenderFromGameThread()
	{
		m_lightManager.EndRender(m_renderContext);
		if (IsMultithreadRendering()) {
			//�R�}���h���X�g���쐬�B
			int commandListNo = 1 ^ m_commandListNoMainThread;
			m_pDeferredDeviceContext->FinishCommandList(FALSE, &m_commandList[commandListNo]);
		}
	}

	void CGraphicsEngine::EndRender()
	{
		m_pSwapChain->Present(1, 0);
		if (IsMultithreadRendering()) {
			//�R�}���h���X�g�����ւ���B
			m_commandListNoMainThread = 1 ^ m_commandListNoMainThread;
		}
	}
}