#include "stdafx.h"
#include "Game.h"
#include "Poison.h"
#include "Lever.h"
#include "Player.h"
#include "GameData.h"
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
	m_game = FindGO<Game>("Game");
	m_gamedata = &GameData::GetInstance();
	return true;
}
void Poison::Range() 
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume =0.1f;
	}
	else if(diff.LengthSq() < range * 1.5){
		m_volume = 0.07f;
	}
	else if(diff.LengthSq() < range*3){
		m_volume = 0.04f;
	}
	else {
		m_volume = 0.0f;
	}
	m_gamedata = &GameData::GetInstance();
}
void Poison::Update()
{
	const auto& leverList = m_game->GetLeverList();
	switch (m_num) {
	case 1:
		if (leverList[m_n]->IsStateLever()) {
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
		else if (!leverList[m_n]->IsStateLever()) {
			m_GhostObject.Release();
		}
		break;
	//Stage2‚Ì“®‚«
	case GameData::enState_Stage2:
		m_time += GameTime().GetFrameDeltaTime();
		
		switch (m_n) {
		case 0:
			if ( m_time >= 4.0f&& m_time <= 13.0f) {
				if (m_time >= 5.0f) {
					m_GhostObject.Release();
				}
			}
			else if (m_time >= 0 || m_time >= 14.0f) {
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


			break;
		case 1:
			if (m_time >= 9.0f) {
				if (m_time >= 10.0f) {
					m_GhostObject.Release();
				}
			}
			else if (m_time >= 4.0f) {
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
			break;
		case 2:
			if (m_time >= 14.0f) 
			{
				if (m_time >= 15.0f) {
					m_GhostObject.Release();
				}
			}
			else if (m_time >= 9.0f) {
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
			break;
		}
		if (m_time >= 15.0f) {
			m_time = 0;
		}
		break;
	case 3:
		if (!leverList[m_n]->IsStateLever()) {
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
		else if (leverList[m_n]->IsStateLever()) {
			m_GhostObject.Release();
		}
		break;
	}

}