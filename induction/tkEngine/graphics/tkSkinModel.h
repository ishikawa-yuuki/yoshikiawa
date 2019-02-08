/*!
 *@brief	�X�L�����f���B
 */

#pragma once

#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "tkEngine/math/tkBox.h"

namespace tkEngine{
	class CSkinModelData;
	/*!
	*@brief	FBX�̏�����B
	*/
	enum EnFbxUpAxis {
		enFbxUpAxisY,		//Y-up
		enFbxUpAxisZ,		//Z-up
	};
	/*!
	 *@brief	�X�L�����f���B
	 *@details
	 * �X�L������A�Ȃ����f���̕\�����T�|�[�g����N���X�B</br>
	 * �����̃C���X�^���X����x�̊֐��R�[���ŕ`�悷�邱�Ƃ��ł���C���X�^���V���O�`����T�|�[�g���Ă���B</br>
	 */
	class CSkinModel : Noncopyable{
	public:
		//�`����s���O�ɌĂ΂��֐��I�u�W�F�N�g�̌^�B
		using OnDrawFookFunction = std::function<void(CRenderContext&, CSkinModel&)>;
		
		typedef std::function<void(CSkeleton&)>		OnPostUpdateSkeleton;

		/*!
		*@brief QueryEffects�����s�����Ƃ��̃R�[���o�b�N�ɓn���������\���́B
		*/
		struct SQuerryEffectsCbArg {
			DirectX::ModelMeshPart*	meshPart;		//���݂̃G�t�F�N�g�B
		};
		CSkinModel();
		~CSkinModel();
		/*!
		*@brief	������
		*@param[in]	modelData		���f���f�[�^�B
		*@param[in] maxInstance		�C���X�^���X�̍ő吔�B1���傫���ꍇ�C���X�^���V���O�`�悪�s���܂��B
		*							�C���X�^���V���O�`����s���ꍇ�́AUpdateInstance�֐����g�p���āA
		*							�C���X�^���X�ŗL�̃f�[�^���X�V����K�v������܂��B
		*/
		void Init(CSkinModelData& modelData, int maxInstance = 1);
		/*!
		*@brief	�X�V�B
		*@details
		* �ʏ�`��̏ꍇ�̍s��X�V�͂�������g�p����B
		* �C���X�^���V���O�`��̏ꍇ��UpdateInstancingData���g�p����B
		*@param[in]		trans		���s�ړ��B
		*@param[in]		rot			��]�B
		*@param[in]		scale		�g��B
		*@param[in]		enUpdateAxis	fbx�̏�����B
		*@param[in]		isForwardRender	�t�H���[�h�����_�����O���s���H
		*/
		void Update(
			const CVector3& trans, 
			const CQuaternion& rot, 
			const CVector3& scale,
			EnFbxUpAxis enUpdateAxis = enFbxUpAxisZ,
			bool isForwardRender = false
		);
		/*!
		 *@brief	�C���X�^���V���O�p�̃f�[�^�̍X�V�B
		 *@details
		 * �C���X�^���V���O�`��̏ꍇ�̍s��X�V�͂�������g�p����B
		 * �S�ẴC���X�^���X�̍s��X�V�����������̂��APostUpadteInstancingData���Ăяo���悤�ɁB
		 *@param[in]		trans		���s�ړ��B
		 *@param[in]		rot			��]�B
		 *@param[in]		scale		�g��B
		 *@param[in]		enUpdateAxis	fbx�̏�����B
		 */
		void UpdateInstancingData(
			const CVector3& trans,
			const CQuaternion& rot,
			const CVector3& scale,
			EnFbxUpAxis enUpdateAxis = enFbxUpAxisZ
		);
		/*!
		*@brief	�C���X�^���X�f�[�^�̍X�V�J�n���ɌĂяo���Ă��������B
		*/
		void BeginUpdateInstancingData()
		{
			if (m_maxInstance > 1) {
				m_numInstance = 0;
			}
		}
		/*!
		 *@brief	�S�ẴC���X�^���X�f�[�^�̍X�V�I�������Ăяo���Ă��������B
		 *@param[in]		isForwardRender	�t�H���[�h�����_�����O���s���H
		 */
		void EndUpdateInstancingData(bool isForwardRender = false);
		/*!
		*@brief	�`��
		*@param[in] renderContext	�����_�����O�R���e�L�X�g�B
		*/
		void Draw(CRenderContext& renderContext);
		/*!
		*@brief	�`��
		*@param[in] renderContext	�����_�����O�R���e�L�X�g�B
		*@param[in]	viewMatrix		�r���[�s��B
		*@param[in]	projMatrix		�v���W�F�N�V�����s��B
		*/
		void Draw(
			CRenderContext& renderContext, 
			const CMatrix& viewMatrix, 
			const CMatrix& projMatrix
		);
		/*!
		*@brief	���b�V���̌����B
		*@param[in]	findMesh		���b�V�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMesh(CSkinModelData::OnFindMesh findMesh) const
		{
			if (m_skinModelData != nullptr) {
				m_skinModelData->FindMesh(findMesh);
			}
		}
		/*!
		*@brief	���f���}�e���A���̌����B
		*@param[in]	findEffect		�}�e���A�������������ɌĂ΂��R�[���o�b�N�֐�
		*/
		void FindMaterial(std::function<void(CModelEffect*)> findMaterial) const
		{
			FindMesh([&](auto& mesh) {
				CModelEffect* effect = reinterpret_cast<CModelEffect*>(mesh->effect.get());
				findMaterial(effect);
			});
		}
		/*!
		* @brief	�V���h�E�L���X�^�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E�L���X�^�[�̃t���O�B
		*/
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}
		/*!
		* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
		*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
		*/
		void SetShadowReceiverFlag(bool flag)
		{
			m_isShadowReceiver = flag;
		}
		/*!
		 *@brief	���[���h�s����擾�B
		 */
		const CMatrix& GetWorldMatrix() const
		{
			return m_worldMatrix;
		}
		/*!
		*@brief	�X�L�����f���f�[�^���擾�B
		*/
		CSkinModelData* GetSkinModelData() const
		{
			return m_skinModelData;
		}
		/*!
		*@brief	�A�j���[�V������ݒ�B
		*@details
		* �G���W�������Ŏg�p����Ă��܂��B���[�U�[�͎g�p���Ȃ��ł��������B
		*/
		void SetAnimation(CAnimation* animation)
		{
			m_animation = animation;
		}
		void UpdateBoundingBox(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, EnFbxUpAxis enUpdateAxis = enFbxUpAxisZ)
		{
			CMatrix mWorld;
			CMatrix mBias = CMatrix::Identity;
			if (enUpdateAxis == enFbxUpAxisZ) {
				//Z-up
				mBias.MakeRotationX(CMath::PI * -0.5f);
			}
			CMatrix mScale, mTrans, mRot;
			mScale.MakeScaling(scale);
			mRot.MakeRotationFromQuaternion(rot);
			mRot = mBias * mRot;
			mTrans.MakeTranslation(trans);
			mWorld = mScale * mRot;
			mWorld = mWorld * mTrans;

			m_boundingBox.Update(mWorld);
		}
		/*!
		*@brief	�o�E���f�B���O�{�b�N�X�̍X�V�B
		*/
		void UpdateBoundingBox()
		{
			m_boundingBox.Update(m_worldMatrix);
		}
		/*!
		*@brief	�o�E���f�B���O�{�b�N�X�B
		*/
		CBox& GetBoundingBox()
		{
			return m_boundingBox;
		}
		/*!
		* @brief	�`��R�[�����s�̒��O�Ƀt�b�N�������֐���ݒ肷��B
		*param[in]	func	�t�b�N�֐��B
		*@code
			//�T���v���R�[�h
			skinModelRender->SetPreDrawFookFunction([&]( CRenderContext& rc, CSkinModel& model){
				printf("�`��R�[���̒��O�ɌĂ΂���");
			});
		*@endcode
		*/
		void SetPreDrawFookFunction(std::function<void(CRenderContext&, CSkinModel&)> func)
		{
			m_preDrawFookFunction = func;
		}
		/*!
		* @brief	�`��R�[�����s�̒���Ƀt�b�N�������֐���ݒ肷��B
		*param[in]	func	�t�b�N�֐��B
		*@code
			//�T���v���R�[�h
			skinModelRender->SetPreDrawFookFunction([&]( CRenderContext& rc, CSkinModel& model){
				printf("�`��R�[���̒���ɌĂ΂���");
			});
		*@endcode
		*/
		void SetPostDrawFookFunction(OnDrawFookFunction func)
		{
			m_postDrawFookFunction = func;
		}
		/// <summary>
		/// ���Ȕ����F��ݒ�B
		/// </summary>
		/// <param name="color">���Ȕ����F</param>
		void SetEmissionColor(CVector3 color)
		{
			m_emissionColor = color;
		}
		/// <summary>
		/// �V���h�E�L���X�^�[���擾�B
		/// </summary>
		/// <returns>�V���h�E�L���X�^�[�̎Q��</returns>
		CShadowCaster_SkinModel& GetShadowCaster()
		{
			return m_shadowCaster;
		}
	private:
		/*!
		*@brief �o�E���f�B���O�{�b�N�X�̏������B
		*/
		void InitBoudingBox();
		/*!
		 *@brief	���[���h�s��̍X�V�B
		 */
		void UpdateWorldMatrix(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, EnFbxUpAxis enUpdateAxis);
	private:
		/*!
		 *@brief	���_�V�F�[�_�[�Ŏg�p����萔�o�b�t�@�p�̍\���́B
		 */
		struct SVSConstantBuffer {
			CMatrix mWorld;			//!<���[���h�s��B
			CMatrix mView;			//!<�r���[�s��B
			CMatrix mProj;			//!<�v���W�F�N�V�����s��B
			CVector3 emissionColor;	//!<���Ȕ����F�B
			int isShadowReceiver;	//!<�V���h�E���V�[�o�[�t���O�B
		};
		CAnimation* m_animation = nullptr;						//!<�A�j���[�V�����Đ������B
		CSkinModelData*	m_skinModelData = nullptr;				//!<�X�L�����f���f�[�^�B
		CMatrix m_worldMatrix = CMatrix::Identity;				//!<���[���h�s��B
		CConstantBuffer m_cb;									//!<�萔�o�b�t�@�B
		CShadowCaster_SkinModel m_shadowCaster;					//!<�V���h�E�L���X�^�[�B
		bool m_isShadowCaster = false;							//!<�V���h�E�L���X�^�[�H
		bool m_isShadowReceiver = false;						//!<�V���h�E���V�[�o�[�H
		std::unique_ptr<CMatrix[]>	m_instancingData;			//!<�C���X�^���V���O�`��p�̃f�[�^�B
		CStructuredBuffer	m_instancingDataSB;					//!<�C���X�^���V���O�`��p�̃X�g���N�`���[�o�b�t�@�B
		int m_maxInstance = 1;									//!<�C���X�^���X�̍ő吔
		int m_numInstance = 0;									//!<�C���X�^���X�̐��B
		CBox m_boundingBox;										//!<�o�E���f�B���O�{�b�N�X�B
		OnDrawFookFunction m_preDrawFookFunction = nullptr;		//�`��̒��O�ɌĂ΂��t�b�N�֐��B
		OnDrawFookFunction m_postDrawFookFunction = nullptr;	//�`�悪�I�������ŌĂ΂��t�b�N�֐��B
		CVector3 m_emissionColor = CVector3::Zero;				//���Ȕ����J���[�B
	};
}