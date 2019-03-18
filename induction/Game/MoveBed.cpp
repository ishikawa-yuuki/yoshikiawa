#include "stdafx.h"
#include "MoveBed.h"


MoveBed::MoveBed()
{
}


MoveBed::~MoveBed()
{
	DeleteGO(m_skin);
}
bool MoveBed::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/MoveBed/MoveBed1.cmo");
	//m_skin->SetScale({ 20.0f,20.0f,20.0f });//思ったより小さかったので20倍
	m_skin->SetScale(m_scale);//Gameクラスから大きさを渡されています
	m_StaticObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{430.0f, 80.0f, 300.0f}
	);
	m_GhostObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{ 435.0f, 85.0f, 305.0f }
	);
	m_skin->SetShadowReceiverFlag(true);
	return true;
}
void MoveBed::Update()
{
	if (!m_sorry) {
		m_lastFramepos = m_position;
		if (m_timer >= 2.0f) {
			m_position.x += m_moveSpeed.x*GameTime().GetFrameDeltaTime();
		}
		if (m_position.x <= m_protpos.x - 370) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = MOVE_SPEED;
			m_timer = 0;
		}
		else if (m_position.x >= m_protpos.x + 475) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = -MOVE_SPEED;
			m_timer = 0;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_position, CQuaternion::Identity);
		m_GhostObject.SetPosition(m_position);
	}
	else if(m_sorry) 
	{
		m_lastFramepos = m_position;
		if (m_timer >= 2.0f) {
			m_position.x += m_moveSpeed.x*GameTime().GetFrameDeltaTime();
		}
		if (m_position.x <= m_protpos.x - 375) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = MOVE_SPEED;
			m_timer = 0;
		}
		else if (m_position.x >= m_protpos.x + 445) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = -MOVE_SPEED;
			m_timer = 0;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_position, CQuaternion::Identity);
		m_GhostObject.SetPosition(m_position);
	}
}
