#include "stdafx.h"
#include "Lightstand.h"


Lightstand::Lightstand()
{
}


Lightstand::~Lightstand()
{
	DeleteGO(m_skin);
}
bool Lightstand::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/StageObject/Lightstand01.cmo");
	m_skin->SetPosition(m_position);
	m_StaticObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{ 100.0f, 500.0f, 100.0f }
	);
	m_position.y = 50;
	return true;
}
void Lightstand::Update()
{
	if (m_timer >= 0.5f) {
		m_effect = NewGO<prefab::CEffect>(0);
		m_effect->Play(L"effect/Fire.efk");
		m_effect->SetPosition(m_position);
		m_timer = 0;
	}
	m_timer += GameTime().GetFrameDeltaTime();
	
}
	
