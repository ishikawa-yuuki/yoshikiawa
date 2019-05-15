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
}
bool Credit::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/arrow.dds", 1280.0f, 720.0f);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Credit::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0,"Title");
			DeleteGO(this);
		}
	}
	else if (Pad(0).IsTrigger(enButtonB)) {
		m_isWaitFadeout = true;
		m_fade->StartFadeOut();
	}
}