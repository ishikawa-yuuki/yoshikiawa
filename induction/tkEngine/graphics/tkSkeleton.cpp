/*!
 *@brief	�X�P���g��
 */
#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/tkSkeleton.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"
#include "tkEngine/graphics/animation/tkAnimation.h"
#include <comdef.h> 

namespace tkEngine {
	namespace {
		
	}
	void CBone::CalcWorldTRS(CVector3& trans, CQuaternion& rot, CVector3& scale)
	{
		CMatrix mWorld = m_worldMatrix;
		//�s�񂩂�g�嗦���擾����B
		scale.x = mWorld.v[0].Length();
		scale.y = mWorld.v[1].Length();
		scale.z = mWorld.v[2].Length();
		m_scale = scale;
		//�s�񂩂畽�s�ړ��ʂ��擾����B
		trans.Set(mWorld.v[3]);
		m_positoin = trans;
		//�s�񂩂�g�嗦�ƕ��s�ړ��ʂ��������ĉ�]�ʂ��擾����B
		mWorld.v[0].Normalize();
		mWorld.v[1].Normalize();
		mWorld.v[2].Normalize();
		mWorld.v[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
		rot.SetRotation(mWorld);
		m_rotation = rot;
	}
	CSkeleton::CSkeleton()
	{
		//���U�[�u�B
		m_bones.reserve(BONE_MAX);
	}
	CSkeleton::~CSkeleton()
	{
	}
	void CSkeleton::UpdateBoneWorldMatrix(CBone& bone, const CMatrix& parentMatrix)
	{
		CMatrix mBoneWorld;
		CMatrix localMatrix = bone.GetLocalMatrix();
		mBoneWorld = localMatrix * parentMatrix;
	
		bone.SetWorldMatrix(mBoneWorld);
		for (auto childBone : bone.GetChildren()) {
			UpdateBoneWorldMatrix(*childBone, mBoneWorld);
		}
	}
	bool CSkeleton::Load(const wchar_t* filePath)
	{
		
		FILE* fp = _wfopen(filePath, L"rb");

		if (fp == nullptr) {
			return false;
		}
		//���̐����擾�B
		int numBone = 0;
		fread(&numBone, sizeof(numBone), 1, fp);
		for (int i = 0; i < numBone; i++) {
			int nameCount = 0;
			//���̖��O���擾�B
			fread(&nameCount, 1, 1, fp);
			std::unique_ptr<char[]> name = std::make_unique<char[]>(nameCount+1);
			fread(name.get(), nameCount+1, 1, fp);
			//�e��ID���擾�B
			int parentId;
			fread(&parentId, sizeof(parentId),  1, fp);
			//�o�C���h�|�[�Y���擾�B
			CVector3 bindPose[4];
			fread(&bindPose, sizeof(bindPose), 1, fp);
			//�o�C���h�|�[�Y�̋t�����擾�B
			CVector3 invBindPose[4];
			fread(&invBindPose, sizeof(invBindPose), 1, fp);
			
			//�o�C���h�|�[�Y�B
			CMatrix bindPoseMatrix;
			memcpy(bindPoseMatrix.m[0], &bindPose[0], sizeof(bindPose[0]));
			memcpy(bindPoseMatrix.m[1], &bindPose[1], sizeof(bindPose[1]));
			memcpy(bindPoseMatrix.m[2], &bindPose[2], sizeof(bindPose[2]));
			memcpy(bindPoseMatrix.m[3], &bindPose[3], sizeof(bindPose[3]));
			bindPoseMatrix.m[0][3] = 0.0f;
			bindPoseMatrix.m[1][3] = 0.0f;
			bindPoseMatrix.m[2][3] = 0.0f;
			bindPoseMatrix.m[3][3] = 1.0f;

			//�o�C���h�|�[�Y�̋t�s��B
			CMatrix invBindPoseMatrix;
			memcpy(invBindPoseMatrix.m[0], &invBindPose[0], sizeof(invBindPose[0]));
			memcpy(invBindPoseMatrix.m[1], &invBindPose[1], sizeof(invBindPose[1]));
			memcpy(invBindPoseMatrix.m[2], &invBindPose[2], sizeof(invBindPose[2]));
			memcpy(invBindPoseMatrix.m[3], &invBindPose[3], sizeof(invBindPose[3]));
			invBindPoseMatrix.m[0][3] = 0.0f;
			invBindPoseMatrix.m[1][3] = 0.0f;
			invBindPoseMatrix.m[2][3] = 0.0f;
			invBindPoseMatrix.m[3][3] = 1.0f;

			wchar_t boneName[256];
			mbstowcs(boneName, name.get(), 256);
			CBonePtr bone = std::make_unique<CBone>(
				boneName,
				bindPoseMatrix,
				invBindPoseMatrix,
				parentId,
				i
			);

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
			//�{�[���̃o���f�[�V�����`�F�b�N�B
			//maxScript�ł�肽���Ƃ���ł͂��邪�A�Ƃ肠�����������B
			auto it = std::find_if(m_bones.begin(), m_bones.end(), [&](auto& bone) {return wcscmp(boneName, bone->GetName()) == 0;  });
			if (it != m_bones.end()) {
				//�����̃{�[�������������B
				_bstr_t b(boneName);
				const char* c = b;
				TK_WARNING("�����̃{�[����������܂����B����̓���ł��B�f�[�^���C�����Ă��������B%s", c);
			}
#endif
			m_bones.push_back(std::move(bone));


		}
		fclose(fp);

		OnCompleteAddedAllBones();

		return true;
	}

	void CSkeleton::OnCompleteAddedAllBones()
	{
		for (auto& bone : m_bones) {
			if (bone->GetParentId() != -1) {
				m_bones.at(bone->GetParentId())->AddChild(bone.get());
				//���[�J���}�g���N�X���v�Z�B
				const CMatrix& parentMatrix = m_bones.at(bone->GetParentId())->GetInvBindPoseMatrix();
				CMatrix localMatrix;
				localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
				bone->SetLocalMatrix(localMatrix);
			}
			else {
				bone->SetLocalMatrix(bone->GetBindPoseMatrix());
			}
		}
		

		//�{�[���s����m��
		m_boneMatrixs = std::make_unique<CMatrix[]>(m_bones.size());
		//StructuredBuffer���쐬�B
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		int stride = sizeof(CMatrix);

		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//SRV�Ƃ��ăo�C���h�\�B
		desc.ByteWidth = static_cast<UINT>(stride * m_bones.size());
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = stride;

		m_boneMatrixSB.Create(NULL, desc);

	}
	void CSkeleton::Update(const CMatrix& mWorld)
	{
		//���[���h�s����\�z���Ă���
		for (auto& bone : m_bones) {
			if (bone->GetParentId() != -1) {
				continue;
			}
			//���[�g�B
			UpdateBoneWorldMatrix(*bone, mWorld);
		}

		if (m_animation != nullptr) {
			m_animation->PostProcess();
		}

		//�{�[���s����v�Z�B
		int boneNo = 0;
		for (auto& bonePtr : m_bones) {
			CMatrix mBone;
			mBone = bonePtr->GetInvBindPoseMatrix() * bonePtr->GetWorldMatrix();
			m_boneMatrixs[boneNo] = mBone;
			boneNo++;
		}
		
	}
	void CSkeleton::Render(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_boneMatrixSB, m_boneMatrixs.get());
		//�{�[���s���SRV�ɐݒ�B
		rc.VSSetShaderResource(enSkinModelSRVReg_BoneMatrix, m_boneMatrixSB.GetSRV());
	}
	
}
