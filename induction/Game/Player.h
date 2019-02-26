#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
class GameCamera;
class Player : public IGameObject
{
private:
	//ここに書いたほうが都合がいいので
    //ここだけprivateにしています。
	enum Color {
		hikari_hutu,
		hikari_red
	};
	Color m_color = hikari_hutu;
public:
	Player();
	~Player();
	bool Start();
	void Update();
	// プレイヤーの基本的な動き
	void Move(); 
	//光の色変更、ラチェクラのクランクイメージ、
	void Color_Change();
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const
	{ 
		return m_position;
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
		case hikari_red:
			number = 1;
			break;
		}
		return number;
	}
private:
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect;
	GameCamera* m_gamecamera = nullptr;
	CCharacterController m_charaCon;
};

