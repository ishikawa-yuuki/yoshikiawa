#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Fade;
class Human;
class Player;
//class Enemy;
class MistEnemy;
class Hill;
class MoveBed;
class MoveBed_zengo;
class Light_Object;
class Light_Object2;
class GameCamera;
class BackGround;
class Exit;
class Poison;
class Lever;
class Lightstand;
class Door;
class Stone;
class GameData;
class CheckPoint;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Pose();
	void Stage1();
	void Stage2();
	void Stage3();
	void Stage4();
	void Stage5();
	void PostRender(CRenderContext& renderContext); //何かを調べるためのポストレンダラ
	//ここから下の関数はごり押しです・・・なんかいい書き方がある気がする・・・

	//ゲームクラスを消したいときに使う関数、基本GameOverクラスから呼ばれる
	bool GameOwari()
	{
		m_Gamesyuuryou = true;
		return m_Gamesyuuryou;
	}
	//ポーズ中であるかどうかの関数、敵やギミックがこれで止まるかも
	bool GetisPose() const
	{
		return m_isPose;
	}
	//ダメージ中であるかどうかの関数、HumanやEnemyクラスに使われるかも
	bool GetDamage()
	{
		m_damege = true;
		return m_damege;
	}
	const std::vector<Light_Object*>& GetLightObjectList()
	{
		return m_lightobjectList;
	}
	//レバーのオン、オフ
	const std::vector<Lever*>&GetLeverList() {
		return m_leverList;
	}
	const std::vector<Poison*>& GetPoisonList() {
		return m_poisonList;
	}
	void SetisClear()
	{
		m_isclear = true;
	}
	bool GetisClear()
	{
		return m_isclear;
	}
private:
	/*ポインタ群*/
	Fade * m_fade = nullptr;
	Human * m_human;
	Player* m_player;
	/*Enemy* m_enemy;*/
	MistEnemy* m_mistenemy;
	BackGround* m_background;
	GameCamera * m_gamecamera;
	Exit* m_exit;
	
	/*prefab::CSkinModelRender* m_goal = nullptr;*/
	//trueなら画面を切り替える。
	bool m_isWaitFadeout = false;
	bool m_isPose = false;
	CVector3 m_Retirepos = { -200.0f,-100.0f,0.0f };
	CVector3 m_toGamepos = { 200.0f,-100.0f,0.0f };
	CVector3 m_arrowpos = { -400.0f,-100.0f,0.0f };
	enum pose{
		retire,
		togame,
		posenum
	};
	pose m_state = togame;
	bool m_Gamesyuuryou = false;
	bool m_damege = false;
	//level
	CLevel m_level;
	int n = 1;
	//可変長配列
	std::vector<MoveBed*> m_moveBedList;
	std::vector<MoveBed_zengo*> m_moveBed_zengoList;
	std::vector<MoveBed_zengo*> m_moveBed_zengo2List;
	std::vector<Light_Object*> m_lightobjectList;
	std::vector<Hill*> m_hillList;
	std::vector<Lever*>m_leverList;
	std::vector<Poison*>m_poisonList;
	std::vector<Lightstand*>m_Lightstand1List;
	std::vector<Stone*>m_StoneList;
	std::vector<Door*>m_DoorList;
	prefab::CSky* m_sky = nullptr;
	GameData* m_gamedata = nullptr;
	CFont m_font;
	bool m_isgameover = false;
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	const float m_time2 = 1.0f;
	CheckPoint* m_checkpoint = nullptr;
	const wchar_t* m_checkpointname = L"CheckPoint";
	bool m_isclear = false;
};

