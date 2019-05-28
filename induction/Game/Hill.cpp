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
		if (!kill) {
		Turn();
	     }
	Kill();
	
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
}

void Hill::Move()
{
	const float Distance = 700.0f * 700.0f;
	const float Speed = 100.0f;

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
	const float Distance = 400.0f * 400.0f;

	CVector3 diff = m_human->GetPosition() - m_position;
	if (diff.LengthSq() <= Distance) {
		m_state = enState_Move;
	}
}

void Hill::Turn()
{/*
	CVector3 speed = m_movespeed;
	speed.y = 0.0f;
	speed.Normalize();
	m_rotation.SetRotationDeg(CVector3::AxisY, atan2f(speed.x, speed.z));
	m_parallel = CVector3::AxisZ;
	m_rotation.Multiply(m_parallel);*/
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	m_rotation.SetRotation(CVector3::AxisY, angle);
}
void Hill::Kill()
{
	if (m_num == 1) {
		const float Distance = 100.0f * 100.0f;
		const float Degree = 60.0f;

		CVector3 diff = m_human->GetPosition() - m_position;
		if (diff.LengthSq() <= Distance) {
			diff.Normalize();
			float angle = acosf(m_parallel.Dot(diff));
			if (angle * M_PI <= Degree) {
				m_human->isKill();
				kill = true;
				m_movespeed = CVector3::Zero;
			}
		}
	}
	else {


		const float Distance = 30.0f * 30.0f;
		const float Degree = 30.0f;

		CVector3 diff = m_human->GetPosition() - m_position;
		if (diff.LengthSq() <= Distance) {
			diff.Normalize();
			float angle = acosf(m_parallel.Dot(diff));
			if (angle * M_PI <= Degree) {
				m_human->isKill();
				kill = true;
				m_movespeed = CVector3::Zero;
			}
		}
	}
}