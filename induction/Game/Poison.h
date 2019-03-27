#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Lever;
class Poison : public IGameObject
{
public:
	Poison();
	~Poison();
	bool Start();
	void Update();

	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//ゴーストオブジェクトの情報を返す関数。
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CEffect* m_effect;
	Lever* m_lever = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsGhostObject m_GhostObject;
	float m_timer = 0.0f;
	
};

