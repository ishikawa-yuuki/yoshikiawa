#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Human.h"
#include "Player.h"
Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_human);
}
bool Game::Start()
{
	//ƒJƒƒ‰‚ğİ’èB
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();

	m_player = NewGO<Player>(0, "Player");
	m_human = NewGO<Human>(0, "Human");
	
	return true;
}

void Game::Update()
{
}