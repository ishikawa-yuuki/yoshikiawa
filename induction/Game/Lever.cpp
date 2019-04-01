#include "stdafx.h"
#include "Lever.h"
#include "Player.h"


Lever::Lever()
{
}


Lever::~Lever()
{
	DeleteGO(m_skin);
}
bool Lever::Start()
{
	m_player = FindGO<Player>("Player");
	m_animClip[enAnimationClip_ON].Load(L"animData/Lever/Lever_ON.tka");
	m_animClip[enAnimationClip_OFF].Load(L"animData/Lever/Lever_OFF.tka");
	m_animClip[enAnimationClip_ON].SetLoopFlag(false);
	m_animClip[enAnimationClip_OFF].SetLoopFlag(false);
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Lever/Lever.cmo", m_animClip, enAnimationClip_num);
	//m_position.y = -50;
	m_position.z = -800;
	//m_position.x = 200;
	m_skin->SetPosition(m_position);
	m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
	return true;
}
void Lever::Update()
{
	CVector3 diff = m_position - m_player->GetPosition();
	diff.y = 0;
	if (diff.LengthSq() <= 100.0f*100.0f&& m_timer >= 2.0f) {
		if (m_State) {
			m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
			m_State = false;
		}
		else {
			m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
			m_State = true;
		}
		m_timer = 0;
	 }
	m_timer += GameTime().GetFrameDeltaTime();
}