#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class Player;
class StarDust : public IGameObject
{
public:
	StarDust();
	~StarDust();
	bool Start();
	void Update();
private:
	prefab::CEffect* m_effect;
	Player* m_player;
	int m_timer = 0;
};

