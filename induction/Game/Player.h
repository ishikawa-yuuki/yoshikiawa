#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"
class GameCamera;
class Human;
class StarDust;
class Title;
class Game;
class TitleGround;
class Player : public IGameObject
{
private:
	//ここに書いたほうが都合がいいので
    //ここだけprivateにしています。
	enum Color {
		hikari_hutu,
		hikari_black,
		hikari_explosion
	};
	
public:
	Player();
	~Player();
	bool Start();
	void Update();
	// プレイヤーの基本的な動き
	void Move(); 
	// プレイヤーがゲームを始める時の動き。
	void GameStartMove();
	//光の色変更、ラチェクラのクランクイメージ、
	void Color_Change();
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const
	{ 
		return m_position;
	}
	//プレイヤーの最初の移動が終わったかを返す関数。
	bool GetStartMove()const
	{
		return m_StartMoveFin;
	}
	/*光の色を変えます*/
	//光の色を返すぜ int型になった。。。
	int GetColor(){
		int number = 0;
		switch (m_color)
		{
		case hikari_hutu:
			number = 0;
			break;
		case hikari_black:
			number = 1;
			break;
		case hikari_explosion:
			number = 2;
			break;
		}
		return number;
	}
	CVector4 GetPointLightAttn() const
	{
		return m_ptLight->GetAttn();
	}
	prefab::CPointLight* GetPointLight() const
	{
		return m_ptLight;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,500.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	prefab::CSkinModelRender* m_skin = nullptr;
	GameCamera* m_gamecamera = nullptr;
	Human* m_human = nullptr;
	StarDust* m_stardust = nullptr;
	Game* m_game = nullptr;
	CCharacterController m_charaCon;
	prefab::CPointLight* m_ptLight = nullptr;
	//通常状態の光の力。初期化用
	const CVector3 m_pointLigDefaultAttn = {1000.0f, 10.0f, 0.0f};
	//変動する光の力。常用
	CVector3 m_attn = { 1000.0f,10.0f,0.0f };
	float m_explosionTimer = 0;
	//最初のプレイヤーの挙動が終わったかどうか。
	bool m_StartMoveFin = false;
	Title* m_title = nullptr;
	//ブラックホールになる時に光があふれる感じを調整するための変数
	float m_ahureru = 0;

	prefab::CSoundSource* m_sound = nullptr;
	TitleGround* m_titleground = nullptr;
	CVector3 m_protposition = CVector3::Zero;
	float m_degree = 0.0f;
	Color m_color = hikari_hutu;
};

