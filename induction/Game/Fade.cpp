#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
}

bool Fade::Start()
{
	//m_texture.CreateFromDDSTextureFromFile(L"sprite/fade.dds");
	//m_sprite.Init(m_texture, GraphicsEngine().Get2DSpaceScreenWidth, GraphicsEngine().Get2DSpaceScreenHeight);
	return true;
}

void Fade::Update()
{

}
void Fade::PostRender(CRenderContext& rc)
{

}