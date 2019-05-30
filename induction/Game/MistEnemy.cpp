#include "stdafx.h"
#include "MistEnemy.h"
#include "Player.h"
#include "Human.h"
#include "Light_Object.h"
#include "Game.h"

MistEnemy::MistEnemy()
{
}


MistEnemy::~MistEnemy()
{
	if (m_effect != nullptr) {
		DeleteGO(m_effect);
	}
	if (m_sound != nullptr) {
		DeleteGO(m_sound);
	}
}

bool MistEnemy::Start()
{
	m_player = FindGO<Player>("Player");
	m_human = FindGO<Human>("Human");
	
	m_startpos = m_position;
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/kuromoya.efk");
	m_effect->SetScale({ 40.0f, 40.0f, 40.0f });
	m_sound = NewGO<prefab::CSoundSource>(0);
	m_sound->Init(L"sound/MistEnemy.wav");
	/*m_sound->SetPosition(m_position);*/
	m_sound->SetVolume(0.0f);
	m_sound->Play(true);
	m_game = FindGO<Game>("Game");
	return true;
	
}

void MistEnemy::Update()
{
	if (m_game->GetisClear()) {
		if (m_effect != nullptr) {
			DeleteGO(m_effect);
			m_effect = nullptr;
			DeleteGO(m_sound);
			m_sound = nullptr;
		}
	}
	else {
		//音m_moyaがtrueなら音が出る
		if (m_moya && m_sound != nullptr) {
			m_sound->SetVolume(1.0f);
		}
		else if (m_sound != nullptr) {
			m_sound->SetVolume(0.0f);
		}
		Atari();
		m_position += m_moveSpeed * GameTime().GetFrameDeltaTime();
		m_effect->SetPosition(m_position);
	}
}

void MistEnemy::Atari()
{
	
	//何か当たった時の処理。行動もここ。
	CVector3 diff_p = m_player->GetPosition() - m_position; //diff_pはプレイヤーとの距離
	CVector3 diff_h = m_human->GetPosition() - m_position;  //diff_hは人との距離
	CVector3 diff_s = m_startpos - m_position;              //diff_sはスタート地点との距離
	CVector3 diff_ph = m_human->GetPosition() - m_player->GetPosition(); //プレイヤーとヒトの距離
	
	diff_p.y = 0.0f;
	diff_h.y = 0.0f;
	diff_s.y = 0.0f;
	if (!m_human->GetisDead()) {
		if (m_state == enNormal) {
			auto game = FindGO<Game>("Game");
			const auto& lightList = game->GetLightObjectList();
			for (int i = 0; i < lightList.size(); i++) {
				CVector3 diff_l = lightList[i]->GetPosition() - m_position;//diff_lはランタンとの距離
				
				if (diff_l.LengthSq() <= 500.0f * 500.0f
					&& lightList[i]->GetLightOn() == true
					||m_escape_flag) {
					m_state = enPlayer;
					m_escape_flag = true;
					if (m_taking_flag) {
						m_taking_flag = false;
					}
					if (!iltutai) {
						prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
						effect->Play(L"effect/kuromoya_kieru.efk");
						effect->SetPosition(m_position);
						iltutai = true;
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
					if (!iltutai) {
						prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
						effect->Play(L"effect/kuromoya_kieru.efk");
						effect->SetPosition(m_position);
						iltutai = true;
					}
				}
				else if (diff_h.LengthSq() <= 120.0f * 120.0f
					&& !m_escape_flag) {
					m_state = enHuman;
					m_taking_flag = true;
				}
				else if (m_human->GetismistEnemy()) {
					if (!m_moya) {
						CVector3 pos = m_human->GetPosition();
						pos.Normalize();
						pos *= 400.0f;
						m_position = pos + m_human->GetPosition();
						m_position.y = 100.0f;
						m_moya = true;
					}
					else {
						//diff_hを直接いじってはいけないのでdifh制作
						CVector3 difh = diff_h;
						difh.Normalize();
						difh *= 120.0f;
						m_moveSpeed = difh;
						m_taking_flag = false;
					}
				}
				else {
					CVector3 difh = diff_h;
					difh.Normalize();
					difh *= 120.0f;
					m_moveSpeed = difh;
					if (m_moya) {
						m_kaerutimer--;
					}
					if (m_kaerutimer < 0) {
						m_state = enPlayer;
						m_kaerutimer = Random().GetRandInt() % 500 + 200;
						if (!iltutai) {
							prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
							effect->Play(L"effect/kuromoya_kieru.efk");
							effect->SetPosition(m_position);
							iltutai = true;
						}
					}
				}

			}
		}
		else if (m_state == enPlayer) {
			m_position = m_startpos;
			if (m_human->GetismistEnemy()) {
				iltutai = false;
				m_escape_flag = false;
				m_state = enNormal;
			}
			if (m_Deathtimer != 0.0f) {
				m_Deathtimer = 0.0f;
			}
			if (m_moya) {
				m_moya = false;
			}
		}
		else if (m_state == enHuman) {
			//diff_pの数値を直接いじってはいけないのでdifpを作成。
			CVector3 difp = diff_p;
			difp.Normalize();
			difp *= -300.0f;
			m_moveSpeed = difp;
			m_Deathtimer += 50.0f * GameTime().GetFrameDeltaTime();

			//捕まった状態の時は光とヒトの距離で計算します。
			//MisteEnemyが壁に入ったらどうしようもないので…
			if (diff_ph.LengthSq() <= 150.0f * 150.0f
				&&!m_player->GetColor()
				|| m_escape_flag) {
				m_state = enPlayer;
				m_escape_flag = true;
				if (!iltutai) {
					prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
					effect->Play(L"effect/kuromoya_kieru.efk");
					effect->SetPosition(m_position);
					iltutai = true;
				}
				if (m_taking_flag) {
					m_taking_flag = false;
				}
			}

			if (m_Deathtimer > 400.0f) {
				m_Deathtimer = 0.0f;
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