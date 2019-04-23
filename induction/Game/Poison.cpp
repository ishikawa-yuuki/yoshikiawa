#include "stdafx.h"
#include "Game.h"
#include "Poison.h"
#include "Lever.h"
#include "Player.h"
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
	m_player = FindGO<Player>("Player");
	return true;
}
void Poison::Range() 
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume =0.1f;
	}
	else if(diff.LengthSq() < range*2){
		m_volume = 0.05f;
	}
	else {
		m_volume = 0.0f;
	}
}
void Poison::Update()
{
	Game* game = FindGO<Game>("Game");
	const auto& leverList = game->GetLeverList();
		if (leverList[n]->IsStateLever()) {
			if (m_timer >= 0.5f) {
				prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
				effect->Play(L"effect/Poison_01.efk");
				effect->SetPosition(m_position);
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Gas.wav");
				Range();
				ss->SetVolume(m_volume);
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