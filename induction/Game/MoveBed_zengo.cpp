#include "stdafx.h"
#include "MoveBed_zengo.h"
#include "Player.h"

MoveBed_zengo::MoveBed_zengo()
{
}


MoveBed_zengo::~MoveBed_zengo()
{
	DeleteGO(m_skin);
}

bool MoveBed_zengo::Start()
{
	m_player = FindGO<Player>("Player");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/MoveBed/MoveBed2.cmo");
	//m_skin->SetScale({ 20.0f,20.0f,20.0f });//Žv‚Á‚½‚æ‚è¬‚³‚©‚Á‚½‚Ì‚Å20”{
	m_skin->SetScale(m_scale);//GameƒNƒ‰ƒX‚©‚ç‘å‚«‚³‚ð“n‚³‚ê‚Ä‚¢‚Ü‚·
	m_skin->SetRotation(m_rotation);
	m_StaticObject.CreateBox(
		m_position,
		m_rotation,
		{ 430.0f, 80.0f, 300.0f }
	);
	m_GhostObject.CreateBox(
		m_position,
		m_rotation,
		{ 435.0f, 85.0f, 305.0f }
	);
	return true;
}
void MoveBed_zengo::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 0.04f;
	}
	else if (diff.LengthSq() < range * 1.5) {
		m_volume = 0.02f;
	}
	else if (diff.LengthSq() < range * 3) {
		m_volume = 0.01f;
	}
	else {
		m_volume = 0.0f;
	}
}
void MoveBed_zengo::Update()
{
	m_lastFramepos = m_position;
	if (m_timer >= 2.0f) {
		prefab::CSoundSource*sound = NewGO<prefab::CSoundSource>(0);
		sound->Init(L"sound/movebed.wav");
		sound->SetPosition(m_position);
		Range();
		sound->SetVolume(m_volume);
		sound->Play(false);
		m_position.z += m_moveSpeed.z * GameTime().GetFrameDeltaTime();
	}
	if (!m_islong) {
		

		if (m_position.z > m_protpos.z ) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -MOVE_SPEED;
			m_timer = 0.0f;
		}
		else if (m_position.z < m_protpos.z - 500) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = MOVE_SPEED;
			m_timer = 0.0f;
		}
		
	}
	else if (m_islong) {
		if (m_position.z > m_protpos.z) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -MOVE_SPEED;
			m_timer = 0.0f;
		}
		else if (m_position.z < m_protpos.z -1020) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = MOVE_SPEED;
			m_timer = 0.0f;
		}
	}
	
	m_timer += GameTime().GetFrameDeltaTime();
	m_skin->SetPosition(m_position);
	m_StaticObject.SetPositionAndRotation(m_position, m_rotation);
	m_GhostObject.SetPosition(m_position);
}

