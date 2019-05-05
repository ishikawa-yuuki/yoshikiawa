#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Stone :public IGameObject
{
public:
	Stone();
	~Stone();
	bool Start();
	void Update();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	void SetRot(const CQuaternion& rot) {
		m_rot = rot;
	}
	//ゴーストオブジェクトの情報を返す関数。
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
private:
	CPhysicsGhostObject m_GhostObject;
	CCharacterController m_charaCon;
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	const float MOVE_SPEED = 4.0f * 60.0f;
	float m_timer = 0;
};

