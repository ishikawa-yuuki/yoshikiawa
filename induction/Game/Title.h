#pragma once
#include "tkEngine/light/tkPointLight.h"
class Fade;
class TitleGround;
class Player;
class Human;
class GameCamera;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	//タイトルシーンの選択
	void Choice(); 
	//ステージセレクト画面に遷移するかどうか
	bool isTransStageSelect()
	{
		return m_istransstageselect;
	}
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSpriteRender* m_menu1;
	prefab::CSpriteRender* m_menu2;
	prefab::CSpriteRender* m_menu3;
	// 弓の初期位置、select1の横にある。
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f };
	enum Select {
		//stage選択画面
		select1,
		//操作方法画面
		select2,
		//クレジット
		select3
	};
	Select m_select = select1;
	TitleGround* m_titleground = nullptr;
	Player* m_player = nullptr;
	Human* m_human = nullptr;
	GameCamera* m_gamecamera = nullptr;
	//ポイントライトを生成
	prefab::CPointLight* m_ptLight = nullptr;
	//ライトの光の増減、減衰率を操作。
	CVector3 attn = CVector3::Zero;
	//trueなら画面を切り替える。
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	//level
	CLevel m_level;
	bool m_istransstageselect = false;
};

