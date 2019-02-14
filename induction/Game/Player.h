#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class GameCamera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move(); // プレイヤーの基本的な動き
	CVector3 GetPosition() const{ // プレイヤーの場所を返す関数。
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
	GameCamera* m_gamecamera = nullptr;
};

