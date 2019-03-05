#include "stdafx.h"
#include "SSPlayer.h"
#include "SSHuman.h"

SSHuman::SSHuman()
{
}


SSHuman::~SSHuman()
{
	DeleteGO(m_skin);
}
bool SSHuman::Start()
{
	m_ssplayer = FindGO<SSPlayer>("SSPlayer");
	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	//アニメクリップをすべてロード、全部使う必要は特にないです。

	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animClip[i].SetLoopFlag(true);
	}
	//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

	

	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/unityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_position.x -= 50;
	m_skin->SetPosition(m_position);
	return true;
}

void SSHuman::Update()
{
	Move();
	Turn();
	AnimeControll();
}

void SSHuman::Move()
{
	CVector3 diff = m_position - m_ssplayer->GetPosition();
	if (diff.LengthSq() <= 100.0f * 100.0f) {
		m_movespeed = CVector3::Zero;
	}
	else {
		m_movespeed = m_ssplayer->GetPosition() - m_position;
		m_movespeed.y = 0.0f;
		m_movespeed.Normalize();
		m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0f;
	}
	m_position += m_movespeed ;
	m_skin->SetPosition(m_position);
}

void SSHuman::Turn()
{
	if (fabsf(m_movespeed.x) <= 0.001f    //fabsfは絶対値。m_movespeed.x&m_movespeedzが
		&&fabsf(m_movespeed.z) <= 0.001f) {//0.001以下の時には何もしない。
		return;
	}
	else {
		float angle = atan2(m_movespeed.x, m_movespeed.z);
		m_qrot.SetRotation(CVector3::AxisY, angle);
	}
	m_skin->SetRotation(m_qrot);
}

void SSHuman::AnimeControll()
{
	const float run_true = 7.0f*7.0f;
	const float walk_true = 1.0f*1.0f;
	if (m_movespeed.LengthSq() > run_true) {
		m_skin->PlayAnimation(enAnimationClip_run, 0.2);
	}
	else if (m_movespeed.LengthSq() > walk_true) {
		m_skin->PlayAnimation(enAnimationClip_walk, 0.2);
	}
	else {
		m_skin->PlayAnimation(enAnimationClip_idle, 0.2);
		m_qrot.SetRotation(CVector3::AxisY, 135);
	
	    m_skin->SetRotation(m_qrot);
	}
}

void SSHuman::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	m_font.Begin(renderContext);
	wchar_t MoveSPeeed[100];
	swprintf(MoveSPeeed, L"x%f,y%f,z%f", m_movespeed.x, m_movespeed.y, m_movespeed.z);
	m_font.Draw(MoveSPeeed, { 0,0 });
	m_font.End(renderContext);
}