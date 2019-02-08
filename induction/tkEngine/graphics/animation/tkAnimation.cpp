/*!
 * @brief	�A�j���[�^�[�N���X�B
 */


#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimation.h"

namespace tkEngine{

	CAnimation::CAnimation()
	{
	}
	CAnimation::~CAnimation()
	{
		if (m_skeleton != nullptr) {
		}
	}
	
	void CAnimation::Init(CSkinModel& skinModel, CAnimationClip animClipList[], int numAnimClip)
	{
		TK_ASSERT(animClipList != nullptr, "animClipList��NULL�ł��B");
		m_skeleton = &skinModel.GetSkinModelData()->GetSkeleton();
		m_skeleton->SetAnimation(this);
		skinModel.SetAnimation(this);
		for (int i = 0; i < numAnimClip; i++) {
			m_animationClips.push_back(&animClipList[i]);
		}
		for (auto& ctr : m_animationPlayController) {
			ctr.Init(m_skeleton);
		}
		
		Play(0);
		m_footIK.Init(m_skeleton);
	}
	/*!
	 * @brief	���[�J���|�[�Y�̍X�V�B
	 */
	void CAnimation::UpdateLocalPose(float deltaTime)
	{
		m_interpolateTime += deltaTime;
		if (m_interpolateTime >= 1.0f) {
			//��Ԋ����B
			//���݂̍ŏI�A�j���[�V�����R���g���[���ւ̃C���f�b�N�X���J�n�C���f�b�N�X�ɂȂ�B
			m_startAnimationPlayController = GetLastAnimationControllerIndex();
			m_numAnimationPlayController = 1;
			m_interpolateTime = 1.0f;
		}
		for (int i = 0; i < m_numAnimationPlayController-1; i++) {
			int index = GetAnimationControllerIndex(m_startAnimationPlayController, i );
			m_animationPlayController[index].Update(deltaTime, this);
		}
		//�Ō�̃|�[�Y�����i�߂Ă����B
		int lastIndex = GetLastAnimationControllerIndex();
		m_animationPlayController[lastIndex].Update(deltaTime, this);
		
	}
	/*!
	 * @brief	�O���[�o���|�[�Y�̍X�V�B
	 */
	void CAnimation::UpdateGlobalPose()
	{
		//�O���[�o���|�[�Y�v�Z�p�̃��������X�^�b�N����m�ہB
		int numBone = m_skeleton->GetNumBones();
		CQuaternion* qGlobalPose = (CQuaternion*)alloca(sizeof(CQuaternion) * numBone);
		CVector3* vGlobalPose = (CVector3*)alloca(sizeof(CVector3) * numBone);
		CVector3* vGlobalScale = (CVector3*)alloca(sizeof(CVector3) * numBone);
		for (int i = 0; i < numBone; i++) {
			qGlobalPose[i] = CQuaternion::Identity;
			vGlobalPose[i] = CVector3::Zero;
			vGlobalScale[i] = CVector3::One;
		}
		//�O���[�o���|�[�Y���v�Z���Ă����B
		int startIndex = m_startAnimationPlayController;
		for (int i = 0; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			float intepolateRate = m_animationPlayController[index].GetInterpolateRate();
			const auto& localBoneMatrix = m_animationPlayController[index].GetBoneLocalMatrix();
			for (int boneNo = 0; boneNo < numBone; boneNo++) {
				//���s�ړ��̕⊮

				CMatrix m = localBoneMatrix[boneNo];
				vGlobalPose[boneNo].Lerp(
					intepolateRate, 
					vGlobalPose[boneNo], 
					*(CVector3*)m.m[3]
				);
				//���s�ړ��������폜�B
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;
				
				//�g�听���̕�ԁB
				CVector3 vBoneScale;
				vBoneScale.x = (*(CVector3*)m.m[0]).Length();
				vBoneScale.y = (*(CVector3*)m.m[1]).Length();
				vBoneScale.z = (*(CVector3*)m.m[2]).Length();

				vGlobalScale[boneNo].Lerp(
					intepolateRate,
					vGlobalScale[boneNo],
					vBoneScale
				);
				//�g�听���������B
				m.m[0][0] /= vBoneScale.x;
				m.m[0][1] /= vBoneScale.x;
				m.m[0][2] /= vBoneScale.x;

				m.m[1][0] /= vBoneScale.y;
				m.m[1][1] /= vBoneScale.y;
				m.m[1][2] /= vBoneScale.y;

				m.m[2][0] /= vBoneScale.z;
				m.m[2][1] /= vBoneScale.z;
				m.m[2][2] /= vBoneScale.z;

				//��]�̕⊮
				CQuaternion qBone;
				qBone.SetRotation(m);
				qGlobalPose[boneNo].Slerp(intepolateRate, qGlobalPose[boneNo], qBone);
			}
		}
		//�O���[�o���|�[�Y���X�P���g���ɔ��f�����Ă����B
		for (int boneNo = 0; boneNo < numBone; boneNo++) {
			
			//�g��s����쐬�B
			CMatrix scaleMatrix;
			scaleMatrix.MakeScaling(vGlobalScale[boneNo]);
			//��]�s����쐬�B
			CMatrix rotMatrix;
			rotMatrix.MakeRotationFromQuaternion(qGlobalPose[boneNo]);
			//���s�ړ��s����쐬�B
			CMatrix transMat;
			transMat.MakeTranslation(vGlobalPose[boneNo]);

			//�S�����������āA�{�[���s����쐬�B
			CMatrix boneMatrix;
			boneMatrix = scaleMatrix * rotMatrix;
			boneMatrix = boneMatrix * transMat;
			
			m_skeleton->SetBoneLocalMatrix(
				boneNo,
				boneMatrix
			);			
			
		}
		
		//�ŏI�A�j���[�V�����ȊO�͕�Ԋ������Ă����珜�����Ă����B
		int numAnimationPlayController = m_numAnimationPlayController;
		for (int i = 1; i < m_numAnimationPlayController; i++) {
			int index = GetAnimationControllerIndex(startIndex, i);
			if (m_animationPlayController[index].GetInterpolateRate() > 0.99999f) {
				//��Ԃ��I����Ă���̂ŃA�j���[�V�����̊J�n�ʒu��O�ɂ���B
				m_startAnimationPlayController = index;
				numAnimationPlayController = m_numAnimationPlayController - i;
			}
		}
		m_numAnimationPlayController = numAnimationPlayController;
	}
	
	void CAnimation::PostProcess()
	{
		//FootIK�����s�B
		m_footIK.Update();
	}
	
	void CAnimation::Update(float deltaTime)
	{
		if (m_numAnimationPlayController == 0) {
			return;
		}
		//���[�J���|�[�Y�̍X�V������Ă����B
		UpdateLocalPose(deltaTime);
		
		//�O���[�o���|�[�Y���v�Z���Ă����B
		UpdateGlobalPose();
	}
}