#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move();
	CVector3 GetPosition() const{
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
};

