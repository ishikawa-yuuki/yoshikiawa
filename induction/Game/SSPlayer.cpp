#include "stdafx.h"
#include "SSPlayer.h"


SSPlayer::SSPlayer()
{
}


SSPlayer::~SSPlayer()
{
	DeleteGO(m_effect);
}
bool SSPlayer::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	return true;
}

void SSPlayer::Update()
{
	Move();
	m_effect->SetPosition(m_position);
}

void SSPlayer::Move()
{
 	const float pl_speed = 600.0f;//Œõ‚Ì‘¬“x 
	if (Pad(0).IsTrigger(enButtonRight)) {
		switch (m_stage) {
		case stage1:
			m_position.x += pl_speed;
			m_stage = stage2;
			break;
		case stage2:
			m_position.x += pl_speed;
			m_stage = stage3;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)) {
		switch (m_stage) {
		case stage3:
			m_position.x -= pl_speed;
			m_stage = stage2;
			break;
		case stage2:
			m_position.x -= pl_speed;
			m_stage = stage1;
			break;
		}
	}
}
