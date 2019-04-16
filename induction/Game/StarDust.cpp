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
	return true;
}

void StarDust::Update()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hoshikuzu.efk");
	m_effect->SetScale({ 20.0f,20.0f,20.0f });
	m_effect->SetPosition(m_player->GetPosition());
}