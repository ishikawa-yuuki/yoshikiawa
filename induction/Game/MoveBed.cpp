#include "stdafx.h"
#include "MoveBed.h"
#include "Player.h"

MoveBed::MoveBed()
{
}


MoveBed::~MoveBed()
{
	DeleteGO(m_skin);
}

bool MoveBed::Start()
{
	m_player = FindGO<Player>("Player");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/MoveBed/MoveBed1.cmo");

	//m_skin->SetScale({ 20.0f,20.0f,20.0f });//Žv‚Á‚½‚æ‚è¬‚³‚©‚Á‚½‚Ì‚Å20”{
	m_skin->SetScale(m_scale);//GameƒNƒ‰ƒX‚©‚ç‘å‚«‚³‚ð“n‚³‚ê‚Ä‚¢‚Ü‚·
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
void MoveBed::Range()
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
void MoveBed::Update()
{
		m_lastFramepos = m_position;
		if (m_timer >= 2.0f) {
			prefab::CSoundSource* m_sound = NewGO<prefab::CSoundSource>(0);
			m_sound->Init(L"sound/movebed.wav");
			m_sound->SetPosition(m_position);
			Range();
			m_sound->SetVolume(m_volume);
			m_sound->Play(false);
			m_position.x += m_moveSpeed.x*GameTime().GetFrameDeltaTime();
		}
		if (m_position.x < m_protpos.x ) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = MOVE_SPEED;
			m_timer = 0.0f;
		}
		else if (m_position.x > m_protpos.x + 870) {
			m_position.x = m_lastFramepos.x;
			m_moveSpeed.x = -MOVE_SPEED;
			m_timer = 0.0f;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_skin->SetPosition(m_position);
		m_StaticObject.SetPositionAndRotation(m_position, CQuaternion::Identity);
		m_GhostObject.SetPosition(m_position);

}
