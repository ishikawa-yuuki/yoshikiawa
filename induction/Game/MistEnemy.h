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
	CVector3 m_position = { 9999.0f,0.0f,9999.0f };
	CVector3 m_startpos = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	Player* m_player;
	Human* m_human;
	//プレイヤーから逃げるフラグ
	bool m_escape_flag = false;
	//人を連れていくフラグ
	bool m_taking_flag = false;
	int m_timer = 0;
	int Deathtimer = 0;
	//最初だけ記録する
	bool m_kiroku = false;
	//もやが出るためのスイッチ
	bool m_moya = false;
	//effectが消える時のスイッチ
	bool iltutai = false;
};

