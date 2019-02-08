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
	
	 
	/*!
	*@brief	�`��G���W���B
	*@details
	* 2018/08/03 release notes
	* 	tkEngine�̕`��G���W����TBDR(Tile Based Deferred Rendering)�Ŏ�������Ă���B
	* 	�V�[���̕`��菇�͉��L�ƂȂ�B
	*  	.1 �v�������_�����O
	*     		1-1 ShadowMap�̍쐬
	*	   		1-2 �^�C�����Ƃ� LightCulling
	*			1-3 G-Buffer�̍쐬�B
	*  	.2 �f�B�t�@�[�h�V�F�[�f�B���O
	*   .3 Forward�����_�����O
	*			����ȃV�F�[�f�B���O���s���}�e���A���A�������}�e���A���̕`��͂����ōs���B
	*  	.4 �|�X�g�G�t�F�N�g
	*	.5 HUD�ȂǁA�|�X�g�����������Ȃ��`����s���B	
	* TBDR�̗̍p�ɂ��A��ʂ̓��I�����������Ɉ������Ƃ��ł���B
	* ���I�����͍ő��1024�ݒu���邱�Ƃ��ł���B�G���W�����J�X�^�}�C�Y���邱�ƂŊg�����\�B
	*/
	class CGraphicsEngine : Noncopyable {
	public:
		CGraphicsEngine();
		~CGraphicsEngine();
		/*!
		* @brief	�������B
		*/
		bool Init(HWND hwnd, const SInitParam& initParam);
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		 *@brief	CGBufferRender�̎擾�B
		 */
		CGBufferRender& GetGBufferRender()
		{
			return m_preRender.GetGBufferRender();
		}

		/*!
		 *@brief	�G�t�F�N�g�G���W���̎擾�B
		 */
		CEffectEngine& GetEffectEngine()
		{
			return m_effectEngine;
		}
		/*!
		* @brief	�V���h�E�}�b�v���擾�B
		*/
		CShadowMap& GetShadowMap()
		{
			return m_preRender.GetShadowMap();
		}
		/*!
		* @brief	�g�[���}�b�v���擾�B
		*/
		CTonemap& GetTonemap()
		{
			return m_postEffect.GetTonemap();
		}
		/*!
		*@brief	���C���J�������擾�B
		*/
		CCamera& GetMainCamera()
		{
			return m_mainCamera;
		}
		/*!
		*@brief	2D�J�������擾�B
		*/
		CCamera& Get2DCamera()
		{
			return m_2dCamera;
		}
		/*!
		*@brief	Direct3DDevice�̎擾�B
		*/
		ID3D11Device* GetD3DDevice() const
		{
			return m_pd3dDevice;
		}
		/*!
		*@brief	ID3D11DeviceContext�̎擾�B
		*/
		ID3D11DeviceContext* GetD3DImmediateDeviceContext() const
		{
			return m_pImmediateContext;
		}
		/*!
		*@brief	�`��R�}���h��ςނ̂Ɏg�p���Ă���ID3D11DeviceContext�̎擾�B
		*/
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
		
		/*!
		*@brief		�t���[���o�b�t�@�̕����擾�B
		*/
		int GetFrameBufferWidth() const
		{
			return m_frameBufferWidth;
		}
		/*!
		*@brief		�t���[���o�b�t�@�̍������擾�B
		*/
		int GetFrameBufferHeight() const
		{
			return m_frameBufferHeight;
		}
		/*!
		 *@brief	2D��Ԃ̃X�N���[���̕��B
		 */
		int Get2DSpaceScreenWidth() const
		{
			return m_2dSpaceScreenWidth;
		}
		/*!
		*@brief	2D��Ԃ̃X�N���[���̍����B
		*/
		int Get2DSpaceScreenHeight() const
		{
			return m_2dSpaceScreenHeight;
		}

		/*!
		* @brief	���C�������_�����O�^�[�Q�b�g�̎擾�B
		*/
		CRenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}
		/// <summary>
		/// ���C���X���b�h����Ăяo���`��J�n�̏����B
		/// </summary>
		void BeginRender();
		/*!
		* @brief	�`��I���B
		*/
		/// <summary>
		/// ���C���X���b�h����Ăяo���`��I�������B
		/// ���ꂪ1�t���[���̍Ō�̕`�揈���ɂȂ�B
		/// </summary>
		void EndRender();
		/// <summary>
		/// �Q�[���X���b�h����Ăяo���I�������B
		/// </summary>
		void EndRenderFromGameThread();
		/*!
		* @brief	�v�������_�����O�擾�B�B
		*/
		CPreRender& GetPreRender()
		{
			return m_preRender;
		}
		/*!
		* @brief	�|�X�g�G�t�F�N�g���擾�B
		*/
		CPostEffect& GetPostEffect()
		{
			return m_postEffect;
		}
		CRenderContext& GetRenderContext()
		{
			return m_renderContext;
		}
		/*!
		*@brief	���C�g�̊Ǘ��҂��擾�B
		*/
		CLightManager& GetLightManager()
		{
			return m_lightManager;
		}
		/*!
		*@brief	���C�������_�����O�^�[�Q�b�g��MSAA�̐ݒ���擾�B
		*/
		const DXGI_SAMPLE_DESC& GetMainRenderTargetMSAADesc() const
		{
			return m_mainRenderTargetMSAADesc;
		}
		/*!
		*@brief	GPU�C�x���g�J�n�B
		*@param[in]		eventName		�C�x���g�̖��O�B
		*/
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
		/*!
		*@brief	GPU�C�x���g�I���B
		*/
		void EndGPUEvent()
		{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			if (m_userAnnoation) {
				m_userAnnoation->EndEvent();
			}
#endif
		}
		/*!
		*@brief	�V�F�[�_�[���\�[�X���擾�B
		*/
		CShaderResources& GetShaderResources()
		{
			return m_shaderResources;
		}
		/*!
		*@brief	SpriteBatch�̎擾�B
		*@details
		* �Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		*/
		DirectX::SpriteBatch* GetSpriteBatch() const
		{
			return m_spriteBatch.get();
		}
		/*!
		*@brief	SpriteFont�̎擾�B
		*@details
		* �Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		*/
		DirectX::SpriteFont* GetSpriteFont() const
		{
			return m_spriteFont.get();
		}
		/*!
		*@brief	�|�X�g�G�t�F�N�g�̏��������������Ƃ��ɌĂ΂�鏈���B
		*@details
		* �Q�[���w�ł͎g�p���Ȃ��悤�ɁB
		*/
		void EndPostEffect(CRenderContext& rc);
		/*!
		*@brief	DirectX���f�����\�[�X�̎擾�B
		*/
		CDirectXModelResource& GetDirectXModelResource()
		{
			return m_directXModelResource;
		}
		/*!
		*@brief	�f�B�t�@�[�h�V�F�[�f�B���O�B
		*/
		void DefferdShading(CRenderContext& rc);
	private:
		/*!
		 *@brief	D3D�f�o�C�X�ƃX���b�v�`�F�C���̏������B
		 */
		bool InitD3DDeviceAndSwapChain(HWND hwnd, const SInitParam& initParam);
		/*!
		 *@brief	�o�b�N�o�b�t�@�̏������B
		 */
		bool InitBackBuffer();
		/*!
		 *@brief	���C�������_�����O�^�[�Q�b�g�̏������B
		 */
		bool InitMainRenderTarget();
		/*!
		*@brief	�f�B�t�@�[�h�V�F�[�f�B���O�̏������B
		*/
		void InitDefferdShading();
	private:
		/*!
		*@brief	����̃����o��ύX������AdefferdShading.fx��PSDefferdCb���ύX����悤�ɁI�I�I
		*/
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