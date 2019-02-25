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
	CVector3 GetPosition() const {
		return m_position;
	}
	CVector3 GetLastPos() const {
		return m_lastFramepos;
	}
	CPhysicsGhostObject* GetGhost() {
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = { 0.0f, 0.0f, -900.0f };//{800.0f, -160.0f, -900.0f};
	CVector3 m_ppos = m_position;
	CVector3 m_protpos = m_position;
	CVector3 m_moveSpeed = { 2.0f, 0.0f, 0.0f };
	CVector3 m_lastFramepos = m_position;
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
	CVector3 size;
};

