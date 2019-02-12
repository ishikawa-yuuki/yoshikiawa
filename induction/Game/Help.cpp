#include "stdafx.h"
#include "Help.h"
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
	return true;
}
void Help::Update()
{
	if (Pad(0).IsTrigger(enButtonB)) {
		NewGO<Title>(0);
		DeleteGO(this);
	}
}