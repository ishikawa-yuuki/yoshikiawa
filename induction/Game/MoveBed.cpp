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
		m_ppos,
		CQuaternion::Identity,
		{430.0f, 80.0f, 300.0f}
	);
	m_GhostObject.CreateBox(
		m_ppos,
		CQuaternion::Identity,
		{ 435.0f, 85.0f, 305.0f }
	);
	m_skin->SetShadowReceiverFlag(true);
	return true;
}
void MoveBed::Update()
{
	m_lastFramepos = m_position;
	if (m_timer >= 60) {
		m_position.x += m_moveSpeed.x;
	}
	if (m_position.x <= m_protpos.x - 850) {
		m_position.x = m_lastFramepos.x;
		m_moveSpeed.x = MOVE_SPEED;
		m_timer = 0;
	}
	else if(m_position.x >= m_protpos.x + 900 ){
		m_position.x = m_lastFramepos.x;
		m_moveSpeed.x = -MOVE_SPEED;
		m_timer = 0;
	}
	m_timer++;
	m_ppos = m_position;//ボックス形状の調整
	//m_ppos.z += 100;
	m_ppos.y += 15;
	//m_ppos.x -= 50;
	m_skin->SetPosition(m_position);
	m_StaticObject.SetPositionAndRotation(m_ppos, CQuaternion::Identity);
	m_GhostObject.SetPosition(m_ppos);
}
