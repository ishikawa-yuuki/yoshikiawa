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
		//��m_moya��true�Ȃ特���o��
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
	
	//���������������̏����B�s���������B
	CVector3 diff_p = m_player->GetPosition() - m_position; //diff_p�̓v���C���[�Ƃ̋���
	CVector3 diff_h = m_human->GetPosition() - m_position;  //diff_h�͐l�Ƃ̋���
	CVector3 diff_s = m_startpos - m_position;              //diff_s�̓X�^�[�g�n�_�Ƃ̋���
	CVector3 diff_ph = m_human->GetPosition() - m_player->GetPosition(); //�v���C���[�ƃq�g�̋���
	
	diff_p.y = 0.0f;
	diff_h.y = 0.0f;
	diff_s.y = 0.0f;
	if (!m_human->GetisDead()) {
		if (m_state == enNormal) {
			auto game = FindGO<Game>("Game");
			const auto& lightList = game->GetLightObjectList();
			for (int i = 0; i < lightList.size(); i++) {
				CVector3 diff_l = lightList[i]->GetPosition() - m_position;//diff_l�̓����^���Ƃ̋���
				
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
						//diff_h�𒼐ڂ������Ă͂����Ȃ��̂�difh����
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
			//diff_p�̐��l�𒼐ڂ������Ă͂����Ȃ��̂�difp���쐬�B
			CVector3 difp = diff_p;
			difp.Normalize();
			difp *= -300.0f;
			m_moveSpeed = difp;
			m_Deathtimer += 50.0f * GameTime().GetFrameDeltaTime();

			//�߂܂�����Ԃ̎��͌��ƃq�g�̋����Ōv�Z���܂��B
			//MisteEnemy���ǂɓ�������ǂ����悤���Ȃ��̂Łc
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
		//human�����񂾂Ƃ��̏����B
		m_state = enNormal;
		m_moveSpeed = CVector3::Zero;
	}
}