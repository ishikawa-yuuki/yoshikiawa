#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Stage_Select.h"
#include "Help.h"
#include "Credit.h"
Title::Title()
{
}


Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_arrow);
}

bool Title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title_induction.dds",1280.0f,720.0f);
	m_arrow = NewGO<prefab::CSpriteRender>(0);
	m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	return true;
}

void Title::Update()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		switch (m_select) {
		case select1:
			NewGO<Stage_Select>(0, "Stage_Select");
			DeleteGO(this);
			break;
		case select2:
			NewGO<Help>(0, "Help");
			DeleteGO(this);
			break;
		case select3:
			NewGO<Credit>(0, "Credit");
			DeleteGO(this);
			break;
		}
	}
	Choice();
}
void Title::Choice()
{
	const float arrow_move = -100.0f;//‹|‚ÌˆÚ“®‹——£
	if (Pad(0).IsTrigger(enButtonDown)) {
		switch (m_select) {
		case select1:
			m_select = select2;
			m_arrowPos.y += arrow_move;
			break;
		case select2:
			m_select = select3;
			m_arrowPos.y += arrow_move;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonUp)) {
		switch (m_select) {
		case select2:
			m_select = select1;
			m_arrowPos.y -= arrow_move;
			break;
		case select3:
			m_select = select2;
			m_arrowPos.y -= arrow_move;
			break;
		}
	}
	m_arrow->SetPosition(m_arrowPos);
}