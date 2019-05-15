#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Player;
class Game;
class GameData;
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
		m_n = num;
	};
	//挙動を変える
	void SetPoisonMoveNumber(const int& number) {
		m_num = number;
	};
private:
	
	prefab::CSkinModelRender* m_skin = nullptr;
	Lever* m_lever ;
	Player* m_player;
	Game* m_game;
	GameData* m_gamedata = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsGhostObject m_GhostObject;
	float m_timer = 0.0f;
	//ガスを出すタイミングをずらすタイム
	float m_time = 0.0f;
	float m_volume = 0;
    //何番か
	int m_n = 0;
	//どの動きをするか
	//1ならレバーで動く
	//2なら順番に動く
	//3ならレバーの逆に動く(1の反転）
	int m_num = 0;
	//ガスの状態trueなら出てる
	bool m_State = true;
	
};

