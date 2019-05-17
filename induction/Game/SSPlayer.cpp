#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPoint.h"
#include "SSPlayer.h"
#include "tkEngine/light/tkPointLight.h"
#include "SSHuman.h"
SSPlayer::SSPlayer()
{
}


SSPlayer::~SSPlayer()
{
	DeleteGO(m_effect);
	DeleteGO(m_ptLight);
}
bool SSPlayer::Start()
{
	m_SS = FindGO<Stage_Select>("Stage_Select");
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	m_ptLight = NewGO<prefab::CPointLight>(0);
	m_ptLight->SetColor({ 10.0f, 10.0f, 10.0f });
	CVector3 attn = CVector3::Zero;
	attn.x = 1000.0f;
	attn.y = 5.0f;
	m_ptLight->SetAttn(attn);
	m_gamedata = &GameData::GetInstance();
	return true;
}

void SSPlayer::Update()
{
	if (m_sshuman == nullptr) {
		m_sshuman = FindGO<SSHuman>("SSHuman");
	}
	switch(m_state) {
		case enState_Stop:
			Stop();
			break;
		case enState_Move:
			Move();
			break;
		case enState_TransStage:
			TransStage();
	}
	m_effect->SetPosition(m_position);
	m_ptLight->SetPosition(m_position);
}

void SSPlayer::Move()
{
	if (Pad(0).IsTrigger(enButtonRight)) {
		if (m_stage > m_sspoint->GetStageNumber()) {
			m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage));
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)) {
		if (m_stage < m_sspoint->GetStageNumber())
			m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage));
	}
	CVector3 move = m_sspoint->GetPlayerPosition() - m_position;
	CVector3 diff = move;
	move.Normalize();
	m_position += move * m_speed * GameTime().GetFrameDeltaTime();
	if (diff.LengthSq() <= m_distance) {
		m_position = m_sspoint->GetPlayerPosition();
		m_stage = m_sspoint->GetStageNumber();
		m_state = enState_Stop;
	}
}

void SSPlayer::Stop()
{
	if (m_sshuman->GetisStop() && m_stage == m_sshuman->GetStageNumber()) {
		if (Pad(0).IsTrigger(enButtonRight)) {
			if (m_stage == GameData::enState_StageLast) {
				return;
			}
			/*if (m_gamedata->GetisStageClear(m_stage)) {*/
				m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage + 1));
				m_state = enState_Move;
			/*}*/
		}
		else if (Pad(0).IsTrigger(enButtonLeft)) {
			if (m_stage == GameData::enState_StageFirst) {
				return;
			}
			m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage - 1));
			m_state = enState_Move;
		}
		else if (Pad(0).IsTrigger(enButtonA)) {
			m_gamedata->SetStageNumber(m_stage);
			m_state = enState_TransStage;
		}
	}
	
}

void SSPlayer::TransStage()
{
	m_position.z -= m_transspeed * GameTime().GetFrameDeltaTime();
	m_timer += GameTime().GetFrameDeltaTime();
}