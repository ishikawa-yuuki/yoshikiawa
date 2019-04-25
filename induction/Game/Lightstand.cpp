#include "stdafx.h"
#include "Lightstand.h"
#include "Player.h"

Lightstand::Lightstand()
{
}


Lightstand::~Lightstand()
{
	DeleteGO(m_skin);
	DeleteGO(m_sound);
}

bool Lightstand::Start()
{
	m_player = FindGO<Player>("Player");
	if (num == 0) {
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Lightstand01.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);
		m_position.y = 10;
	}
	else if (num == 1) {
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Torches.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		/*m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);*/
		m_position.y += 50;
		//m_position.x += 30;
	}
	else if(num == 2){
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Lightstand02.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		/*m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);*/
	}
	m_sound = NewGO<prefab::CSoundSource>(0);
	m_sound->Init(L"sound/Fire.wav");
	m_sound->SetPosition(m_position);
	/*m_sound->SetVolume(m_volume);*/
	m_sound->Play(true);
	m_pointLight = NewGO<prefab::CPointLight>(0);
	m_pointLight->SetColor({10.0,10.0,10.0});
	CVector3 Attn;
	Attn.x = 1000.0f;
	Attn.y = 10.0f;
	m_pointLight->SetAttn(Attn);
	
	return true;
}
void Lightstand::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 1.0f;
	}
	else if (diff.LengthSq() < range * 1.5) {
		m_volume = 0.25f;
	}
	else if (diff.LengthSq() < range * 3) {
		m_volume = 0.07f;
	}
	else {
		m_volume = 0.0f;
	}
}
void Lightstand::Update()
{
	if (m_timer >= 0.5f) {
		prefab::CEffect*  effect = NewGO<prefab::CEffect>(0);
	    effect->Play(L"effect/Fire.efk");
		effect->SetPosition(m_position);
		m_timer = 0.0f;
	}
	Range();
	m_sound->SetVolume(m_volume);
	m_pointLight->SetPosition(m_position);
	m_timer += GameTime().GetFrameDeltaTime();
}
	
