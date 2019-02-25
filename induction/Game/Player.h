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
	void Move(); // プレイヤーの基本的な動き
	void Color_Change();//光の色変更、ラチェクラのクランクイメージ、
	CVector3 GetPosition() const{ // プレイヤーの場所を返す関数。
		return m_position;
	}

	/*光の色を変えます*/
	int GetColor(){//光の色を返すぜ//　　　ポインタ使うといいかもしれない。 //int型になった。。。
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

