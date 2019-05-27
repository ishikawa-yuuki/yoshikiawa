#include "stdafx.h"
#include "Help.h"
#include "Fade.h"
#include "Title.h"
#include "Game.h"
Help::Help()
{
}


Help::~Help()
{
	if (!m_nextSprite) {
		DeleteGO(m_spriteRender);
	}
	else {
		DeleteGO(m_spriteRender2);
	}
}
bool Help::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/setumei_teisei.dds", 1280.0f, 720.0f);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}
void Help::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_istransstage) {
				NewGO<Game>(0, "Game");
				DeleteGO(this);
			}
			else {
				NewGO<Title>(0, "Title");
				DeleteGO(this);
			}
		}
	}
	else if (Pad(0).IsTrigger(enButtonA)) {
		//void PostRender();
		switch (m_nextSprite)
		{
		case false:
			m_nextSprite = true;
			DeleteGO(m_spriteRender);
			m_spriteRender2 = NewGO < prefab::CSpriteRender >(0);
			m_spriteRender2->Init(L"sprite/setumei_teisei2.dds",1280.0f,720.0f);
			break;
		case true:
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
	else if (Pad(0).IsTrigger(enButtonB)) {
		switch (m_nextSprite)
		{
		case false:
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
			break;
		case true:
			m_nextSprite = false;
			DeleteGO(m_spriteRender2);
			m_spriteRender = NewGO < prefab::CSpriteRender >(0);
			m_spriteRender->Init(L"sprite/setumei_teisei.dds", 1280.0f, 720.0f);
		}
	}
	
}

//void Help::PostRender(CRenderContext& renderContext) 
//{
//	if (!m_nextSprite) {
//		m_font.Begin(renderContext);
//		wchar_t aaa2[100];
//		swprintf(aaa2, L"ヒカリをソウサし、ヒトをゴールまでミチビきましょう。");
//		m_font.Draw(aaa2, { 0.0f,0.0f }, CVector4::White, 0.0f, 1.5f);
//		m_font.End(renderContext);
//	}
//	else if (m_nextSprite) {
//		m_font.Begin(renderContext);
//		wchar_t aaa2[100];
//		swprintf(aaa2, L"Aボタンでブラックホールにキリカワリます。ブラックホールモードはヒカリをスいとることができます。");
//		m_font.Draw(aaa2, { 0.0f,0.0f }, CVector4::White, 0.0f, 1.5f);
//		m_font.End(renderContext);
//	}
//}