#include "stdafx.h"
#include "SSPlayer.h"
#include "SSHuman.h"
#include "Stage_Select.h"
#include "SSPoint.h"
SSHuman::SSHuman()
{
}


SSHuman::~SSHuman()
{
	DeleteGO(m_skin);
}
bool SSHuman::Start()
{
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);

	m_animClip[enAnimationClip_idle].Load(L"animData/Human/idle.tka");
	//m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/Human/run.tka");
	//m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	//m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/Human/KneelDown.tka");
	m_animClip[enAnimationClip_clear].Load(L"animData/Human/clear.tka");
	//アニメクリップをすべてロード、全部使う必要は特にないです。


	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animClip[i].SetLoopFlag(true);
	}
	//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

	//m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	//m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_clear].SetLoopFlag(false);
	//trueにしたら問題がある奴だけfalseに直した。

	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Human/Human.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
	m_skin->SetPosition(m_position);
	m_stageselect = FindGO<Stage_Select>("Stage_Select");
	return true;
}

void SSHuman::Update()
{
	if (m_ssplayer == nullptr) {
		m_ssplayer = FindGO<SSPlayer>("SSPlayer");
		return;
	}
	switch (m_state) {
	case SSPlayer::enState_Stop:
		Stop();
		break;
	case SSPlayer::enState_Move:
		Move();
		break;
	case SSPlayer::enState_TransStage:
		TransStage();
		break;
	}
	Animation_Turn();
	m_skin->SetPosition(m_position);
}

void SSHuman::Stop()
{
	if (m_ssplayer->GetisMoveHuman()) {
		m_state = SSPlayer::enState_TransStage;
		TransStage();
	}
	else if (m_stage != m_ssplayer->GetStagenum()) {
		m_sspoint = m_stageselect->GetStagePoint(m_ssplayer->GetStagenum());
		m_stage = m_ssplayer->GetStagenum();
		m_state = SSPlayer::enState_Move;
	}
}

void SSHuman::Move()
{
	m_movespeed = m_sspoint->GetHumanPosition() - m_position;
	CVector3 diff = m_movespeed;
	m_movespeed.Normalize();
	m_movespeed *= m_ssplayer->m_speed;
	m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
	if (diff.LengthSq() <= m_ssplayer->m_distance) {
		m_position = m_sspoint->GetHumanPosition();
		m_charaCon.SetPosition(m_position);
		m_state = SSPlayer::enState_Stop;
	}
}

void SSHuman::Animation_Turn()
{
	const float run_true = 7.0f*7.0f;
	const float walk_true = 1.0f*1.0f;
	const float time = 0.2f;
	if (m_movespeed.LengthSq() > walk_true && m_state != SSPlayer::enState_Stop) {
		m_skin->PlayAnimation(enAnimationClip_run, time);
		CVector3 pos = m_movespeed;
		pos.y = 0.0f;
		pos.Normalize();
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY, atan2(pos.x, pos.z));
		m_skin->SetRotation(rot);

	}
	else {
		m_skin->PlayAnimation(enAnimationClip_idle, time);
		m_skin->SetRotation(m_rotation);
	}
}

void SSHuman::TransStage()
{
	m_movespeed = CVector3::Zero;
	m_movespeed.z = -m_ssplayer->m_transspeed;
	m_position += m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
}

/*void SSHuman::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	m_font.Begin(renderContext);
	wchar_t MoveSPeeed[100];
	swprintf(MoveSPeeed, L"x%f,y%f,z%f", m_movespeed.x, m_movespeed.y, m_movespeed.z);
	m_font.Draw(MoveSPeeed, { 0,0 });
	m_font.End(renderContext);
}*/
