#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPoint.h"
#include "SSPlayer.h"
#include "Stage_Number.h"
#include "tkEngine/light/tkPointLight.h"

SSPlayer::SSPlayer()
{
}


SSPlayer::~SSPlayer()
{
	DeleteGO(m_effect);
}
bool SSPlayer::Start()
{
	NewGO<Stage_Number>(0,"Stage_Number");
	m_SS = FindGO<Stage_Select>("Stage_Select");
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	m_sspoint = m_SS->m_ssPoint[0];
	m_ptLight = NewGO<prefab::CPointLight>(0);
	m_ptLight->SetColor({ 10.0f, 10.0f, 10.0f });
	CVector3 attn = CVector3::Zero;
	attn.x = 1000.0f;
	attn.y = 5.0f;
	m_ptLight->SetAttn(attn);

	return true;
}

void SSPlayer::Update()
{
	
	if (m_State == true) {
		MoveState();
	}
	 if(m_SelectOK == true){
		Move();
	}
	m_position.y = 50;
	m_position.z = -100;
	m_effect->SetPosition(m_position);
	m_ptLight->SetPosition(m_position);
}

void SSPlayer::Move()
{

	
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
		m_SelectOK = false;
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
	m_v = m_position - m_sspoint->m_position;
	m_v.z = 0.0f;
	if (m_v.LengthSq() <= 60.0f * 60.0f) {
		m_moveSpeed = CVector3::Zero;
		m_State = false;
	}
    if (m_v.LengthSq() <= 250.0f * 250.0f) {
			m_SelectOK = true;
			
	}
	else {
			m_moveSpeed = m_sspoint->m_position - m_position;
			m_moveSpeed.y = 0.0f;
			m_moveSpeed.Normalize();
			m_moveSpeed *= m_v.LengthSq() / (350.0f * 350.0f) * 12.0;
	}
	m_position += m_moveSpeed;
	
}
