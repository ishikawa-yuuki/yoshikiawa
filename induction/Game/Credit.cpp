#include "stdafx.h"
#include "Credit.h"
#include "Fade.h"
#include "Title.h"

Credit::Credit()
{
}


Credit::~Credit()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_fade);
}
bool Credit::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/arrow.dds", 1280.0f, 720.0f);
	m_fade = NewGO<Fade>(0, "Fade");
	m_fade->StartFadeIn();
	return true;
}
void Credit::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
	else if (Pad(0).IsTrigger(enButtonB)) {
		m_isWaitFadeout = true;
		m_fade->StartFadeOut();
	}
}