#include "stdafx.h"
#include "MistEnemy.h"
#include "Player.h"
#include "Human.h"
#include "Light_Object.h"
#include "Light_Object2.h"

MistEnemy::MistEnemy()
{
}


MistEnemy::~MistEnemy()
{
	DeleteGO(m_effect);
}

bool MistEnemy::Start()
{
	m_player = FindGO<Player>("Player");
	m_human = FindGO<Human>("Human");
	m_lightObject = FindGO<Light_Object>("LightObject");
	m_lightObject2 = FindGO<Light_Object2>("LightObject2");

	m_startpos = m_position;
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/kuromoya.efk");
	m_effect->SetScale({ 40.0f, 40.0f, 40.0f });
	return true;
}

void MistEnemy::Update()
{
	Atari();
	m_position += m_moveSpeed;
	m_effect->SetPosition(m_position);
}

void MistEnemy::Atari()
{
	//何か当たった時の処理。行動のトリガーに引っかかってない時の処理もここに書いてあります
	CVector3 diff_p = m_player->GetPosition() - m_position; //diff_pはプレイヤーとの距離
	CVector3 diff_h = m_human->GetPosition() - m_position;  //diff_hは人との距離
	CVector3 diff_s = m_startpos - m_position;              //diff_sはスタート地点との距離
	CVector3 diff_l = m_lightObject->GetPosition() - m_position;//diff_lはランタンとの距離
	CVector3 diff_l2 = m_lightObject2->GetPosition() - m_position;//上記、番号が変わっただけ

	diff_p.y = 0.0f;
	diff_h.y = 0.0f;
	diff_s.y = 0.0f;
	diff_l.y = 0.0f;
	diff_l2.y = 0.0f;

	if (m_state == enNormal) {
		if(diff_l.LengthSq() <= 250.0f*250.0f
			&&m_lightObject->GetLightOn() == true){
			m_state = enPlayer;
			m_escape_flag = true;
			if (m_taking_flag) {
				m_taking_flag = false;
			}
		}
		else if (diff_l2.LengthSq() <= 150.0f*150.0f
			&&m_lightObject2->GetLightOn()) {
			m_state = enPlayer;
			m_escape_flag = true;
			if (m_taking_flag) {
				m_taking_flag = false;
			}
		}
		else if (diff_p.LengthSq() <= 100.0f*100.0f
			|| m_escape_flag) {
			m_state = enPlayer;
			m_escape_flag = true;
			if (m_taking_flag) {
				m_taking_flag = false;
			}
		}
		else if (diff_h.LengthSq() <= 100.0f*100.0f
			&&!m_escape_flag) {
			m_state = enHuman;
			m_taking_flag = true;
		}
		else {
			diff_h.Normalize();
			diff_h *= 5.0f;
			m_moveSpeed = diff_h;
		}
	}
	else if(m_state == enPlayer) {
		diff_p.Normalize();
		diff_p *= -15.0f;
		m_moveSpeed = diff_p;
		m_timer++;

		if (m_timer >= 400) {
			m_timer = 0;
			m_escape_flag = false;
			m_state = enNormal;
		}
	}
	else if (m_state == enHuman) {
		diff_s.Normalize();
		diff_s *= 4.0f;
		m_moveSpeed = diff_s;

		if (diff_p.LengthSq() <= 130.0f*130.0f
			|| m_escape_flag) {
			m_state = enPlayer;
			m_escape_flag = true;
			if (m_taking_flag) {
				m_taking_flag = false;
			}
		}
	}
	time++;
	if (time <50) {
		//m_moveSpeed.y += 0.3f;
	}
	else if (time<100) {
		//m_moveSpeed.y -= 0.3f;
	}
	else {
		time = 0;
	}
}