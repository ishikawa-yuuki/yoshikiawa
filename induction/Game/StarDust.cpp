#include "stdafx.h"
#include "StarDust.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"
#include "Player.h"

StarDust::StarDust()
{
}


StarDust::~StarDust()
{
	DeleteGO(m_effect);
}

bool StarDust::Start()
{
	m_player = FindGO<Player>("Player");
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hosikuzu.efk");
	m_effect->SetScale({ 20.0f,20.0f,20.0f });
	
	return true;
}

void StarDust::Update()
{
	if (m_timer > 20) {
		m_timer = 0;
		//DeleteGO(this);
	}
	m_timer++;
	m_effect->SetPosition(m_player->GetPosition());
}