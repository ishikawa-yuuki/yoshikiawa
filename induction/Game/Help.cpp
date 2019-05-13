#include "stdafx.h"
#include "Help.h"
#include "Fade.h"
#include "Title.h"

Help::Help()
{
}


Help::~Help()
{
	DeleteGO(m_spriteRender);
}
bool Help::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/Stage_Select.dds", 1280.0f, 720.0f);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Help::Update()
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