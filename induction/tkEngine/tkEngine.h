/*!
 *@file	tkEngine.h
 */
#pragma once

#include "tkEngine/graphics/tkRenderTarget.h"
#include "tkEngine/timer/tkStopwatch.h"
#include "tkEngine/Sound/tkSoundEngine.h"
#include "tkEngine/graphics/tkGraphicsEngine.h"
#include "tkEngine/tkEngineStruct.h"
#include "tkEngine/physics/tkPhysics.h"
#include "tkEngine/random/tkRandom.h"
#include "tkEngine/graphics/font/tkFont.h"
#include "tkEngine/debug/math/tkVectorRender.h"
#include <thread>
#include <mutex>
#include <condition_variable>

 /*!
  *@namespace	tkEngine�S�̖̂��O��ԁB
  */
namespace tkEngine{
	/*!
	 *@brief	�͌��w�������Q�[���G���W�� version 2.2
	 */
	class CEngine : Noncopyable {
	private:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CEngine();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CEngine();
	public:
		/*!
		 *@brief	�������B
		 *@param[in]	initParam		�������p�����[�^�B
		 */
		bool Init(const SInitParam& initParam);
		/*!
		 *@brief	�I�������B
		 */
		void Final();
		/*!
		 *@brief	�Q�[�����[�v�����s�B
		 */
		void RunGameLoop();
		/*!
		 *@brief	�C���X�^���X���擾�B
		 */
		static CEngine& GetInstance()
		{
			static CEngine* instance = nullptr;
			if (instance == nullptr) {
				instance = new CEngine;
			}
			return *instance;
		}

		/*!
		* @brief	�Q�[���p�b�h�̎擾�B
		*@param[in]	padNo	�p�b�h�ԍ��BCPad::CONNECT_PAD_MAX-1�܂Ŏw��\�B
		*/
		CPad& GetPad(int padNo)
		{
			TK_ASSERT(padNo < CPad::CONNECT_PAD_MAX && padNo >= 0, "padNo is invalid");
			return m_pad[padNo];
		}
		/*!
		* @brief	�T�E���h�G���W���̎擾�B
		*/
		CSoundEngine& GetSoundEngine()
		{
			return m_soundEngine;
		}
		/*!
		* @brief	�O���t�B�b�N�X�G���W���̎擾�B
		*/
		CGraphicsEngine& GetGraphicsEngine()
		{
			return m_graphicsEngine;
		}
		/*!
		 *@brief	�������[���h�̎擾�B
		 */
		CPhysicsWorld& GetPhysicsWorld()
		{
			return m_physicsWorld;
		}
		/*!
		*@brief	���C���J�������擾�B
		*/
		CCamera& GetMainCamera()
		{
			return m_graphicsEngine.GetMainCamera();
		}
		/*!
		*@brief	2D�J�������擾�B
		*/
		CCamera& GetMainCamera2D()
		{
			return m_graphicsEngine.Get2DCamera();
		}
		/*!
		 *@brief	�����擾�B
		 */
		CRandom& GetRandom()
		{
			return m_random;
		}
		/*!
		*@brief		���\�[�X�̃A�����[�h�B
		*@details
		* �풓���\�[�X�ȊO�̃��\�[�X�����ׂăA�����[�h���܂��B
		* �V�[���̐؂�ւ��ȂǂŁA���\�[�X�̃A�����[�h���K�v�ȏꍇ�Ɏg�p���Ă��������B
		*/
		void ResourceUnload();
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		prefab::CVectorRender* GetVectorRender()
		{
			return m_vectorRender;
		}
#endif
	private:
		/*!
		 *@brief	�E�B���h�E�������B
		 */
		bool InitWindow( const SInitParam& initParam );
		
		/// <summary>
		/// �Q�[���X���b�h�B
		/// </summary>
		void GameThread();
		/*!
		* @brief	�E�B���h�E�v���V�[�W���B
		*@param[in]	hWnd	�E�B���h�E�n���h��
		*@param[in] msg		���b�Z�[�W
		*@param[in] wParam	WPARAM
		*@param[in] lParam	LPARAM
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/// <summary>
		/// �Q�[�������̍X�V�����B
		/// </summary>
		void GameUpdate();
	private:
		HINSTANCE				m_hInst = nullptr;	//!<�A�v���P�[�V�����̃C���X�^���X�B
		HWND					m_hWnd = nullptr;	//!<�E�B���h�E�n���h���B
		CGraphicsEngine			m_graphicsEngine;							//!<�O���t�B�b�N�G���W���B
		CSoundEngine			m_soundEngine;								//!<�T�E���h�G���W���B
		CPhysicsWorld			m_physicsWorld;								//!<�������[���h�B
		int						m_screenWidth = 0;							//!<�X�N���[���̕��B
		int						m_screenHeight = 0;							//!<�X�N���[���̍����B
		CPad					m_pad[CPad::CONNECT_PAD_MAX];				//!<�Q�[���p�b�h�B
		CRandom					m_random;									//!<�����B
		std::unique_ptr<std::thread> m_gameThread;							//�Q�[���X���b�h�B
		bool			m_isRunGameThread = false;
		bool			m_isReqDeadGameThread = false;
		std::mutex		m_isRunGameThreadMtx;
		std::condition_variable m_isRunGameThreadCv;
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		std::unique_ptr<CFont>	m_font;
		float					m_fps = 30.0f;
		float					m_timeTotal = 0.0f;
		prefab::CVectorRender*  m_vectorRender = nullptr;					//!<�x�N�g�������_���[�B
#endif
	public:
		CStopwatch				m_sw;
	};

	/*!
	* @brief	Engine�̃C���X�^���X���擾�B
	*/
	static inline CEngine& Engine()
	{
		return CEngine::GetInstance();
	}
	/*!
	* @brief	CPad�̃C���X�^���X���擾�B
	*/
	static inline CPad& Pad(int padNo)
	{
		return Engine().GetPad(padNo);
	}
	/*!
	* @brief	CSoundEngine�̃C���X�^���X���擾�B
	*/
	static inline CSoundEngine& SoundEngine()
	{
		return Engine().GetSoundEngine();
	}
	/*!
	* @brief	CGraphicsEngine�̃C���X�^���X���擾�B
	*/
	static inline CGraphicsEngine& GraphicsEngine()
	{
		return Engine().GetGraphicsEngine();
	}
	/*!
	 *@brief	CPhysicsWorld�̃C���X�^���X���擾�B
	 */
	static inline CPhysicsWorld& PhysicsWorld()
	{
		return Engine().GetPhysicsWorld();
	}
	/*!
	* @brief	���C���J�����̃C���X�^���X���擾�B
	*/
	static inline CCamera& MainCamera()
	{
		return GraphicsEngine().GetMainCamera();
	}
	/*!
	* @brief	���C���J����(2D)�̃C���X�^���X���擾�B
	*/
	static inline CCamera& MainCamera2D()
	{
		return GraphicsEngine().Get2DCamera();
	}
	/*!
	* @brief	CLightManager�̃C���X�^���X���擾�B
	*/
	static inline CLightManager& LightManager()
	{
		return GraphicsEngine().GetLightManager();
	}
	/*!
	* @brief	GPU�C�x���g�̊J�n�B
	*/
	static inline void BeginGPUEvent(const wchar_t* name)
	{
		GraphicsEngine().BeginGPUEvent(name);
	}
	/*!
	* @brief	GPU�C�x���g�̏I���B
	*/
	static inline void EndGPUEvent()
	{
		GraphicsEngine().EndGPUEvent();
	}
	/*!
	 *@brief	�������擾�B
	 */
	static inline CRandom& Random()
	{
		return Engine().GetRandom();
	}
	/*!
	*@brief	G-Buffer��SRV���擾�B
	*/
	static inline CShaderResourceView& GetGBufferSRV(EnGBuffer gBuffer)
	{
		return Engine().GetGraphicsEngine().GetGBufferRender().GetRenderTarget(gBuffer).GetRenderTargetSRV();
	}
	/// <summary>
	/// �|�X�g�G�t�F�N�g�̋@�\�ɊȈՓI�ɃA�N�Z�X���邽�߂̖��O��ԁB
	/// </summary>
	namespace postEffect {
		/// <summary>
		/// ��ʊE�[�x�ɃA�N�Z�X
		/// </summary>
		static inline CDof& Dof()
		{
			return GraphicsEngine().GetPostEffect().GetDof();
		}
		/// <summary>
		/// �g�[���}�b�v�ɃA�N�Z�X�B
		/// </summary>
		/// <returns></returns>
		static inline CTonemap& Tonemap()
		{
			return GraphicsEngine().GetPostEffect().GetTonemap();
		}
	}
	//�f�o�b�O�@�\���ȈՓI�ɃA�N�Z�X���邽�߂̖��O���
	namespace dbg {
		
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		/*!
		* @brief	�R���W�����̃f�o�b�O�\����L���ɂ���B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		static inline void SetDrawPhysicsCollisionEnable()
		{
			PhysicsWorld().SetDebugDrawMode(1);
		}
		/*!
		* @brief	�R���W�����̃f�o�b�O�\����L���ɂ���B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		static inline void SetDrawPhysicsCollisionDisable()
		{
			PhysicsWorld().SetDebugDrawMode(0);
		}
		/*!
		* @brief	�x�N�g���̃f�o�b�O�o�́B
		*/
		static inline void DrawVector(CVector3 vector, CVector3 origin, const char* name = "no name")
		{
			prefab::CVectorRender::SRenderData renderData = { name, vector, origin };
			Engine().GetVectorRender()->AddVector(renderData);
		}
		/*!
		* @brief	�x�N�g���̃f�o�b�O�`���L���ɂ���B
		*/
		static inline void SetDrawVectorEnable()
		{
			Engine().GetVectorRender()->SetRenderFlag(true);
		}
		/*!
		* @brief	�x�N�g���̃f�o�b�O�`��𖳌��ɂ���B
		*/
		static inline void SetDrawVectorDisable()
		{
			Engine().GetVectorRender()->SetRenderFlag(false);
		}
		static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
		{
			Engine().GetVectorRender()->SetRenderVectorNameList(list);
		}
#else

		static inline void SetDrawPhysicsCollisionEnable()
		{
		}

		static inline void SetDrawPhysicsCollisionDisable()
		{
		}

		static inline void DrawVector(CVector3 vector, CVector3 origin, const char* name = "no name")
		{
		}
		
		static inline void SetDrawVectorEnable()
		{
		}
	
		static inline void SetDrawVectorDisable()
		{
		}
		static inline void SetDrawVectorNameList(const std::vector<std::string>& list)
		{
		}
#endif

	}
}


