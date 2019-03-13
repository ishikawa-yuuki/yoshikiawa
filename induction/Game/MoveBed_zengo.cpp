#include "stdafx.h"
#include "MoveBed_zengo.h"


MoveBed_zengo::MoveBed_zengo()
{
}


MoveBed_zengo::~MoveBed_zengo()
{
	DeleteGO(m_skin);
}
bool MoveBed_zengo::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/MoveBed/MoveBed2.cmo");
	//m_skin->SetScale({ 20.0f,20.0f,20.0f });//思ったより小さかったので20倍
	m_skin->SetScale(m_scale);//Gameクラスから大きさを渡されています
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
void MoveBed_zengo::Update()
{
	if (!m_islong) {
		m_lastFramepos = m_position;
		if (m_timer > 60) {
			m_position.z += m_moveSpeed.z;
		}

		if (m_position.z >= m_protpos.z +450) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -MOVE_SPEED;
			m_timer = 0;
		}
		else if (m_position.z <= m_protpos.z - 950) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = MOVE_SPEED;
			m_timer = 0;
		}
		m_timer++;
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_position, m_rotation);
		m_GhostObject.SetPosition(m_position);
	}
	else if (m_islong) {
		m_lastFramepos = m_position;
		if (m_timer >= 60) {
			m_position.z += m_moveSpeed.z;
		}

		if (m_position.z >= m_protpos.z+450) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -MOVE_SPEED;
			m_timer = 0;
		}
		else if (m_position.z <= m_protpos.z - 1550) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = MOVE_SPEED;
			m_timer = 0;
		}
		m_timer++;
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_position, m_rotation);
		m_GhostObject.SetPosition(m_position);
	}
}

