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
	m_StaticObject.CreateBox(
		m_ppos,
		CQuaternion::Identity,
		{ 450.0f, 100.0f, 500.0f }
	);
	m_GhostObject.CreateBox(
		m_ppos,
		CQuaternion::Identity,
		{ 455.0f, 105.0f, 505.0f }
	);
	return true;
}
void MoveBed_zengo::Update()
{
	if (!m_islong) {
		m_lastFramepos = m_position;
		if (m_position.z >= m_protpos.z) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -4.0f;
		}
		else if (m_position.z <= m_protpos.z - 600) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = +4.0f;
		}
		m_position.z += m_moveSpeed.z;
		m_ppos = m_position;//ボックス形状の調整
		//m_ppos.x += 50;
		m_ppos.y += 50;
		//m_ppos.z += 50;
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_ppos, CQuaternion::Identity);
		m_GhostObject.SetPosition(m_ppos);
	}
	else if (m_islong) {
		m_lastFramepos = m_position;
		if (m_position.z >= m_protpos.z) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = -4.0f;
		}
		else if (m_position.z <= m_protpos.z - 1200) {
			m_position.z = m_lastFramepos.z;
			m_moveSpeed.z = +4.0f;
		}
		m_position.z += m_moveSpeed.z;
		m_ppos = m_position;//ボックス形状の調整
							//m_ppos.x += 50;
		m_ppos.y += 50;
		//m_ppos.z += 50;
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_ppos, CQuaternion::Identity);
		m_GhostObject.SetPosition(m_ppos);
	}
}

