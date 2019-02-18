#include "stdafx.h"
#include "GameOver.h"


GameOver::GameOver()
{

}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
}

bool GameOver::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/retire.dds", 1280.0f, 720.0f);
	return true;
}
void GameOver::Update()
{
	if (Pad(0).IsTrigger(enButtonB)) {

		DeleteGO(this);
	}
}