#include "stdafx.h"
#include "Enemy.h"
#include "Human.h"
#include "Game.h"

Enemy::Enemy()
//m_pathMoveLoop(this, m_movePath)
{
}
Enemy::~Enemy()
{
	DeleteGO(m_skin);
}
bool Enemy::Start()
{
	m_human = FindGO<Human>("Human");
	m_game = FindGO<Game>("Game");


	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");

	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animClip[i].SetLoopFlag(true);
	}
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/BlackUnityChan.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisY);
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);
	return true;
}
void Enemy::NotifyRestart()
{
	m_isFindPlayer = false;
}
void Enemy::SearchPlayer()
{
	CVector3 pos = m_human->GetPosition() - m_position;
	if (pos.LengthSq() < 400.0f*400.0f) {
		//視野角を判定。
		pos.Normalize();
		float angle = acosf(pos.Dot(m_forward));
		if (fabsf(angle) < CMath::PI * 0.25f) {
			//視野角45度以内。
			//ゲームにゲームオーバーを通知。
			m_human = FindGO<Human>("Human");
			m_human->isKill();
			m_isFindPlayer = true;
		}
	}
}
void Enemy::Move()
{
	m_timer += GameTime().GetFrameDeltaTime();
	switch(m_state) {
	case State1:
		
		m_movespeed.x = MOVE_SPEED;
		if (m_timer == 450) {
			m_timer = 0;
			m_state = State2;
		}
	
		break;
	case State2:
		
		m_movespeed.z = MOVE_SPEED;
		if (m_timer == 500) {
			m_timer = 0;
			m_state = State3;
		}
		break;
	case State3:
		
		m_movespeed.x = -MOVE_SPEED;
		if (m_timer == 450) {
			m_timer = 0;
			m_state = State4;
		}
		break;
	case State4:
		
		m_movespeed.z = -MOVE_SPEED;
		if (m_timer == 500) {
			m_timer = 0;
			m_state = State1;
		}
		break;
	}
	if (m_timer == 0) {
		m_movespeed = CVector3::Zero;
	}
    CVector3 pos = m_movespeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
	m_charaCon.SetPosition(m_position);
	m_skin->SetPosition(m_position);
}
void Enemy::Turn()
{
	if (fabsf(m_movespeed.x) <= 0.001f    //fabsfは絶対値。m_movespeed.x&m_movespeedzが
		&&fabsf(m_movespeed.z) <= 0.001f) {//0.001以下の時には何もしない。
		return;
	}
	else {
		float angle = atan2(m_movespeed.x, m_movespeed.z);
		m_rotation.SetRotation(CVector3::AxisY, angle);
	}
	m_skin->SetRotation(m_rotation);
}
void Enemy::Update()
{
	if (!m_human->GetisDead()) {
		Move();
		Turn();
		SearchPlayer();
		m_skin->PlayAnimation(enAnimationClip_walk);
		//m_pathMoveLoop.Update();
	}
	else {
		m_skin->PlayAnimation(enAnimationClip_idle);
	}
	//m_skin->SetPosition(m_position);

	auto mRot = CMatrix::Identity;
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
}