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
	m_skin->Init(L"modelData/MoveBed/MoveBed.cmo");
	m_skin->SetScale({ 20.0f,20.0f,20.0f });//évÇ¡ÇΩÇÊÇËè¨Ç≥Ç©Ç¡ÇΩÇÃÇ≈20î{
	m_StaticObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{200.0f, 200.0f, 200.0f}
	);
	m_GhostObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{ 200.0f, 200.0f, 200.0f }
	);
	return true;
}
void MoveBed::Update()
{
	m_lastFramepos = m_position;
	if (m_position.x <= m_protpos.x - 200) {
		m_position.x = 600;
		m_moveSpeed.x = 2.0f;
	}
	else if(m_position.x >= m_protpos.x + 200 ){
		m_position.x = 1000;
		m_moveSpeed.x = -2.0f;
	}
	m_position.x += m_moveSpeed.x;
	m_skin->SetPosition(m_position);
	m_StaticObject.SetPositionAndRotation(m_position, CQuaternion::Identity);
	m_GhostObject.SetPosition(m_position);
}
