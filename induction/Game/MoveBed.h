#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class MoveBed : public IGameObject
{
public:
	MoveBed();
	~MoveBed();
	bool Start();
	void Update();
	CVector3 GetPosition() const {// �v���C���[�̏ꏊ��Ԃ��֐��B
		return m_position;
	}
	CVector3 GetLastPos() const {// 1�t���[���O�̃v���C���[�̏ꏊ��Ԃ��֐��B
		return m_lastFramepos;
	}
	CPhysicsGhostObject* GetGhost() {//�S�[�X�g�I�u�W�F�N�g�̏���Ԃ��֐��B
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = { 0.0f, 0.0f, -900.0f };//{800.0f, -160.0f, -900.0f};
	CVector3 m_ppos = m_position;//�{�b�N�X�`���p
	CVector3 m_protpos = m_position;//�����ʒu
	CVector3 m_moveSpeed = { 2.0f, 0.0f, 0.0f };
	CVector3 m_lastFramepos = m_position;//�P�t���[���O�̈ʒu
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
};

