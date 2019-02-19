#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Game.h"

GameOver::GameOver()
{

}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}

bool GameOver::Start()
{
	m_game = FindGO<Game>("Game");
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/retire.dds", 1280.0f, 720.0f);
	return true;
}
void GameOver::Update()
{
	if (Pad(0).IsTrigger(enButtonB)) {
		m_game->GameOwari();
		NewGO<Title>(0);
		DeleteGO(this);
	}
}