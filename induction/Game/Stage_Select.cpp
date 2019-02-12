#include "stdafx.h"
#include "Stage_Select.h"
#include "Game.h"
#include "Title.h"

Stage_Select::Stage_Select()
{
}


Stage_Select::~Stage_Select()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_arrow);
}

bool Stage_Select::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Stage_Select.dds", 1280.0f, 720.0f);
	m_arrow = NewGO<prefab::CSpriteRender>(0);
	m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	return true;
}

void Stage_Select::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		if (m_stage == stage1) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else if (Pad(0).IsTrigger(enButtonB)) {
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
	Choice();
}

void Stage_Select::Choice()
{
	float arrow_move = 215.0f;
	if (Pad(0).IsTrigger(enButtonRight)) {
		switch (m_stage) {
		case stage1:
			m_stage = stage2;
			m_arrowPos.x += arrow_move;
			break;
		case stage2:
			m_stage = stage3;
			m_arrowPos.x += arrow_move;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)) {
		switch (m_stage) {
		case stage2:
			m_stage = stage1;
			m_arrowPos.x -= arrow_move;
			break;
		case stage3:
			m_stage = stage2;
			m_arrowPos.x -= arrow_move;
			break;
		}
	}
	m_arrow->SetPosition(m_arrowPos);
}