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
	//色々ストップ
	bool isStop()
	{
		return m_isstop;
	}
	//カメラの注視点を取得
	CVector3 GetCameraTarget()
	{
		return m_camerataragetpos;
	}
private:
	void GameStart();
	void SelectMenu();
	void TransScene();
	void TransStageSelect();
private:
	enum State {
		enState_GameStart,					//スタートボタン押すまで
		enState_SelectMenu,					//メニュー表示
		enState_TransScene,					//クレジットや操作説明に移行する時		
		enState_TransStageSelect,			//ステージセレクト画面に移行する時
	};
	State m_state = enState_GameStart;
	const CVector4 m_transparent = CVector4(1.0f, 1.0f, 1.0f, 0.0f);		//画像を透明(表示させない時)にこれをカラー乗算させる
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSpriteRender* m_pressstart = nullptr;
	std::vector <prefab::CSpriteRender*> m_menuList;
	// 弓の初期位置、select1の横にある。
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f };
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
	//メニューに移行するまで
 	float m_alphatitle = 0.0f, m_alphastart = 0.0f;
	float m_starttime = 1.0f;
	bool m_isaddalphastart = true;
	bool m_ispressstartbutton = false;
	//メニュー選択からシーン移行まで
	float m_alphamenu = 0.0f;							//α値
	const float m_translucentalphamenu = 0.5f;			//選択されてないやつは半透明にする
	bool m_ispressAbutton = false;						//Aボタンが押されたかどうか
	enum Select {
		//stage選択画面
		enState_StageSelect,
		//操作方法画面
		enState_Manual,
		//クレジット
		enState_Credit,
		//最小値
		enState_Fist = enState_StageSelect,
		//最大値
		enState_Last = enState_Credit
	};
	Select m_select = enState_StageSelect;				//最初はカーソルは一番上
	//ステージセレクト画面に移行
	CVector3 m_point = CVector3::Zero;
	bool m_isstop = false;
	float m_timer = 0.0f, m_time = 4.6f,m_time2 = 5.2;
	prefab::CSky* m_sky = nullptr;
	CVector3 m_camerataragetpos = CVector3::Zero;
};

