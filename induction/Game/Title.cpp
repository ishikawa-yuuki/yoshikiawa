#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Stage_Select.h"

Title::Title()
{
}


Title::~Title()
{
	DeleteGO(m_spriteRender);
}

bool Title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title_induction.dds",1280.0f,720.0f);
	return true;
}

void Title::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		NewGO<Stage_Select>(0, "Stage_Select");
		DeleteGO(this);
	}
}