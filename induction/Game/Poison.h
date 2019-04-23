#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Player;
class Poison : public IGameObject
{
public:
	Poison();
	~Poison();
	bool Start();
	void Update();
	void Range();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//ゴーストオブジェクトの情報を返す関数。
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
	void SetPoisonNumber(const int& num) {
		n = num;
	};
private:
	int n = 0;
	prefab::CSkinModelRender* m_skin = nullptr;
	Lever* m_lever ;
	Player* m_player;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsGhostObject m_GhostObject;
	float m_timer = 0.0f;
	float m_volume = 0;
	
};

