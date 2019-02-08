/*!
 *@brief	FootIK
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/animation/postProcess/tkAnimationFootIK.h"
#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine{
	namespace {
		//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�n�ʗp)
		struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
		{
			bool isHit = false;									//�Փ˃t���O�B
			CVector3 hitPos = CVector3(0.0f, -FLT_MAX, 0.0f);	//�Փ˓_�B
			CVector3 startPos = CVector3::Zero;					//���C�̎n�_�B
			float dist = FLT_MAX;								//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B

																//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
			virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				if (convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character) {
					//�L�����N�^�����̃R���W�����ƏՓ˂����B
					return 0.0f;
				}
				//�Փ˓_�̖@�������������Ă���B
				CVector3 hitNormalTmp = *(CVector3*)&convexResult.m_hitNormalLocal;
				//������Ɩ@���̂Ȃ��p�x�����߂�B
				float angle = hitNormalTmp.Dot(CVector3::Up);
				angle = fabsf(acosf(angle));
				if (angle < CMath::PI * 0.3f		//�n�ʂ̌X�΂�54�x��菬�����̂Œn�ʂƂ݂Ȃ��B
					|| convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground //�������̓R���W�����������n�ʂƎw�肳��Ă���B
					) {
					//�Փ˂��Ă���B
					isHit = true;
					CVector3 hitPosTmp = *(CVector3*)&convexResult.m_hitPointLocal;
					//�Փ˓_�̋��������߂�B�B
					CVector3 vDist;
					vDist.Subtract(hitPosTmp, startPos);
					float distTmp = vDist.Length();
					if (dist > distTmp) {
						//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
						hitPos = hitPosTmp;
						dist = distTmp;
					}
				}
				return 0.0f;
			}
		};

	}
	CAnimationFootIK::CAnimationFootIK()
	{
	}
	CAnimationFootIK::~CAnimationFootIK()
	{
	}
	
	bool CAnimationFootIK::CalcIKTargetPosition(const SFoot& foot, CVector3& targetPosition)
	{
		//�G�t�F�N�^�̐e�̍��W����A�R���C�_�[�̈ʒu�����߂�B
		if (foot.m_bone->GetParentId() == -1) {
			//�^�[�Q�b�g�͌�����Ȃ������B�B
			return false;
		}
		CMatrix m = foot.m_bone->GetWorldMatrix();
		CVector3 effectorPos = { m.m[3][0], m.m[3][1], m.m[3][2] };

		//���C���쐬����B
		btTransform btRayStart, btRayEnd;
		btRayStart.setIdentity();
		btRayEnd.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S�B
		btRayStart.setOrigin({ effectorPos.x, effectorPos.y, effectorPos.z });
		//10cm���Ɍ����ă��C���΂��B
		btRayEnd.setOrigin(
		{ 
			effectorPos.x,
			effectorPos.y - UnitCM(5.0f),
			effectorPos.z
		});

		SweepResultGround callback;
		callback.startPos.Set(btRayStart.getOrigin());
		PhysicsWorld().ConvexSweepTest((const btConvexShape*)foot.m_collider.GetBody(), btRayStart, btRayEnd, callback);
		if (callback.isHit == false) {
			return false;
		}
		targetPosition = callback.hitPos;
		//�G�t�F�N�^�\�Ƃ̋����𒲂ׂ�B
		CVector3 diff = targetPosition - effectorPos;
		if (diff.LengthSq() < 0.01f) {
			//�G�t�F�N�^�\�ƖڕW���W���߂����邒�B
			return false;
		}
		return true;
	}
	void CAnimationFootIK::Init(CSkeleton* skeleton)
	{
		m_skeleton = skeleton;
	}
	
	void CAnimationFootIK::Enable(const SFootIKParam& param)
	{
		m_isEnable = true;
		int boneId = m_skeleton->FindBoneID(param.footBoneName_0);
		m_foots[0].m_bone = m_skeleton->GetBone(boneId);
		m_foots[0].m_collider.Create(param.footCapsuleColliderRadius_0, param.footCapsuleColliderHeight_0);
		
		boneId = m_skeleton->FindBoneID(param.footBoneName_1);
		m_foots[1].m_bone = m_skeleton->GetBone(boneId);
		m_foots[1].m_collider.Create(param.footCapsuleColliderRadius_1, param.footCapsuleColliderHeight_1);

		m_rootBoneId = m_skeleton->FindBoneID(param.rootBoneName);
	}
	void CAnimationFootIK::SolverCCD_IK(const SFoot& foot, CVector3 targetPosition)
	{
		//�����B�T��v�Z����B
		const int iteration = 1;
		for (int i = 0; i < iteration; i++) {
			int parentId = foot.m_bone->GetParentId();
			CMatrix m = foot.m_bone->GetWorldMatrix();
			CVector3 effectorPos = { m.m[3][0], m.m[3][1], m.m[3][2] };
			CBone* currentBone = nullptr;
			while (parentId != m_rootBoneId) {
				currentBone = m_skeleton->GetBone(parentId);
				CMatrix m = currentBone->GetWorldMatrix();
				CVector3 currentBonePos = {m.m[3][0], m.m[3][1], m.m[3][2]};
				//
				CVector3 toEffectorPos = effectorPos - currentBonePos;
				toEffectorPos.Normalize();
				CVector3 toTargetPos = targetPosition - currentBonePos;
				toTargetPos.Normalize();
				//��]�������߂�B
				CVector3 rotateAxis;
				rotateAxis.Cross(toEffectorPos, toTargetPos);
				rotateAxis.Normalize();

				//�K���ʒu�ɍ��킹�邽�߂̉�]�s������߂�B
				float angle = acos(min(1.0f, toEffectorPos.Dot(toTargetPos)));
				CQuaternion qRot;
				qRot.SetRotation(rotateAxis, angle);
				CMatrix mAddRot;
				mAddRot.MakeRotationFromQuaternion(qRot);
				//��]�s�񂪂ł����̂ŁA���[���h�ɔ��f�B
				m.m[3][0] = 0.0f;
				m.m[3][1] = 0.0f;
				m.m[3][2] = 0.0f;
				//�ǉ��̉�]��������B
				m = m * mAddRot;
				m.m[3][0] = currentBonePos.x;
				m.m[3][1] = currentBonePos.y;
				m.m[3][2] = currentBonePos.z;
				
				//���[�J���s������߂�B
				CMatrix localMat;
				parentId = currentBone->GetParentId();
				if (parentId != -1) {
					CMatrix toParentSpaceMatrix = m_skeleton->GetBone(parentId)->GetWorldMatrix();
					toParentSpaceMatrix.Inverse();
					localMat = m * toParentSpaceMatrix;
					parentId = currentBone->GetParentId();
					currentBone->SetLocalMatrix(localMat);
				}
			}
			//���[�g�{�[�����牺�̍��̃��[���h�s��̍Čv�Z���s���B
			CSkeleton::UpdateBoneWorldMatrix(*currentBone, m_skeleton->GetBone(m_rootBoneId)->GetWorldMatrix());
		}
	}
	void CAnimationFootIK::SolverPIK(const SFoot& foot, CVector3 targetPosition)
	{
		//�֐߂Ƀp�[�e�B�N����u���Ă����B
		
	}
	void CAnimationFootIK::Update()
	{
		if (m_isEnable == false) {
			//FootIK�������B
			return;
		}
		for (auto& foot : m_foots) {
			//�G�t�F�N�^�̖ڕW���W�����߂�B
			CVector3 targetPosition;
			if (CalcIKTargetPosition(foot, targetPosition) == false) {
				//�ڕW���W�����܂�Ȃ������B
				continue;
			}
#if 0
			//CCD-IK�@���g�p����IK
			SolverCCD_IK(foot, targetPosition);
#else
			//PIK���g�p����IK
			SolverPIK(foot, targetPosition);
#endif
		}
	}
}