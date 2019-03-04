#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class MoveBed_zengo : public IGameObject
{
public:
	MoveBed_zengo();
	~MoveBed_zengo();
	bool Start();
	void Update();
	
	void SetProtPos(const CVector3& pos)
	{
		m_protpos = pos;
	}
	//���x���Őݒu��������m_position��u��
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//���x���Őݒ肵���傫����������B
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const
	{
		return m_position;
	}
	// 1�t���[���O�̃v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetLastPos() const
	{
		return m_lastFramepos;
	}
	//�S�[�X�g�I�u�W�F�N�g�̏���Ԃ��֐��B
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = { 0.0f, 0.0f, -900.0f };
	//�{�b�N�X�`���p
	CVector3 m_ppos = m_position;
	//�����ʒu
	CVector3 m_protpos = m_position;
	CVector3 m_moveSpeed = { 0.0f, 0.0f, 2.0f };
	//�P�t���[���O�̈ʒu
	CVector3 m_lastFramepos = m_position;
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
	//���x���f�U�C���p�̃X�P�[���𑫂��܂���
	CVector3 m_scale = CVector3::Zero;
};