#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Lever;
class Poison : public IGameObject
{
private:
	enum PoisonNumber {
		poison0,
		poison1,
	};
	PoisonNumber m_poisonnum = poison0;
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
	void SetPoisonNumber(const int num);
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CEffect* m_effect;
	Lever* m_lever = nullptr;
	Lever* m_lever1 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsGhostObject m_GhostObject;
	float m_timer = 0.0f;
	
};

