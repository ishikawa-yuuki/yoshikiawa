/*!
 *@brief	�`��G���W��
 */

#pragma once


#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkengine/light/tkLightManager.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"
#include "tkEngine/resource/tkShaderResources.h"
#include "tkEngine/graphics/effect/tkEffectEngine.h"
#include "tkEngine/resource/tkDirectXModelResource.h"

namespace tkEngine{
	/// <summary>
	/// �`��G���W��
	/// </summary>
	/// <remarks>
	/// 2019/03/26 release notes
	/// tkEngine�̕`��G���W����TBDR(Tile Based Deferred Rendering)�Ŏ�������Ă���B
	/// TBDR�̗̍p�ɂ��A��ʂ̓��I�����������Ɉ������Ƃ��ł���B
	/// ���I�����͍ő��1024�ݒu���邱�Ƃ��ł���B�G���W�����J�X�^�}�C�Y���邱�ƂŊg�����\�B
	/// �V�[���̕`��菇�͉��L�ƂȂ�B
	/// .1�@�v�������_�����O
	///			1-1  �S���ʃV���h�E�}�b�v�̐����B
	///			1-2  �w�������C�g�ɂ��V���h�E�}�b�v�̐����B
	///			1-3  G-Buffer�̍쐬�B
	///			1-4  ���C�g�J�����O�B
	/// .2�@�f�B�t�@�[�h�V�F�[�f�B���O
	///			1-4�ō쐬���ꂽ�V���h�E�}�b�v�AG-Buffer�A���C�g�J�����O��������
	///			PBR�x�[�X�̃V�F�[�f�B���O���s���B
	/// .3  �t�H���[�h�V�F�[�f�B���O
	///			�����������ȃV�F�[�f�B���O���s���}�e���A���̕`����s���B
	/// .4  �|�X�g�G�t�F�N�g
	///			1-1  �g�[���}�b�v�B
	///			1-2  Effekseer�𗘗p�����G�t�F�N�g�`��B
	///			1-3  Temporal Screen Space Reflection�B
	///			1-4  �쐣���u���[���B
	///			1-5  DOF
	///			1-6  �A���`�G�C���A�X(FXAA)�B
	///			1-7  �f�B�U�����O�B
	/// .5  �|�X�g�����_�����O
	///			HUD�Ȃǃ|�X�g�G�t�F�N�g�����������Ȃ��`����s���B
	/// </remarks>
	class CGraphicsEngine : Noncopyable {
	public:
		CGraphicsEngine();
		~CGraphicsEngine();
		
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="hwnd">�E�B���h�E�n���h��</param>
		/// <param name="initParam">�������p�̃p�����[�^�B</param>
		/// <returns></returns>
		bool Init(HWND hwnd, const SInitParam& initParam);

		/// <summary>
		/// �J���B
		/// </summary>
		/// <remarks>
		/// �G���W�������ŗ��p����Ă��܂��B���[�U�[�͗��p���Ȃ��ł��������B
		/// </remarks>
		void Release();

		/// <summary>
		/// GBufferRender�N���X�̃C���X�^���X���擾�B
		/// </summary>
		CGBufferRender& GetGBufferRender()
		{
			return m_preRender.GetGBufferRender();
		}

		/// <summary>
		/// CEffectEngine�N���X�̃C���X�^���X���擾�B
		/// </summary>
		CEffectEngine& GetEffectEngine()
		{
			return m_effectEngine;
		}
		/*!
		* @brief	�w�����V���h�E�}�b�v���擾�B
		*/
		/// <summary>
		/// �w�����V���h�E�}�b�v�N���X�̃C���X�^���X���擾�B
		/// </summary>
		CDirectionShadowMap& GetDirectionShadowMap()
		{
			return m_preRender.GetDirectionShadowMap();
		}
		/// <summary>
		/// �S���ʃV���h�E�}�b�v�N���X�̃C���X�^���X���擾�B
		/// </summary>
		COminiDirectionShadowMap& GetOminiDirectionShadowMap()
		{
			return m_preRender.GetOminiDirectionShadowMap();
		}
		/// <summary>
		/// �g�[���}�b�v�N���X�̃C���X�^���X���擾�B
		/// </summary>
		CTonemap& GetTonemap()
		{
			return m_postEffect.GetTonemap();
		}
		/// <summary>
		/// 3D�J�������擾��B
		/// </summary>
		CCamera& GetMainCamera()
		{
			return m_mainCamera;
		}
		/// <summary>
		/// 2D�J�������擾�B
		/// </summary>
		CCamera& Get2DCamera()
		{
			return m_2dCamera;
		}
		/// <summary>
		/// D3D�f�o�C�X���擾�B
		/// </summary>
		ID3D11Device* GetD3DDevice() const
		{
			return m_pd3dDevice;
		}
	
		/// <summary>
		/// D3D�����f�o�C�X�R���e�L�X�g�̎擾�B
		/// </summary>
		/// <returns></returns>
		ID3D11DeviceContext* GetD3DImmediateDeviceContext() const
		{
			return m_pImmediateContext;
		}
		/// <summary>
		/// �`��R�}���h��ςނ̂Ɏg�p���Ă�D3D�f�o�C�X�R���e�L�X�g���擾�B
		/// </summary>
		/// <returns></returns>
		ID3D11DeviceContext* GetD3DDeviceContext() const
		{
			return m_renderContext.GetD3DDeviceContext();
		}
		/// <summary>
		/// �}���`�X���b�h�����_�����O���s���Ă���H
		/// </summary>
		/// <returns>true�Ȃ�}���`�X���b�h�����_�����O���s���Ă���B</returns>
		bool IsMultithreadRendering() const
		{
			return m_pDeferredDeviceContext != nullptr;
		}
		/// <summary>
		/// �t���[���o�b�t�@�̕����擾�B
		/// </summary>
		int GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/// <summary>
		/// �t���[���o�b�t�@�̍������擾�B
		/// </summary>
		int GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/// <summary>
		/// 2D��Ԃ̃X�N���[���̕����擾�B
		/// </summary>
		int Get2DSpaceScreenWidth() const
		{
			return m_2dSpaceScreenWidth;
		}
		/// <summary>
		/// 2D��Ԃ̃X�N���[���̍������擾�B
		/// </summary>
		int Get2DSpaceScreenHeight() const
		{
			return m_2dSpaceScreenHeight;
		}
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̎擾�B
		/// </summary>
		/// <returns></returns>
		CRenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}
		/// <summary>
		/// ���C���X���b�h����Ăяo���`��J�n�̏����B
		/// </summary>
		void BeginRender();

		/// <summary>
		/// ���C���X���b�h����Ăяo���`��I�������B
		/// ���ꂪ1�t���[���̍Ō�̕`�揈���ɂȂ�B
		/// </summary>
		void EndRender();

		/// <summary>
		/// �Q�[���X���b�h����Ăяo���I�������B
		/// </summary>
		void EndRenderFromGameThread();

		/// <summary>
		/// �v�������_�����O�̃C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		CPreRender& GetPreRender()
		{
			return m_preRender;
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g�̃C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		CPostEffect& GetPostEffect()
		{
			return m_postEffect;
		}
		/// <summary>
		/// �����_�����O�R���e�L�X�g�̃C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		CRenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/// <summary>
		/// ���C�g�̊Ǘ��҂̃C���X�^���X���擾�B
		/// </summary>
		/// <returns></returns>
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}

		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g��MSAA�̐ݒ���擾�B
		/// </summary>
		/// <returns></returns>
		const DXGI_SAMPLE_DESC& GetMainRenderTargetMSAADesc() const
		{
			return m_mainRenderTargetMSAADesc;
		}

		/// <summary>
		/// GPU�C�x���g�J�n�B
		/// </summary>
		/// <param name="eventName">�C�x���g�̖��O</param>
		void BeginGPUEvent(const wchar_t* eventName)
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			if (m_userAnnoation) {
				m_userAnnoation->BeginEvent(eventName);
			}
#else
			(void)eventName;
#endif
		}
		/// <summary>
		/// GPU�C�x���g�I���B
		/// </summary>
		void EndGPUEvent()
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			if (m_userAnnoation) {
				m_userAnnoation->EndEvent();
			}
#endif
		}
		/// <summary>
		/// �V�F�[�_�[���\�[�X�̎擾�B
		/// </summary>
		/// <returns></returns>
		CShaderResources& GetShaderResources()
		{
			return m_shaderResources;
		}
		/*!
		*@brief	SpriteBatch�̎擾�B
		*@details
		* �Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		*/
		/// <summary>
		/// SpriteBatch�̎擾
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p����܂��B�Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		/// </remarks>
		/// <returns></returns>
		DirectX::SpriteBatch* GetSpriteBatch() const
		{
			return m_spriteBatch.get();
		}
		/// <summary>
		/// SpriteFont�̎擾�B
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p����܂��B�Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		/// </remarks>
		/// <returns></returns>
		DirectX::SpriteFont* GetSpriteFont() const
		{
			return m_spriteFont.get();
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g�̏��������������Ƃ��ɌĂ΂�鏈���B
		/// </summary>
		/// <remarks>
		/// �G���W�������Ŏg�p����܂��B�Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		/// </remarks>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void EndPostEffect(CRenderContext& rc);
		
		/// <summary>
		/// DirectX���f�����\�[�X�̎擾
		/// </summary>
		/// <returns></returns>
		CDirectXModelResource& GetDirectXModelResource()
		{
			return m_directXModelResource;
		}
		/// <summary>
		/// �f�B�t�@�[�h�V�F�[�f�B���O�̎��s�B
		/// </summary>
		/// <param name="rc"></param>
		void DefferdShading(CRenderContext& rc);
	private:
		/// <summary>
		/// D3D�f�o�C�X�ƃX���b�v�`�F�C���̏������B
		/// </summary>
		/// <param name="hwnd">�E�B���h�E�n���h��</param>
		/// <param name="initParam">�������p�����[�^</param>
		/// <returns>true���Ԃ��Ă����珉��������</returns>
		bool InitD3DDeviceAndSwapChain(HWND hwnd, const SInitParam& initParam);

		/// <summary>
		/// �o�b�N�o�b�t�@�̏������B
		/// </summary>
		/// <returns>true���Ԃ��Ă����珉��������</returns>
		bool InitBackBuffer();
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̏������B
		/// </summary>
		/// <returns></returns>
		bool InitMainRenderTarget();
	
		/// <summary>
		/// �f�B�t�@�[�h�V�F�[�f�B���O�̏������B
		/// </summary>
		void InitDefferdShading();
	private:
		/// <summary>
		/// ���̍\���̂̃����o��ύX������AdefferdShading.fx��PSDefferdCb���ύX����悤�ɁI�I�I
		/// </summary>
		struct PSDefferdCb {
			CMatrix mViewProjInv;		//!<�r���[�v���W�F�N�V�����s��̋t�s��B
		};
		ID3D11Device*			m_pd3dDevice = nullptr;						//!<D3D11�f�o�C�X�B
		CRenderContext			m_renderContext;							//!<�����_�����O�R���e�L�X�g�B
		ID3D11DeviceContext*	m_pImmediateContext = nullptr;				//!<D3D11�����f�o�C�X�R���e�L�X�g�B
		ID3D11DeviceContext*	m_pDeferredDeviceContext = nullptr;			//!<D3D11�f�B�t�@�[�h�f�o�C�X�R���e�L�X�g�B
		IDXGISwapChain*			m_pSwapChain = nullptr;						//!<SwapChain�B
		CRenderTarget			m_mainRenderTarget;							//!<���C�������_�����O�^�[�Q�b�g�B
		CPreRender				m_preRender;								//!<�v�������_�����O�B
		CPostEffect				m_postEffect;								//!<�|�X�g�G�t�F�N�g�B
		CCamera					m_mainCamera;								//!<���C���J�����B
		CCamera					m_2dCamera;									//!<2D�J�����B
		CEffectEngine			m_effectEngine;								//!<�G�t�F�N�g�G���W���B
		int						m_frameBufferWidth = 0;						//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		int						m_frameBufferHeight = 0;					//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		DXGI_SAMPLE_DESC		m_mainRenderTargetMSAADesc;					//!<���C�������_�����O�^�[�Q�b�g��MSAA�̐ݒ�B
		D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<�h���C�o�̎�ނ̃I�v�V�����B
		D3D_FEATURE_LEVEL		m_featureLevel = D3D_FEATURE_LEVEL_11_0;	//!<Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
		CLightManager			m_lightManager;								//!<���C�g�̊Ǘ��ҁB
		CShader					m_copyVS;									//!<�R�s�[�p�̒��_�V�F�[�_�[�B
		CShader					m_copyPS;									//!<�R�s�[�p�̃s�N�Z���V�F�[�_�[�B
		ID3D11RenderTargetView*	m_backBufferRT = nullptr;					//!<�o�b�N�o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
		ID3DUserDefinedAnnotation* m_userAnnoation = nullptr;
		CShaderResources		m_shaderResources;							//!<�V�F�[�_�[���\�[�X�B
		std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//!<�X�v���C�g�o�b�`�B
		std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//!<�X�v���C�g�t�H���g�B
		const int				m_2dSpaceScreenWidth = 1280;				//!<2D��Ԃ̃X�N���[���̕��B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
		const int				m_2dSpaceScreenHeight = 720;				//!<2D��Ԃ̃X�N���[���̍����B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
		CDirectXModelResource	m_directXModelResource;						//!<DirectX���f�����\�[�X�̊Ǘ��ҁB
		CConstantBuffer			m_cbDefferd;								//!<�f�B�t�@�[�h�V�F�[�f�B���O�p�̒萔�o�b�t�@�B
		CShader					m_vsDefferd;								//!<�f�B�t�@�[�h�V�F�[�f�B���O�p�̒��_�V�F�[�_�[�B
		CShader					m_psDefferd;								//!<�f�B�t�@�[�h�V�F�[�f�B���O�p�̃s�N�Z���V�F�[�_�[�B
		ID3D11CommandList*		m_commandList[2] = { nullptr };				//!<�R�}���h���X�g�B
		D3D11_FEATURE_DATA_THREADING m_featureDataThreading;				//!<�O���t�B�b�N�h���C�o�ŃT�|�[�g����Ă���}���`�X���b�h�@�\�ɂ��Ă̏��B
		int m_commandListNoMainThread = 0;									//!<���C���X���b�h�ŃA�N�Z�X���Ă���R�}���h���X�g�̔ԍ��B
		CConstantBuffer m_cb;
	};
}