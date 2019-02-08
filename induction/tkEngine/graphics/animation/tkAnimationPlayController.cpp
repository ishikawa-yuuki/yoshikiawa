/*!
 * @brief	�A�j���[�V�����Đ��R���g���[���B
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationPlayController.h"


namespace tkEngine{
	
	
	void CAnimationPlayController::Init(CSkeleton* skeleton)
	{
		int numBones = skeleton->GetNumBones();
		//�{�[���s����o�V�b�Ɗm�ہB
		m_boneMatrix.resize(numBones);
		m_skeleton = skeleton;
	}
	
	void CAnimationPlayController::InvokeAnimationEvent(CAnimation* animation)
	{
		auto& animEventArray = m_animationClip->GetAnimationEvent();
		for( auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++){
			if (m_time > animEventArray[i].GetInvokeTime()
				&& animEventArray[i].IsInvoked() == false ) {
				//�A�j���[�V�����̋N�����Ԃ��߂��Ă��銎�A�܂��C�x���g�N�����Ă��Ȃ��B
				animation->NotifyAnimationEventToListener(
					m_animationClip->GetName(), animEventArray[i].GetEventName()
				);
				animEventArray[i].SetInvokedFlag(true);
			}
		}
	}
	
	void CAnimationPlayController::StartLoop()
	{
		m_currentKeyFrameNo = 0;
		m_time = 0.0f;
		//�A�j���[�V�����C�x���g�����ׂĖ������ɂ���B
		auto& animEventArray = m_animationClip->GetAnimationEvent();
		for (auto i = 0; i < m_animationClip->GetNumAnimationEvent(); i++) {
			animEventArray[i].SetInvokedFlag(false);
		}
	}
	void CAnimationPlayController::Update(float deltaTime, CAnimation* animation)
	{
		if(m_animationClip == nullptr){
			TK_WARNING("m_animationClip is nullptr\n");
			return ;
		}
		const auto& topBoneKeyFrameList = m_animationClip->GetTopBoneKeyFrameList();
		m_time += deltaTime;

		//�A�j���[�V�����C�x���g�̔����B
		InvokeAnimationEvent(animation);
		//�⊮���Ԃ��i�߂Ă����B
		m_interpolateTime = min(1.0f, m_interpolateTime + deltaTime);
		while (true) {
			if (m_currentKeyFrameNo >= (int)topBoneKeyFrameList.size()) {
				//�I�[�܂ōs�����B
				if (m_animationClip->IsLoop()) {
					//���[�v�B
					StartLoop();
				}
				else {
					//�����V���b�g�Đ��B
					m_currentKeyFrameNo--;
					m_isPlaying = false;	//�Đ��I���B
				}
				break;
			}
			if (topBoneKeyFrameList.at(m_currentKeyFrameNo)->time >= m_time) {
				//�I���B
				break;
			}
			//���ցB
			m_currentKeyFrameNo++;
		}
		//�{�[���s����v�Z���Ă����B
		const auto& keyFramePtrListArray = m_animationClip->GetKeyFramePtrListArray();
		for (const auto& keyFrameList : keyFramePtrListArray) {
			if (keyFrameList.size() == 0) {
				continue;
			}
			//���ݍĐ����̃L�[�t���[��������Ă���B
			Keyframe* keyframe = keyFrameList.at(m_currentKeyFrameNo);
			m_boneMatrix[keyframe->boneIndex] = keyframe->transform;
		}
		//�{�[�����t���[�Y�����鏈�����s���B
		ExecuteFreezeBone();
	}
	void CAnimationPlayController::ExecuteFreezeBone()
	{
		//�t���[�Y������{�[���ԍ����擾�B
		const CAnimationClip::SFreezeBoneInfo& freezeBoneInfo = m_animationClip->GetFreezeBoneInfo();
		
		if (freezeBoneInfo.boneNo == -1) {
			//�t���[�Y������{�[�����Ȃ��B
			return;
		}
		
		for (int boneNo = 0; boneNo < m_skeleton->GetNumBones(); boneNo++) {
			//�ړI�̃{�[���̃��[���h�s������߂�B
			CBone* bone = m_skeleton->GetBone(boneNo);
			if (bone->GetParentId() == -1) {
				//���[�g�{�[�����������B
				CMatrix freezeBoneWorldMatrix;
				CalcFreezeBoneWorldMatrix(*bone, CMatrix::Identity, freezeBoneWorldMatrix);
				m_freezeBoneTranslate = CVector3::Zero;
				if (freezeBoneInfo.freezeX) {
					//X���̈ړ����t���[�Y�B
					m_freezeBoneTranslate.x = freezeBoneWorldMatrix.m[3][0];
					m_boneMatrix[bone->GetNo()].m[3][0] -= freezeBoneWorldMatrix.m[3][0];
				}
				if (freezeBoneInfo.freezeY) {
					//Y���̈ړ����t���[�Y�B
					m_freezeBoneTranslate.y = freezeBoneWorldMatrix.m[3][1];
					m_boneMatrix[bone->GetNo()].m[3][1] -= freezeBoneWorldMatrix.m[3][1];
				}
				if (freezeBoneInfo.freezeZ) {
					//Z���̈ړ����t���[�Y�B
					m_freezeBoneTranslate.z = freezeBoneWorldMatrix.m[3][2];
					m_boneMatrix[bone->GetNo()].m[3][2] -= freezeBoneWorldMatrix.m[3][2];
				}
				break;
			}
		}
	}
	
	void CAnimationPlayController::CalcFreezeBoneWorldMatrix(CBone& bone, const CMatrix& parentMatrix, CMatrix& freezeBoneMatrix)
	{
		const CAnimationClip::SFreezeBoneInfo& freezeBoneInfo = m_animationClip->GetFreezeBoneInfo();
		CMatrix mBoneWorld;
		CMatrix localMatrix = m_boneMatrix[bone.GetNo()];
		mBoneWorld = localMatrix * parentMatrix;
		if (bone.GetNo() == freezeBoneInfo.boneNo) {
			//���������B
			freezeBoneMatrix = mBoneWorld;
			return;
		}
		for (auto childBone : bone.GetChildren()) {
			CalcFreezeBoneWorldMatrix(*childBone, mBoneWorld, freezeBoneMatrix);
		}
	}
	
}