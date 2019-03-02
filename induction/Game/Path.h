#pragma once
class PathEdge {
public:
	CVector3 startPos;		//!<�n�_�B
	
	CVector3 endPos;		//!<�I�_�B
	CVector3 direction;		//!<�����B
	CVector3 directionXZ;	//!<XZ���ʂł̕����B
	int no;
	/*!
	*@brief	�G�b�W�܂ł̍ŒZ�x�N�g�����v�Z�B
	*/
	CVector3 VectorToEdge(const CVector3& point) const;
};
class Path
{
public:
	Path();
	~Path();
	/*!
	*@brief	�p�X�f�[�^�����[�h�B
	*/
	void Load(const wchar_t* filePath);
	/*!
	*@brief	�p�X�̃|�C���g�̐����擾�B
	*/
	int GetNumPoint() const
	{
		return static_cast<int>(m_pointList.size());
	}
	/*!
	*@brief	�ŋߖ_�̃G�b�W�������B
	*/
	const PathEdge* GetNearEdge(const CVector3& pos)const;
	/*!
	*@brief	�G�b�W�̐����擾�B
	*/
	int GetNumEdge() const
	{
		return m_edgeList.size();
	}
	/*!
	*@brief	�G�b�W���擾�B
	*/
	const PathEdge* GetEdge(const int no) const
	{
		return &m_edgeList[no];
	}
private:

	std::vector<CVector3> m_pointList;	//!<���W�̃��X�g�B
	std::vector<PathEdge> m_edgeList;		//!<�G�b�W�̃��X�g�B
};

