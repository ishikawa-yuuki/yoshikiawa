#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
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
	DeleteGO(m_bgm);
}

bool Title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Title_induction.dds",1280.0f,720.0f);
	m_arrow = NewGO<prefab::CSpriteRender>(0);
	m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/kari.wav");
	m_bgm->Play(true);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}

void Title::Update()
{
	
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_select == select1) {
				NewGO<Stage_Select>(0, "Stage_Select");
				DeleteGO(this);
			}
			else if (m_select == select2) {
				NewGO<Help>(0, "Help");
				DeleteGO(this);
			}
			else if (m_select == select3) {
				NewGO<Credit>(0, "Credit");
				DeleteGO(this);
			}
		}
	}
		Choice();
	
}
void Title::Choice()
{
	prefab::CSoundSource* ss;
	const float arrow_move = -100.0f;//‹|‚ÌˆÚ“®‹——£
	if (Pad(0).IsTrigger(enButtonDown)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
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
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
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
	else if (Pad(0).IsTrigger(enButtonA)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/decision1.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		m_isWaitFadeout = true;
		m_fade->StartFadeOut();
	}
	
	m_arrow->SetPosition(m_arrowPos);
}