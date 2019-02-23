#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Fade;
class Human;
class Player;
class MoveBed;
class GameCamera;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Pose();
	//ここから下の関数はごり押しです・・・なんかいい書き方がある気がする・・・

	bool GameOwari() {//ゲームクラスを消したいときに使う関数、基本GameOverクラスから呼ばれる
		m_Gamesyuuryou = true;
		return m_Gamesyuuryou;
	}
	bool GetifPose() const{//ポーズ中であるかどうかの関数、敵やギミックがこれで止まるかも
		return m_isPose;
	}
	bool GetDamage(){//ダメージ中であるかどうかの関数、HumanやEnemyクラスに使われるかも
		m_damege = true;
		return m_damege;
	}
private:
	Fade * m_fade = nullptr;
	Human * m_human;
	Player* m_player;
	MoveBed* m_movebed;
	GameCamera * m_gamecamera;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSpriteRender* m_sprite_Retire = nullptr;
	prefab::CSpriteRender* m_sprite_toGame = nullptr;
	prefab::CSpriteRender* m_sprite_arrow = nullptr;
	bool m_isWaitFadeout = false; //trueなら画面を切り替える。
	bool m_isPose = false;
	CVector3 m_Retirepos = { -200.0f,-100.0f,0.0f };
	CVector3 m_toGamepos = { 200.0f,-100.0f,0.0f };
	CVector3 m_arrowpos = { -400.0f,-100.0f,0.0f };
	enum pose{
		retire,
		togame,
		posenum
	};
	pose m_state = retire;
	bool m_Gamesyuuryou = false;
	bool m_damege = false;
};

