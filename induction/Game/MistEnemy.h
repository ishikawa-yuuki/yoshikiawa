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
	bool Gettakingflag()const {
		return m_taking_flag;
	}
private:
	enum Enstate {
		enNormal = 0,//0
		enPlayer = 1,//1
		enHuman = 2//2
	};

	Enstate m_state = enNormal;
	prefab::CEffect* m_effect = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_startpos = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	Player* m_player;
	Human* m_human;
	//�v���C���[���瓦����t���O
	bool m_escape_flag = false;
	//�A�s�t���O
	bool m_taking_flag = false;
	int m_timer = 0;
	int Deathtimer = 0;
};

