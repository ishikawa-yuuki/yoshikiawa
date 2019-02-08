/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#pragma once

namespace tkEngine{
	/*!
	*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
	*/
	struct AnimClipHeader {
		std::uint32_t numKey;				//!<�L�[�t���[���̐��B
		std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
	};
	/*!
	*@brief	�A�j���[�V�����C�x���g
	*/
	struct AnimationEvent {
		float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
		std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
	};
	/*!
	 *@brief	�L�[�t���[���B
	 */
	struct Keyframe {
		std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
		float time;					//!<���ԁB
		CMatrix transform;			//!<�g�����X�t�H�[���B
	};
	/*!
	*@brief	�L�[�t���[���B
	*/
	struct KeyframeRow {
		std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
		float time;					//!<���ԁB
		CVector3 transform[4];		//!<�g�����X�t�H�[���B
	};
	/*!
	*@brief	�A�j���[�V�����C�x���g�B
	*/
	class CAnimationEvent : Noncopyable {
	public:
		CAnimationEvent()
		{
		}
		/*!
		*@brief	�C�x���g�������Ԃ�ݒ�B
		*/
		float GetInvokeTime() const
		{
			return m_invokeTime;
		}
		/*!
		*@brief	�C�x���g�����擾�B
		*/
		const wchar_t* GetEventName() const
		{
			return m_eventName.c_str();
		}
		/*!
		*@brief	�C�x���g�������Ԃ�ݒ�B
		*/
		void SetInvokeTime(float time)
		{
			m_invokeTime = time;
		}
		/*!
		*@brief	�C�x���g����ݒ�B
		*/
		void SetEventName(const wchar_t* name)
		{
			m_eventName = name;
		}
		/*!
		*@brief	�C�x���g�������ς݂�����B
		*/
		bool IsInvoked() const
		{
			return m_isInvoked;
		}
		/*!
		*@brief	�C�x���g�������ς݂̃t���O��ݒ肷��B
		*/
		void SetInvokedFlag(bool flag)
		{
			m_isInvoked = flag;
		}
	private:
		bool m_isInvoked = false;	//!<�C�x���g�����ς݁H
		float m_invokeTime;			//!<�C�x���g�������ԁB
		std::wstring m_eventName;	//!<�C�x���g���B
	};
	/*!
	 *@brief	�A�j���[�V�����N���b�v�B
	 */
	class CAnimationClip : Noncopyable {
	public:
		/*!
		 *@brief	�{�[���̃t���[�Y���B
		 */
		struct SFreezeBoneInfo {
			int boneNo;		//!<�t���[�Y������{�[���ԍ��B
			bool freezeX;	//!<X�����̈ړ����t���[�Y������H
			bool freezeY;	//!<Y�����̈ړ����t���[�Y������H
			bool freezeZ;	//!<Z�����̈ړ����t���[�Y������H
		};
		typedef std::vector<Keyframe*>		keyFramePtrList;
		/*!
		* @brief	�R���X�g���N�^
		*/
		CAnimationClip() 
		{
			m_freezeBoneInfo.boneNo = -1;
			m_freezeBoneInfo.freezeX = false;
			m_freezeBoneInfo.freezeY = false;
			m_freezeBoneInfo.freezeZ = false;
		}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CAnimationClip();
		/*!
		 *@brief	�A�j���[�V�����N���b�v�����[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 *@param[in]	clipName	�N���b�v���B
		 */
		void Load(const wchar_t* filePath, const wchar_t* cliipName = nullptr);
#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
		/*!
		*@brief	�A�b�v�R���o�[�^�[�B
		*@details
		* �g���̂ăR�[�h�̉�B�g��Ȃ��悤�ɁB
		*/
		void Upconverte(const wchar_t* filePath);
#endif
		/*!
		*@brief	���[�v����H
		*/
		bool IsLoop() const
		{
			return m_isLoop;
		}
		/*!
		*@brief	���[�v�t���O��ݒ肷��B
		*/
		void SetLoopFlag(bool flag)
		{
			m_isLoop = flag;
		}
		/*!
		*@brief
		*/
		const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
		{
			return m_keyFramePtrListArray;
		}
		const keyFramePtrList& GetTopBoneKeyFrameList() const
		{
			return *m_topBoneKeyFramList;
		}
		/*!
		 *@brief	�N���b�v�����擾�B
		 */
		const wchar_t* GetName() const
		{
			return m_clipName.c_str();
		}
		/*!
		*@brief	�A�j���[�V�������t���[�Y����{�[���̏���ݒ�B
		*@details
		* �t���[�Y���ꂽ�{�[����Y�����̈ړ��ʂ͂��ׂẴ{�[������ł�������܂��B
		*  ���ȂɂŎg����H
		*		���A�j���[�V�����Ɉړ��ʂ������Ă���W�����v���[�V�����Ƃ��Ŏg����B
		*/
		void SetFreezeBoneInfo(int boneNo, bool freezeX, bool freezeY, bool freezeZ)
		{
			m_freezeBoneInfo.boneNo = boneNo;
			m_freezeBoneInfo.freezeX = freezeX;
			m_freezeBoneInfo.freezeY = freezeY;
			m_freezeBoneInfo.freezeZ = freezeZ;
		}
		/*!
		*@brief	X�����̃A�j���[�V�������t���[�Y���Ă���{�[���̔ԍ����擾�B
		*/
		const SFreezeBoneInfo& GetFreezeBoneInfo() const
		{
			return m_freezeBoneInfo;
		}
		/*!
		*@brief	�A�j���[�V�����C�x���g���擾�B
		*/
		std::unique_ptr<CAnimationEvent[]>& GetAnimationEvent()
		{
			return m_animationEvent;
		}
		/*!
		*@brief	�A�j���[�V�����C�x���g�̐����擾�B
		*/
		int GetNumAnimationEvent() const
		{
			return m_numAnimationEvent;
		}
		/*!
		*@brief	�A�j���[�V�����N���b�v�̓��[�h�ς݁H
		*/
		bool IsLoaded() const
		{
			return m_loaded;
		}
	private:
		using KeyframePtr = std::unique_ptr<Keyframe>;
		std::wstring m_clipName;	//!<�A�j���[�V�����N���b�v�̖��O�B
		bool m_isLoop = false;	//!<���[�v�t���O�B
		std::vector<KeyframePtr>			m_keyframes;				//�L�[�t���[���B
		std::vector<keyFramePtrList>		m_keyFramePtrListArray;		//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
		std::unique_ptr<CAnimationEvent[]>	m_animationEvent;			//�A�j���[�V�����C�x���g�B
		int									m_numAnimationEvent = 0;	//�A�j���[�V�����C�x���g�̐��B
		keyFramePtrList*				m_topBoneKeyFramList = nullptr;
		SFreezeBoneInfo m_freezeBoneInfo;	//!<�t���[�Y������{�[�����B
		bool m_loaded = false;	//�A�j���[�V�����N���b�v�����[�h����Ă���H
	};
	using CAnimationClipPtr = std::unique_ptr<CAnimationClip>;
}