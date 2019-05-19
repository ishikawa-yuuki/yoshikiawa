#include "stdafx.h"
#include "Hill.h"
#include "Human.h"
#define _USE_MATH_DEFINES //M_PI(円周率)を呼び出し
#include <math.h>
Hill::Hill()
{
}


Hill::~Hill()
{
	DeleteGO(m_skinModelRender);
}

bool Hill::Start()
{
	m_human = FindGO<Human>("Human");

	m_animeClip[enAnimationClip_move].Load(L"animData/Hill/move.tka");

	//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。
	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animeClip[i].SetLoopFlag(true);
	}
	

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Hill/Hill.cmo",m_animeClip,enAnimationClip_num,enFbxUpAxisZ);
	m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.2);
	return true;
}

void Hill::Update()
{
	if (m_human == nullptr) {
		m_human = FindGO<Human>("Human");
		return;
	}
	switch (m_state) {
	case enState_Stop:
		Stop();
		break;
	case enState_Move:
		Move();
		break;
	}
	Turn();
	Kill();
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
}

void Hill::Move()
{
	const float Distance = 300.0f * 300.0f;
	const float Speed = 150.0f * 150.0f;

	CVector3 diff = m_human->GetPosition() - m_position;
	if (diff.LengthSq() >= Distance) {
		m_state = enState_Stop;
	}
	else {
		diff.Normalize();
		m_movespeed = diff * Speed * GameTime().GetFrameDeltaTime();
		m_position += m_movespeed;
	}
}

void Hill::Stop()
{
	const float Distance = 150.0f * 150.0f;

	CVector3 diff = m_human->GetPosition() - m_position;
	if (diff.LengthSq() <= Distance) {
		m_state = enState_Move;
	}
}

void Hill::Turn()
{
	CVector3 speed = m_movespeed;
	speed.y = 0.0f;
	speed.Normalize();
	m_rotation.SetRotationDeg(CVector3::AxisY, atan2f(speed.x, speed.z));
	m_parallel = CVector3::AxisZ;
	m_rotation.Multiply(m_parallel);
}

void Hill::Kill()
{
	const float Distance = 30.0f * 30.0f;
	const float Degree = 30.0f;

	CVector3 diff = m_human->GetPosition() - m_position;
	if (diff.LengthSq() <= Distance) {
		diff.Normalize();
		float dot = m_parallel.Dot(diff);
		if (dot * M_PI <= Degree) {
			m_human->isKill();
		}
	}
}