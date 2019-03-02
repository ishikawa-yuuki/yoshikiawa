#include "stdafx.h"
#include "Path.h"

CVector3 PathEdge::VectorToEdge(const CVector3& point) const
{
	//���_����pos�Ɍ������ĐL�т�x�N�g��v0���v�Z�B
	CVector3 v0 = point - startPos;
	//v0���G�b�W��Ɏˉe�����x�N�g��v1���v�Z����B
	CVector3 v1 = direction * v0.Dot(direction);
	//v0����G�b�W�ɑ΂��ė��Ƃ����������v�Z����B
	CVector3 v3 = v1 - v0;
	return v3;
}

Path::Path()
{
}


Path::~Path()
{
}
void Path::Load(const wchar_t* filePath)
{
	CSkeleton loc;
	if (!loc.Load(filePath)) {
		//�p�X��ǂݍ��߂Ȃ������B
		return;
	}
	m_pointList.resize(loc.GetNumBones() - 1);
	for (int i = 1; i < loc.GetNumBones(); i++) {
		CBone* bone = loc.GetBone(i);
		const CMatrix& mat = bone->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.y = mat.m[3][2];
		pos.z = -mat.m[3][1];
		int pointNo = _wtoi(bone->GetName());
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (pointNo == 0) {
			TK_WARNING_MESSAGE_BOX("�p�X�̃m�[�h�̃{�[���̖��O���s���ł��B");
			m_pointList.clear();
			return;
		}
#endif
		m_pointList[pointNo - 1] = pos;
	}

	//�G�b�W���\�z�B

	m_edgeList.reserve(m_pointList.size() - 1);
	for (int i = 0; i < m_pointList.size() - 1; i++) {
		PathEdge edge;
		edge.startPos = m_pointList[i];
		edge.endPos = m_pointList[i + 1];
		edge.direction = edge.endPos - edge.startPos;
		edge.direction.Normalize();
		edge.directionXZ = edge.direction;
		edge.directionXZ.y = 0.0f;
		edge.directionXZ.Normalize();
		edge.no = m_edgeList.size();
		m_edgeList.push_back(edge);
	}
}
/*!
*@brief	�ŋߖ_�̃G�b�W�������B
*/
const PathEdge* Path::GetNearEdge(const CVector3& pos) const
{
	float dist = FLT_MAX;
	const PathEdge* nearEdge = nullptr;
	for (auto& edge : m_edgeList) {
		//v0����G�b�W�ɑ΂��ė��Ƃ����������v�Z����B
		CVector3 v = edge.VectorToEdge(pos);
		v.y = 0.0f;
		float distTmp = v.Length();
		if (dist > distTmp) {
			//������̕����߂��B
			dist = distTmp;
			nearEdge = &edge;
		}

	}
	return nearEdge;
}