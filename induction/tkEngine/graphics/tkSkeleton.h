/*!
 *@brief	�X�P���g��
 */
#pragma once


namespace tkEngine{
	class CAnimation;
	/*!
	*@brief	�{�[���B
	*/
	class CBone : Noncopyable{
	public:
		/*!
		*@brief	�R���X�g���N�^�B
		*@param[in]	boneName		�{�[���̖��O�B
		*@param[in]	bindPose		�o�C���h�|�[�Y�̍s��B
		*@param[in] invBindPose		�o�C���h�|�[�Y�̋t�s��B
		*@param[in]	parentId		�e�̃{�[���ԍ��B
		*@param[in] boneId			�{�[���ԍ��B
		*/
		CBone(
			const wchar_t* boneName,
			const CMatrix& bindPose,
			const CMatrix& invBindPose,
			int parentId,
			int boneId
		) :
			m_boneName(boneName),
			m_bindPose(bindPose),
			m_invBindPose(invBindPose),
			m_parentId(parentId),
			m_worldMatrix(bindPose),
			m_boneId(boneId)
		{
		}
		/*!
		 *@brief	���[�J���s���ݒ�
		 */
		void SetLocalMatrix(const CMatrix& m)
		{
			m_localMatrix = m;
		}
		/*!
		 *@brief	���[�J���s����擾�B
		 */
		const CMatrix& GetLocalMatrix() const
		{
			return m_localMatrix;
		}
		/*!
		*@brief	���[���h�s���ݒ�B
		*/
		void SetWorldMatrix(const CMatrix& m)
		{
			m_worldMatrix = m;
		}
		/*!
		 *@brief	���[���h�s����擾�B
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	�o�C���h�|�[�Y�̍s����擾�B
		*/
		const CMatrix& GetBindPoseMatrix() const
		{
			return m_bindPose;
		}
		/*!
		 *@brief	�o�C���h�|�[�Y�̋t�s����擾�B
		 */
		const CMatrix& GetInvBindPoseMatrix() const
		{
			return m_invBindPose;
		}
		/*!
		 *@brief	�e�̃{�[���s����擾�B
		 */
		int GetParentId() const
		{
			return m_parentId;
		}
		/*!
		 *@brief	�{�[���ԍ��̎擾�B
		 */
		int GetNo() const
		{
			return m_boneId;
		}

		/*!
		*@brief	�q����ǉ��B
		*/
		void AddChild(CBone* bone) 
		{
			m_children.push_back(bone);
		}
		/*!
		*@brief	�q�����擾�B
		*/
		std::list<CBone*>& GetChildren()
		{
			return m_children;
		}
		const CMatrix& GetOffsetLocalMatrix() const
		{
			return m_offsetLocalMatrix;
		}
		/*!
		 *@brief	���O�̎擾�B
		 */
		const wchar_t* GetName() const
		{
			return m_boneName.c_str();
		}
		/*!
		*@brief	���̃{�[���̃��[���h��Ԃł̈ʒu�Ɖ�]�ƃX�P�[�����v�Z����B
		*@param[out]	trans		���s�ړ��ʂ̊i�[��B
		*@param[out]	rot			��]�ʂ̊i�[��B
		*@param[out]	scale		�g�嗦�̊i�[��B
		*/
		void CalcWorldTRS(CVector3& trans, CQuaternion& rot, CVector3& scale);
		
	private:
	
		std::wstring	m_boneName;
		int				m_parentId = -1;	//!<�e�̃{�[���ԍ��B
		int				m_boneId = -1;		//!<�{�[���ԍ��B
		CMatrix			m_bindPose;		//!<�o�C���h�|�[�Y�B
		CMatrix			m_invBindPose;	//!<�o�C���h�|�[�Y�̋t�s��B
		CMatrix			m_localMatrix = CMatrix::Identity;	//!<���[�J���s��B
		CMatrix			m_worldMatrix = CMatrix::Identity;	//!<���[���h�s��B
		CMatrix			m_offsetLocalMatrix;
		CVector3		m_positoin = CVector3::Zero;		//!<���̃{�[���̃��[���h��Ԃł̈ʒu�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
		CVector3		m_scale = CVector3::One;			//!<���̃{�[���̊g�嗦�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
		CQuaternion		m_rotation = CQuaternion::Identity;	//!<���̃{�[���̉�]�B�Ō��CalcWorldTRS�����s�����Ƃ��̌��ʂ��i�[����Ă���B
		std::list<CBone*>	m_children;		//!<�q���B
	};
	/*!
	 *@brief	�X�P���g���B
	 */
	class CSkeleton : Noncopyable {
	public:
		using OnPostProcessSkeletonUpdate = std::function<void()>;

		CSkeleton();
		~CSkeleton();
		
		/*!
		 *@brief	�{�[���̃��[�J���s���ݒ�B
		 *@param[in]	boneNo		�{�[���ԍ�
		 *@param[in]	m			�s��B
		 */
		void SetBoneLocalMatrix(int boneNo, const CMatrix& m)
		{
			if (boneNo > (int)m_bones.size() - 1) {
				TK_WARNING("boneNo is over m_bones.size() ");
				return;
			}
			m_bones[boneNo]->SetLocalMatrix(m);
		}
		/*!
		 *@brief	�{�[���̐����擾�B
		 */
		int GetNumBones() const
		{
			return static_cast<int>(m_bones.size());
		}
		/*!
		*@brief	���[�h�B
		*@param[in]	filePath	�t�@�C���p�X�B
		*/
		bool Load(const wchar_t* filePath);
		/*!
		 *@brief	�{�[���̖��O����{�[��ID�������B
		 */
		int FindBoneID(const wchar_t* boneName) const
		{
			for (int i = 0; i < (int)m_bones.size(); i++) {
				if (wcscmp(m_bones[i]->GetName(), boneName) == 0) {
					return i;
				}
			}
			//������Ȃ������B
			return -1;
		}
		/*!
		*@brief	�{�[�����擾�B
		*/
		CBone* GetBone(int boneNo) const
		{
			return m_bones[boneNo].get();
		}
	public:
		
		/*!
		 *@brief	�X�V�B
		 */
		void Update(const CMatrix& mWorld);
		/*!
		 *@brief	�`�揈������Ă΂�鏈���B
		 */
		void Render(CRenderContext& rc);
		/*!
		*@brief	�X�P���g���̍X�V���I��������ɌĂ΂��R�[���o�b�N�֐���ǉ��B
		*/
		void SetAnimation(CAnimation*  anim)
		{
			m_animation = anim;
		}
		/*!
		*@brief	�{�[���̃��[���h�s��̍X�V�֐��B
		*@details
		* �ʏ�̓��[�U�[�����̊֐����Ăяo���K�v�͂���܂���B
		*@param[in]	bone		�X�V����{�[���B
		*@param[in]	parentMatrix	�e�̃{�[���̃��[���h�s��B
		*/
		static 	void UpdateBoneWorldMatrix(CBone& bone, const CMatrix& parentMatrix);
	private:
		/*!
		*@brief	���ׂł̃{�[���̒ǉ������������Ƃ��ɌĂяo���K�v�����鏈���B
		*/
		void OnCompleteAddedAllBones();
	private:

		static const int BONE_MAX = 512;	//!<�{�[���̍ő吔�B
		typedef std::unique_ptr<CBone>	CBonePtr;
		std::vector<CBonePtr>	m_bones;	//!<�{�[���̔z��B
		std::unique_ptr<CMatrix[]>	m_boneMatrixs;	//!<�{�[���s��B
		CStructuredBuffer			m_boneMatrixSB;	//!<�{�[���s��̃X�g���N�`���[�o�b�t�@�B
		CAnimation*					m_animation = nullptr;	//!<���̃X�P���g���𓮂����Ă���A�j���[�V�����B
	};
}