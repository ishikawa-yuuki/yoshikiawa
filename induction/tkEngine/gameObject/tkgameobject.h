/*!
 *@brief	�Q�[���I�u�W�F�N�g�̊��N���X�B
 */

#ifndef _CGAMEOBJECT_H_
#define _CGAMEOBJECT_H_


namespace tkEngine{
	class CGameObjectManager;
	class CRenderContext;
	typedef unsigned char	GameObjectPrio;
	/*!
	 *@brief	�Q�[���I�u�W�F�N�g�B
	 */
	class IGameObject : Noncopyable{
	public:
		using IGameObjectIsBase = IGameObject;
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		/*!
		 *@brief	�f�X�g���N�^
		 */
		virtual ~IGameObject()
		{
		}
	public:
		/*!
		*@brief	�C�x���g
		*/
		enum EnEvent {
			enEvent_Undef,			//!<����`�C�x���g�B
			enEvent_Destroy,		//!<�C���X�^���X���j�������B
			enBaseClassEvent_Num,	//!<���N���X�Œ�`����Ă���C�x���g�̐��B
			enEvent_User,			//!<����ȍ~�Ƀ��[�U�[��`�̃C�x���g���쐬���Ă��������B
			
		};
		/*!
		*@brief	�C�x���g�������̃f�[�^�B
		*/
		struct SEventParam {
			EnEvent eEvent = enEvent_Undef;			//!<�������Ă���C�x���g�B
			IGameObject* gameObject = nullptr;		//!<�C�x���g��ʒm���Ă���Q�[���I�u�W�F�N�g�̃C���X�^���X�B
		};
		/*!
		*@brief	Update�̒��O�ŌĂ΂��J�n�����B
		*@details
		* �{�֐���true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����</br>
		* Update�֐����Ă΂�o���܂��Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�܂��B</br>
		* �Q�[���I�u�W�F�N�g�̏������ɕ����t���[��������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v�Ȃǂ��g����</br>
		* �K�؂ɏ��������s���Ă��������B
		*/
		virtual bool Start() { return true; }
		/*!
		 *@brief	�X�V
		 */
		virtual void Update() {}
		/*!
		 *@brief	�`��
		 */
		[[deprecated("This function will be delete. please use ForwardRender() function.")]]
		virtual void Render(CRenderContext& renderContext)
		{
			(void)renderContext;
		}
		/*!
		*@brief	�t�H���[�h�����_�����O�̃p�X����Ă΂��`�揈���B
		*@details
		* ����ȃV�F�[�f�B���O���s���������̂͂�����Ń����_�����O���s���Ă��������B
		* �ʏ�̃����_�����O�͕����x�[�X�V�F�[�_�[���g�p����Ă��܂��B
		*/
		virtual void ForwardRender(CRenderContext& renderContext)
		{
			(void)renderContext;
		}
		/*!
		 *@brief	�폜�����Ƃ��ɌĂ΂��B
		 *@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
		 * �f�X�g���N�^���O�Ɏ��s����܂��B
		 */
		virtual void OnDestroy(){} 
		/*!
		*@brief	���s�D��x���擾�B
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
	public:
		/*!
		 *@brief	�C���X�^���X���������ꂽ����ɌĂ΂��֐��B
		 *@details	�R���X�g���N�^���Ă΂ꂽ��ő��Ă΂�܂��B
		 */
		virtual void Awake(){}
		/*!
		 *@brief	Update�֐������s�����O�ɌĂ΂��X�V�֐��B
		 */
		virtual void PreUpdate() {}
		/*!
		 *@brief	Update�֐������s���ꂽ��ŌĂ΂��X�V�֐��B
		 */
		virtual void PostUpdate() {} 
		/*!
		 *@brief	Render�֐������s�����O�ɌĂ΂��`�揈���B
		 */
		[[deprecated("This function will be delete. please use PreForwardRender() function.")]]
		virtual void PreRender(CRenderContext& renderContext) { 
			(void)renderContext; 
		}
		/*!
		*@brief	Render�֐������s�����O�ɌĂ΂��`�揈���B
		*/
		virtual void PreForwardRender(CRenderContext& renderContext) {
			(void)renderContext;
		}
		/*!
		 *@brief	Render�֐������s���ꂽ��ŌĂ΂��`�揈��
		 *@details
		 * �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
		 */
		virtual void PostRender(CRenderContext& renderContext) {
			(void)renderContext;
		}
		/*!
		*@brief	���S�t���O�𗧂Ă�B
		*@details
		* ���̊֐��̓G���W���̊O����͎��s���Ȃ��ł��������B
		*/
		void SetDeadMark()
		{
			m_isDead = true;
		}
		/*!
		*@brief	���S����B
		*/
		bool IsDead() const
		{
			return m_isDead;
		}
		/*!
		*@brief Start�֐������������H
		*/
		virtual bool IsStart() const
		{
			return m_isStart;
		}
		/*!
		*@brief �A�N�e�B�u���ǂ����𔻒�B
		*/
		bool IsActive() const
		{
			return m_isActive;
		}
		/*!
		*@brief �A�N�e�B�u�t���O��ݒ�B
		*/
		void SetActiveFlag(bool flag)
		{
			m_isActive = flag;
		}
		/*!
		*@brief �^�O��ݒ�B
		*/
		void SetTags(unsigned int tags)
		{
			m_tags = tags;
		}
		/*!
		*@brief �^�O���擾�B
		*/
		unsigned int GetTags() const
		{
			return m_tags;
		}
		/*!
		*@brief �C�x���g���X�i�[��o�^
		*@param[in]	listener	�C�x���g���X�i�[�B
		*/
		void AddEventListener(std::function<void(SEventParam& eventParam)> listener)
		{
			m_eventListeners.push_back(listener);
		}
#if 0 //���傢�I�~�b�g�B
		/*!
		*@brief �C�x���g���X�i�[��j��
		*@param[in]	listener	�j������C�x���g���X�i�[�B
		*/
		void RemoveEventListener(std::function<void(SEventParam& eventParam)> listener)
		{
			auto it = std::remove_if(
				m_eventListeners.begin(), 
				m_eventListeners.end(), 
				[&](auto& l) { return l == listener; }
			);
			m_eventListeners.erase(it, m_eventListeners.end());
		}
#endif
	public:
		void PostRenderWrapper(CRenderContext& renderContext)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostRender(renderContext);
			}
		}
		void ForwardRenderWrapper(CRenderContext& renderContext)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				ForwardRender(renderContext);
			}
		}
		void PreForwardRenderWrapper(CRenderContext& renderContext)
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreForwardRender(renderContext);
			}
		}
		void PostUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PostUpdate();
			}
		}
		void PreUpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				PreUpdate();
			}
		}
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Update();
			}
		}
		void StartWrapper()
		{
			if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
				if (Start()) {
					//���������������B
					m_isStart = true;
				}
			}
		}
		void OnDestroyWrapper()
		{
			SEventParam param;
			param.eEvent = enEvent_Destroy;
			param.gameObject = this;
			//�f�X�g���C�C�x���g�����X�i�[�ɒʒm����B
			for (auto& listener : m_eventListeners) {
				listener(param);
			}
			OnDestroy();
			
		}
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}
		
		friend class CGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<���s�D��x�B
		bool m_isStart;						//!<Start�̊J�n�t���O�B
		bool m_isDead;						//!<���S�t���O�B
		bool m_isRegistDeadList = false;	//!<���S���X�g�ɐς܂�Ă���B
		bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ�B
		bool m_isRegist = false;			//!<GameObjectManager�ɓo�^����Ă���H
		bool m_isActive = true;				//!<Active�t���O�B
		unsigned int m_tags = 0;			//!<�^�O�B
		unsigned int m_nameKey = 0;			//!<���O�L�[�B
		std::list<std::function<void(SEventParam& eventParam)>>	m_eventListeners;	//�C�x���g���X�i�[�B�B
	};
}
#endif // _CGAMEOBJECT_H_