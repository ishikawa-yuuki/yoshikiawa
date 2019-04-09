#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class Human;
class Light_Object;
class Light_Object2;
class MistEnemy : public IGameObject
{
public:
	MistEnemy();
	~MistEnemy();
	bool Start();
	void Update();
	void Atari();
	CVector3 GetPosition()const {
		return m_position;
	}
	int Getstate()const {
		return m_state;
	}
private:
	enum Enstate {
		enNormal,//0
		enPlayer,//1
		enHuman//2
	};

	Enstate m_state = enNormal;
	prefab::CEffect* m_effect;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_startpos = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	Player* m_player;
	Human* m_human;
	Light_Object* m_lightObject;
	Light_Object2* m_lightObject2;
	bool m_escape_flag = false;
	bool m_taking_flag = false;
	int m_timer = 0;
	int time = 0;
};

