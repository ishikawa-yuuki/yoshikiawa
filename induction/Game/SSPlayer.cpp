#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPoint.h"
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
	m_SS = FindGO<Stage_Select>("Stage_Select");
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	return true;
}

void SSPlayer::Update()
{
	if (m_State == true) {
		MoveState();
	}
	else {
		Move();
	}
	m_position.y = 50;
	m_effect->SetPosition(m_position);
}

void SSPlayer::Move()
{
 	const float pl_speed = 1200.0f;//Œõ‚Ì‘¬“x 
	if (Pad(0).IsTrigger(enButtonRight)) {
		m_State = true;
		m_SelectOK = false;
		switch (m_stage) {
		case stage1:
			 m_sspoint = m_SS->m_ssPoint[1];
			m_stage = stage2;
			break;
		case stage2:
			m_sspoint = m_SS->m_ssPoint[2];
			m_stage = stage3;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)) {
		m_State = true;
		switch (m_stage) {
		case stage3:
			m_sspoint = m_SS->m_ssPoint[1];
			m_stage = stage2;
			break;
		case stage2:
			m_sspoint = m_SS->m_ssPoint[0];
			m_stage = stage1;
			break;
		}
	}
}
void SSPlayer::MoveState()
{
	CVector3 v = m_position - m_sspoint->m_position;
	if (v.LengthSq() <= 60.0f * 60.0f) {
		m_State = false;
		m_SelectOK = true;
		m_moveSpeed = CVector3::Zero;
	}
	else {
		m_moveSpeed = m_sspoint->m_position - m_position;
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.Normalize();
		m_moveSpeed *= v.LengthSq() / (350.0f * 350.0f) * 12.0;
		
	}
	m_position += m_moveSpeed;
}
