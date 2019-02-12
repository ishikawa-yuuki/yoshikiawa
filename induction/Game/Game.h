#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Human;
class Player;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
private:
	Human * m_human;
	Player* m_player;
};

