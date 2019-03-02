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
	//m_skin->SetScale({ 20.0f,20.0f,20.0f });//�v������菬���������̂�20�{
	m_skin->SetScale(m_scale);//Game�N���X����傫����n����Ă��܂�
	m_StaticObject.CreateBox(
		m_ppos,
		CQuaternion::Identity,
		{600.0f, 100.0f, 450.0f}
	);
	m_GhostObject.CreateBox(
		m_ppos,
		CQuaternion::Identity,
		{ 605.0f, 15.0f, 455.0f }
	);
	return true;
}
void MoveBed::Update()
{
	m_lastFramepos = m_position;
	if (m_position.x <= m_protpos.x - 200) {
		m_position.x = m_lastFramepos.x;
		m_moveSpeed.x = 2.0f;
	}
	else if(m_position.x >= m_protpos.x + 200 ){
		m_position.x = m_lastFramepos.x;
		m_moveSpeed.x = -2.0f;
	}
	m_position.x += m_moveSpeed.x;
	m_ppos = m_position;//�{�b�N�X�`��̒���
	m_ppos.z += 100;
	m_ppos.y += 70;
	m_ppos.x -= 50;
	m_skin->SetPosition(m_position);
	m_StaticObject.SetPositionAndRotation(m_ppos, CQuaternion::Identity);
	m_GhostObject.SetPosition(m_ppos);
}
