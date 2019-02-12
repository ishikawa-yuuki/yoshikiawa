#include "stdafx.h"
#include "Credit.h"
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
	return true;
}
void Credit::Update()
{
	if (Pad(0).IsTrigger(enButtonB)) {
		NewGO<Title>(0);
		DeleteGO(this);
	}
}