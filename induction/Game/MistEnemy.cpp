#include "stdafx.h"
#include "MistEnemy.h"
#include "Player.h"
#include "Human.h"
#include "Light_Object.h"
#include "Light_Object2.h"
#include "Game.h"

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
	
	m_startpos = m_position;
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/kuromoya.efk");
	m_effect->SetScale({ 40.0f, 40.0f, 40.0f });
	return true;
}

void MistEnemy::Update()
{
	Atari();
	m_position += m_moveSpeed * GameTime().GetFrameDeltaTime();
	m_effect->SetPosition(m_position);
}

void MistEnemy::Atari()
{
	//何か当たった時の処理。行動もここ。
	CVector3 diff_p = m_player->GetPosition() - m_position; //diff_pはプレイヤーとの距離
	CVector3 diff_h = m_human->GetPosition() - m_position;  //diff_hは人との距離
	CVector3 diff_s = m_startpos - m_position;              //diff_sはスタート地点との距離
	
	diff_p.y = 0.0f;
	diff_h.y = 0.0f;
	diff_s.y = 0.0f;
	if (!m_human->GetisDead()) {
		if (m_state == enNormal) {
			auto game = FindGO<Game>("Game");
			const auto& lightList = game->GetLightObjectList();
			for (int i = 0; i < lightList.size(); i++) {
				CVector3 diff_l = lightList[i]->GetPosition() - m_position;//diff_lはランタンとの距離

				if (diff_l.LengthSq() <= 250.0f * 250.0f
					&& lightList[i]->GetLightOn() == true) {
					m_state = enPlayer;
					m_escape_flag = true;
					if (m_taking_flag) {
						m_taking_flag = false;
					}
				
				}
				else if (diff_p.LengthSq() <= 120.0f * 120.0f
					&&!m_player->GetColor()
					|| m_escape_flag) {
					m_state = enPlayer;
					m_escape_flag = true;
					if (m_taking_flag) {
						m_taking_flag = false;
					}
				}
				else if (diff_h.LengthSq() <= 120.0f * 120.0f
					&& !m_escape_flag) {
					m_state = enHuman;
					m_taking_flag = true;
				}
				else if (m_human->GetismistEnemy()) {
					CVector3 dif = diff_h;
					dif.Normalize();
					dif *= 1200.0f;
					m_moveSpeed = dif;
					//m_taking_flag = false;
				}
				else {
					m_moveSpeed = CVector3::Zero;
				}
			}
		}
		else if (m_state == enPlayer) {
			diff_p.Normalize();
			diff_p *= -900.0f;
			m_moveSpeed = diff_p;
			m_timer++;
			if (m_timer >= 400) {
				m_timer = 0;
				m_escape_flag = false;
				m_state = enNormal;
			}
			if (Deathtimer != 0) {
				Deathtimer = 0;
			}
		}
		else if (m_state == enHuman) {
			diff_s.Normalize();
			diff_s *= 300.0f;
			m_moveSpeed = diff_s;
			Deathtimer += 60 * GameTime().GetFrameDeltaTime();

			if (diff_p.LengthSq() <= 130.0f * 130.0f
				&&!m_player->GetColor()
				|| m_escape_flag) {
				m_state = enPlayer;
				m_escape_flag = true;
				if (m_taking_flag) {
					m_taking_flag = false;
				}
			}

			if (Deathtimer > 300) {
				Deathtimer = 0;
				m_human->isKill();
			}
		}
	}
	else
	{
		//humanが死んだときの処理。
		m_state = enNormal;
		m_moveSpeed = CVector3::Zero;
	}
}