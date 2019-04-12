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
	m_lever1 = FindGO<Lever>("Lever1");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Poison/huzitubo.cmo");
	m_skin->SetPosition(m_position);
	
	return true;
}
void Poison::Update()
{
	prefab::CSoundSource* ss;
	switch(m_poisonnum) {
	case poison0:
		if (m_lever->IsStateLever(0)) {
			if (m_timer >= 0.5f) {
				m_effect = NewGO<prefab::CEffect>(0);
				m_effect->Play(L"effect/Poison_01.efk");
				m_effect->SetPosition(m_position);
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Gas.wav");
				ss->SetVolume(0.1f);
				ss->SetPosition(m_position);
				ss->Play(false);
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
		break;
	case poison1:
		if (m_lever1->IsStateLever(1)) {
			if (m_timer >= 0.5f) {
				m_effect = NewGO<prefab::CEffect>(0);
				m_effect->Play(L"effect/Poison_01.efk");
				m_effect->SetPosition(m_position);
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Gas.wav");
				ss->SetVolume(0.1f);
				ss->SetPosition(m_position);
				ss->Play(false);
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
		break;
	}
	
	
}
void Poison::SetPoisonNumber(const int num)
{
	switch (num) {
	case 0:
		m_poisonnum = poison0;
		break;
	case 1:
		m_poisonnum = poison1;
		break;
	}
}