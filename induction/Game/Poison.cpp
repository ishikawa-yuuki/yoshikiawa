#include "stdafx.h"
#include "Game.h"
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
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Poison/huzitubo.cmo");
	m_skin->SetPosition(m_position);
	
	return true;
}
void Poison::Update()
{
	Game* game = FindGO<Game>("Game");
	const auto& leverList = game->GetLeverList();
		if (leverList[n]->IsStateLever()) {
			if (m_timer >= 0.5f) {
				prefab::CEffect* m_effect = NewGO<prefab::CEffect>(0);
				m_effect->Play(L"effect/Poison_01.efk");
				m_effect->SetPosition(m_position);
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Gas.wav", true);
				ss->SetVolume(0.1f);
				ss->SetPosition(m_position);
				ss->Play(false);
				m_timer = 0.0f;
			}
			m_timer += GameTime().GetFrameDeltaTime();
			m_GhostObject.CreateBox(
				m_position,
				CQuaternion::Identity,
				{ 100.0f, 500.0f, 100.0f }
			);
		}
		else if( !leverList[n]->IsStateLever()){		
			m_GhostObject.Release();
		}
}