#include "stdafx.h"
#include "Human.h"
#include "Player.h"

Human::Human()
{
}


Human::~Human()
{
	DeleteGO(m_skinModelRender);
}

bool Human::Start()
{
	m_player = FindGO<Player>("Player");
	
	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_clear].Load(L"animData/unityChan/clear.tka");
	//アニメクリップをすべてロード、全部使う必要は特にないです。

	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animClip[i].SetLoopFlag(true);
	}
	//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_clear].SetLoopFlag(false);
	//trueにしたら問題がある奴だけfalseに直した。

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo",m_animClip,enAnimationClip_num,enFbxUpAxisY);

	return true;
}

void Human::Update()
{
	//Playerである光の信号を受け取ったら
	//行動を変える関数を考えています、、、

	Move();
	Turn();
	AnimeControll();
}

void Human::Move()
{
	float humanspeed = 60.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() <= 130.0f * 130.0f) {
		m_movespeed = CVector3::Zero;
	}
	else {
		m_movespeed = m_player->GetPosition() - m_position;
		m_movespeed.y = 0.0f;
		m_movespeed.Normalize();
		m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0;
		//m_movespeed = m_movespeed* GameTime().GetFrameDeltaTime();
	}
	m_position += m_movespeed;
	m_skinModelRender->SetPosition(m_position);
}

void Human::Turn()
{
	if (fabsf(m_movespeed.x) <= 0.001f    //fabsfは絶対値。m_movespeed.x&m_movespeedzが
		&&fabsf(m_movespeed.z <=0.001f)) {//0.001以下の時には何もしない。
		return;
	}
	else {
		float angle = atan2(m_movespeed.x, m_movespeed.z);
		m_qrot.SetRotation(CVector3::AxisY, angle);
	}
	m_skinModelRender->SetRotation(m_qrot);
}

void Human::AnimeControll()
{
	const float run_true = 6.0f*6.0f;
	const float walk_true = 2.0f*2.0f;
	if (m_movespeed.LengthSq() > run_true) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
	}
	else if (m_movespeed.LengthSq() > walk_true) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2);
	}
	else {
		m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2);
	}
}

void Human::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	m_font.Begin(renderContext);
	wchar_t MoveSPeeed[100];
	swprintf(MoveSPeeed, L"x%f,y%f,z%f", m_movespeed.x, m_movespeed.y, m_movespeed.z);
	m_font.Draw(MoveSPeeed, { 0,0 });
	m_font.End(renderContext);
}