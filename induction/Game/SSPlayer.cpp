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
		case enState_Choice:
			Choice();
			break;
		case enState_TransStage:
			TransStage();
			break;
	}
	m_effect->SetPosition(m_position);
	m_ptLight->SetPosition(m_position);
}

void SSPlayer::Move()
{
	//スティックの入力量を受け取る
	float L_Stick_X = Pad(0).GetLStickXF();
	if (Pad(0).IsTrigger(enButtonRight)
		||L_Stick_X > 0.5f) {
		if (m_stage > m_sspoint->GetStageNumber()) {
			m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage));
		}
	}
	else if (Pad(0).IsTrigger(enButtonLeft)
		||L_Stick_X < -0.5f) {
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
	float L_Stick_X = Pad(0).GetLStickXF();
	if (m_sshuman->GetisStop() && m_stage == m_sshuman->GetStageNumber()) {
		if (Pad(0).IsTrigger(enButtonRight)
			|| L_Stick_X > 0.5f) {
			if (m_stage == GameData::enState_StageLast) {
				return;
			}
			if (m_gamedata->GetisStageClear(m_stage)) {
				m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage + 1));
				m_state = enState_Move;
			}
		}
		else if (Pad(0).IsTrigger(enButtonLeft)
			|| L_Stick_X < -0.5f) {
			if (m_stage == GameData::enState_StageFirst) {
				return;
			}
			m_sspoint = m_SS->GetStagePoint(GameData::StageNumber(m_stage - 1));
			m_state = enState_Move;
		}
		else if (Pad(0).IsTrigger(enButtonA)) {
			if (m_gamedata->GetisStageCheck(m_stage)) {
				m_state = enState_Choice;
			}
			else {
				m_gamedata->SetStageNumber(m_stage);
				m_gamedata->SetCheckPoint(false);
				m_state = enState_TransStage;
			}
		}
	}
	
}

void SSPlayer::Choice()
{
	if (Pad(0).IsTrigger(enButtonA)) {
		if (m_states == enState_Yes) {
			m_gamedata->SetCheckPoint(true);
		}
		else {
			m_gamedata->SetCheckPoint(false);
		}
		m_gamedata->SetStageNumber(m_stage);
		m_state = enState_TransStage;
	}
	else {
		if (Pad(0).IsTrigger(enButtonRight)) {
			if (m_states == enState_Yes) {
				m_states = enState_No;
			}
		}
		else if (Pad(0).IsTrigger(enButtonLeft)) {
			if (m_states == enState_No) {
				m_states = enState_Yes;
			}
		}
	}
}

void SSPlayer::TransStage()
{
	m_position.z -= m_transspeed * GameTime().GetFrameDeltaTime();
	m_timer += GameTime().GetFrameDeltaTime();
}

void SSPlayer::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	if (m_state == enState_Choice) {
		CVector4 Yellow = { 1.0f,1.0f,0.0f,1.0f };
		CVector4 Transparent = { 0.5f,0.5f,0.0f,1.0f };
		const float Scale1 = 1.2f;
		const float Scale2 = 1.0;
		m_font.Begin(renderContext);
		wchar_t aaa[20];
		swprintf(aaa, L"チェックポイントからはじめますか?");
		m_font.Draw(aaa, { 0.0f,200.0f }, CVector4::White, 0.0f, Scale1);
		if (m_states == enState_Yes) {
			wchar_t aaa[20];
			swprintf(aaa, L"はい");
			m_font.Draw(aaa, { -150.0f,00.0f }, Yellow, 0.0f, Scale2);
			wchar_t aaa2[20];
			swprintf(aaa2, L"いいえ");
			m_font.Draw(aaa2, { 150.0f,00.0f }, Transparent, 0.0f, Scale2);
		}
		else {
			wchar_t aaa[20];
			swprintf(aaa, L"はい");
			m_font.Draw(aaa, { -150.0f,00.0f }, Transparent, 0.0f, Scale2);
			wchar_t aaa2[20];
			swprintf(aaa2, L"いいえ");
			m_font.Draw(aaa2, { 150.0f,00.0f }, Yellow, 0.0f, Scale2);
		}
		m_font.End(renderContext);
	}
}
