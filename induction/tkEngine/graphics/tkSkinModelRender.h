/*!
 * @brief	�X�L�����f�������_���[
 */

#pragma once

#include "tkEngine/culling/tkObjectFrustumCulling.h"

namespace tkEngine{
namespace prefab{
	/*!
	 * @brief	3D���f����\������@�\��񋟂���N���X�B
	 *@details
	 * ���̃N���X��IGameObject���p�����Ă��邽�߁ANewGO���g�p���āA\n
	 * �C���X�^���X�𐶐�����K�v������܂��B\n
	 * �C���X�^���X���s�v�ɂȂ�����DeleteGO���g�p���Ĕj�����Ă��������B
	 *@code
		
		//�C���X�^���X�𐶐��`�G���o���܂ł̃T���v���R�[�h�B
		//�܂���NewGO�����s�B
		prefab::CSkinModelRender* render = NewGO<prefab::CSkinModelRender>(0);

		//�����ăt�@�C���p�X���w�肵�ă��[�h����΁A�ȍ~�̃t���[����3D���f�����\�������悤�ɂȂ�܂��B
		render->Init( L"modelData/test.cmo" );

	 *@endcode
	 */
	class CSkinModelRender : public IGameObject {
	public:
		
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSkinModelRender() {}
		/// <summary>
		/// DeleteGO�����s���ꂽ�Ƃ��ɌĂ΂��B
		/// </summary>
		void OnDestroy() override;
		/*!
		* @brief	�������B
		*@param[in]	filePath			���[�h������cmo�t�@�C���̃t�@�C���p�X�B
		*@param[in]	animationClips		�A�j���[�V�����N���b�v�̔z��̐擪�A�h���X
		*@param[in]	numAnimClip			�A�j���[�V�����N���b�v�̐�
		*@param[in]	enUpdateAxis		fbx�̏�����B
		*@param[in] maxInstance			�C���X�^���X�̐��B�C���X�^���V���O���s�������ꍇ�Ɏw�肵�Ă��������B
		*/
		void Init(const wchar_t* filePath,
			CAnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnFbxUpAxis fbxUpAxis = enFbxUpAxisZ,
			int maxInstance = 1 );
		
		/*!
		*@brief	�`��̒��O�ɌĂяo�����t�b�N�֐��I�u�W�F�N�g��ݒ肷��B
		*@details
		* �`��̒��O�ɓ���ȏ������s�������ꍇ�Ɏg�p���Ă��������B
		*@param[in]	func	�t�b�N�֐��I�u�W�F�N�g�B
		*@code
			//�T���v���R�[�h
			skinModelRender->SetPreDrawFookFunction([&]( CRenderContext& rc, CSkinModel& model){
				printf("�`��R�[���̒��O�ɌĂ΂���");
			});
		*@endcode
		*/
		void SetPreDrawFookFunction(CSkinModel::OnDrawFookFunction func)
		{
			m_skinModel.SetPreDrawFookFunction(func);
		}
		/*!
		*@brief	�`�悪�I�������Ƀt�b�N�������֐���ݒ肷��B
		*@details
		* �`��̒���ɓ���ȏ������s�������ꍇ�Ɏg�p���Ă��������B
		*@param[in]	func	�t�b�N�֐��B�� void Fook(CRenderContext& rc, CSkinModel& model);
		*@code
			//�T���v���R�[�h
			skinModelRender->SetPostDrawFookFunction([&]( CRenderContext& rc, CSkinModel& model){
				printf("�`��R�[���̒���ɌĂ΂���");
			});
		*@endcode
		*/
		void SetPostDrawFookFunction(CSkinModel::OnDrawFookFunction func)
		{
			m_skinModel.SetPostDrawFookFunction(func);
		}
	
		/*!
		* @brief	�A�j���[�V�������Đ��B
		*@param[in]	clipNo	�A�j���[�V�����N���b�v�̔ԍ��B�R���X�g���N�^�ɓn����animClipList�̕��тƂȂ�B
		*@param[in]	interpolateTime		�⊮����(�P�ʁF�b)
		*/
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/*!
		* @brief	�A�j���[�V�����̍Đ����H
		*@retval	true		�A�j���[�V�������Đ����B
		*@retval	false		�A�j���[�V�����͍Đ����Ă��Ȃ��B
		*/
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/*!
		* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
	    * @details
		* �V���h�E�L���X�^�[�Ƃ́A�e�𗎂Ƃ����̃��f���̂��Ƃł��B\n
		* �Ⴆ�΁A�v���C���[�̉e��n�ʂɗ��Ƃ������ꍇ��\n
		* �v���C���[�̓V���h�E�L���X�^�[�ƂȂ�܂��B
		*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
		*@details
		*���̈�����true���n���ꂽ�ꍇ�A���̃C���X�^���X���`�悷�郂�f���̓V���h�E�L���X�^�[�ɂȂ�܂��B
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_skinModel.SetShadowCasterFlag(flag);
		}
		/*!
		* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
		* @details
		* �V���h�E�L���X�^�[�Ƃ́A�e�𗎂Ƃ���鑤�̃��f���̂��Ƃł��B\n
		* �Ⴆ�΁A�v���C���[�̉e��n�ʂɗ��Ƃ������ꍇ��\n
		* �n�ʂ͂̓V���h�E���V�[�o�[�ƂȂ�܂��B
		*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
		*@details
		*���̈�����true���n���ꂽ�ꍇ�A���̃C���X�^���X���`�悷�郂�f���̓V���h�E���V�[�o�[�ɂȂ�܂��B
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_skinModel.SetShadowReceiverFlag(flag);
		}
		/*!
		* @brief	���Ȕ����F��ݒ�B
		*@param[in]	color	���Ȕ����F�B
		*/
		void SetEmissionColor(CVector3 color)
		{
			m_skinModel.SetEmissionColor(color);
		}
		/*!
		*@brief	�t���[�Y�����Ă���{�[���̕��s�ړ��ʂ��擾�B
		*/
		CVector3 GetFreezeBoneTranslate() const
		{
			return m_animation.GetFreezeBoneTranslate();
		}
		/*!
		*@brief	�A�j���[�V�����C�x���g���Ď�����֐���o�^�B
		*@details
		* �A�j���[�V�����C�x���g���ł����܂ꂽ�t���[���܂ŃA�j���[�V������\n
		* �Đ�����ƁA�o�^����Ă���֐����Ăяo����܂��B
		*@param[in]		eventListener		�C�x���g���Ď�����֐��I�u�W�F�N�g�B
		*/
		void AddAnimationEventListener(std::function<void(const wchar_t* clipName, const wchar_t* eventName)> eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}
		/*!
		*@brief	���W��ݒ�B
		*@details
		* 3D���f����\�����������[���h���W���w�肵�Ă��������B
		*@param[in]	position		���[���h���W�B
		*/
		void SetPosition(const CVector3& position)
		{
			m_position = position;
		}
		/*!
		*@brief	��]��ݒ�B
		*@details
		* 3D���f���̃��[���h��Ԃł̉�]��\���A�N�H�[�^�j�I�����w�肵�Ă��������B
		*@param[in]	rotation		���[���h��Ԃł̉�]�N�H�[�^�j�I���B
		*/
		void SetRotation(const CQuaternion& rotation)
		{
			m_rotation = rotation;
		}
		/*!
		*@brief	�g�嗦��ݒ�B
		*@details
		* 3D���f���̃��[���h��Ԃł̊g�嗦���w�肵�Ă��������B
		*@param[in] scale			���[���h��Ԃł̊g�嗦�B( 1, 1, 1 )�œ��{�B
		*/
		void SetScale(const CVector3& scale)
		{
			m_scale = scale;
		}
		/*!
		*@brief	���[���h��Ԃł̍��W�A��]�A�g������ׂĐݒ�
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in] scale		�g��B
		*/
		void SetPRS(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
		{
			SetPosition(trans);
			SetRotation(rot);
			SetScale(scale);
		}
		/*!
		*@brief	�C���X�^���V���O�f�[�^���X�V�B
		*@details
		* �C���X���^�V���O�`����s���Ă���ꍇ�́A���̊֐����g����\n
		* ���[���h��Ԃł̍��W�A��]�A�g����w�肵�Ă��������B\n
		* �Ⴆ�΁A100�̂ŃC���X�^���V���O�`����s���Ă���ꍇ��\n
		* �P�t���[����100��A���̊֐����Ăяo���K�v������܂��B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in] scale		�g��B
		*/
		void UpdateInstancingData(const CVector3& trans, const CQuaternion& rot, const CVector3& scale)
		{
			m_skinModel.UpdateInstancingData(trans, rot, scale);
		}
		/*!
		*@brief	�X�L�����f���f�[�^���擾�B
		*@return	�X�L�����f���f�[�^�B
		*/
		CSkinModelData& GetSkinModelData() 
		{
			return m_skinModelData;
		}
		/*!
		*@brief	�X�L�����f���f�[�^���擾�Bconst�Q�ƔŁB
		*@return	�X�L�����f���f�[�^�B
		*/
		const CSkinModelData& GetSkinModelData() const
		{
			return m_skinModelData;
		}
		/*!
		*@brief	�X�L�����f���擾�B
		*@return	�X�L�����f���B
		*/
		CSkinModel& GetSkinModel()
		{
			return m_skinModel;
		}
		/*!
		*@brief	�X�L�����f���擾�Bconst�Q�ƔŁB
		*@return	�X�L�����f���B
		*/
		const CSkinModel& GetSkinModel() const
		{
			return m_skinModel;
		}
		/*!
		*@brief	������J�����O���s�����ǂ����̃t���O��ݒ�B
		*@details
		* ���̃t���O��true�ɂ���Ɖ�ʂɉf���Ă��Ȃ��I�u�W�F�N�g�͕\������Ȃ��Ȃ�܂��B
		*/
		void SetFrustumCulling(bool flag)
		{
			m_isFrustumCulling = flag;
		}
		/*!
		*@brief	���f���}�e���A���̌����B
		*@param[in]	findEffect		�}�e���A�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMaterial(std::function<void(CModelEffect*)> findMaterial) const
		{
			m_skinModel.FindMaterial(findMaterial);
		}
		/*!
		*@brief	�A�j���[�V�����̍X�V�t���O��ݒ�B
		*@param flag	�X�V�t���O
		*@details
		*���̃t���O��false��ݒ肷��ƁA�A�j���[�V�����̍Đ����~�܂�܂��B
		*/
		void SetUpdateAnimationFlag(bool flag)
		{
			m_isUpdateAnimation = flag;
		}
		/*!
		*@brief	�t�H���[�h�����_�����O�̃t���O��ݒ�B
		*@details
		* �t���O�𗧂Ă�ƃt�H���[�h�����_�����O���s���܂��B
		* �����x�[�X�����_�����O�ȊO�̓���ȃ����_�����O���s�������ꍇ�͗L���ɂ��Ă��������B
		*/
		void SetForwardRenderFlag(bool flag)
		{
			m_isForwardRender = flag;
		}
		void FindVertexPosition(std::function<void(CVector3* pos)>);
		/*!
		*@brief	�{�[������������B
		*@param[in]	boneName	�{�[���̖��O�B
		*@return	���������{�[���̃A�h���X�B������Ȃ������ꍇ��nullptr��Ԃ��܂��B
		*@details
		* ���̊֐��͌������s�����߁A�������d���ł��B
		* Update�֐��ȂǂŖ��t���[���Ăяo���̂ł͂Ȃ��A
		* �������֐��ȂǂŁA�N���X�̃����o�ϐ��ɃL���b�V������̂��I�X�X�����܂��B
		*/
		CBone* FindBone(const wchar_t* boneName) const
		{
			const auto& skeleton = m_skinModelData.GetSkeleton();
			auto boneId = skeleton.FindBoneID(boneName);
			if (boneId != -1) {
				return skeleton.GetBone(boneId);
			}
			return nullptr;

		}
	private:
		void ForwardRender(CRenderContext& rc) override final;
		/*!
		* @brief	�X�V�O�ɌĂ΂��֐��B
		*/
		bool Start() override final;
		/*!
		* @brief	���O�X�V�B
		*/
		void PreUpdate() override final
		{
			if (m_skinModelData.IsAvailable() == true) {
				m_skinModel.BeginUpdateInstancingData();
			}
		}
		/*!
		* @brief	�X�V�B
		*/
		void Update() override final;
		/*!
		* @brief	�x���X�V�B
		*/
		void PostUpdate() override final
		{
			if (m_skinModelData.IsAvailable() == true) {
				m_skinModel.EndUpdateInstancingData();
			}
		}
		
		/*!
		* @brief	�A�j���[�V�����̏������B
		*/
		void InitAnimation(CAnimationClip* animationClips, int numAnimationClips);
	private:
		bool						m_isForwardRender = false;		//!<�t�H���[�h�����_�����O�B
		CAnimationClip*				m_animationClips = nullptr;			//!<�A�j���[�V�����N���b�v�B
		int							m_numAnimationClips = 0;			//!<�A�j���[�V�����N���b�v�̐��B
		CVector3 					m_position = CVector3::Zero;		//!<���W�B
		CQuaternion	 				m_rotation = CQuaternion::Identity;	//!<��]�B
		CVector3					m_scale = CVector3::One;			//!<�g�嗦�B
		EnFbxUpAxis					m_enFbxUpAxis = enFbxUpAxisZ;		//!<FBX�̏�����B
		CAnimation					m_animation;						//!<�A�j���[�V�����B
		CSkinModel					m_skinModel;						//!<�X�L�����f���B
		CSkinModelData				m_skinModelData;					//!<�X�L�����f���f�[�^�B
		const std::wstring			m_filePath;							//!<�t�@�C���p�X�B
		bool						m_isFrustumCulling = false;			//!<�t���X�^���J�����O���s���H
		CObjectFrustumCulling		m_frustumCulling;					//!<�t���X�^���J�����O�B
		bool						m_isUpdateAnimation = true;			//!<�A�j���[�V�������X�V����H
	};
}
}