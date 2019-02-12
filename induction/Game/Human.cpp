#include "stdafx.h"
#include "Human.h"
#include "Player.h"

Human::Human()
{
}


Human::~Human()
{
}

bool Human::Start()
{
	m_player = FindGO<Player>("Player");
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");

	return true;
}

void Human::Update()
{
	Move();
}

void Human::Move()
{
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() <= 100.0f * 100.0f) {
		m_movespeed = CVector3::Zero;
	}
	else {
		m_movespeed = m_player->GetPosition() - m_position;
		m_movespeed.y = 0.0f;
		m_movespeed.Normalize();
		m_movespeed *= diff.LengthSq() / (300.0f * 300.0f) * 12.0;
	}
	m_position += m_movespeed;
	m_skinModelRender->SetPosition(m_position);
}