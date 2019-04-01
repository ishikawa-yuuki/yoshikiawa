#include "stdafx.h"
#include "Poison.h"
#include "Lever.h"

Poison::Poison()
{
}


Poison::~Poison()
{
	DeleteGO(m_skin);
}
bool Poison::Start()
{
	m_lever = FindGO<Lever>("Lever");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Poison/huzitubo.cmo");
	m_position.y = -50;
	m_position.z = -500;
	m_skin->SetPosition(m_position);
	
	return true;
}
void Poison::Update()
{
	if (m_lever->IsStateLever()) {
		if (m_timer >= 0.5f) {
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Play(L"effect/Poison_01.efk");
			m_effect->SetPosition(m_position);
			m_timer = 0;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_GhostObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);
	}
	else {
		m_GhostObject.Release();
	}
	
}