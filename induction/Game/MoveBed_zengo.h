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

	//�������o�O�̌�����
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
	//���x���Őݒ肵����]��������B
	void SetRot(const CQuaternion& rot) {
		m_rotation = rot;
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
	//���̊֐����Ă΂��Ə������ς��B
	bool isLongFrag() {
		m_islong = true;
		return m_islong;
	}
private:
	const float MOVE_SPEED = 4.0f*60.0f;
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = {0.0f,0.0f,0.0f};
	//�����ʒu
	CVector3 m_protpos = m_position;
	CVector3 m_moveSpeed = { 0.0f, 0.0f, MOVE_SPEED };
	CQuaternion m_rotation = { 0.0f,0.0f,0.0f, 1.0f };
	//�P�t���[���O�̈ʒu
	CVector3 m_lastFramepos = CVector3::Zero;
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
	//���x���f�U�C���p�̃X�P�[���𑫂��܂���
	CVector3 m_scale = { 0.0f,0.0f,0.0f };
	//�ړ����鋗��������������
	bool m_islong = false;
	float m_timer = 0.0f;
	
};