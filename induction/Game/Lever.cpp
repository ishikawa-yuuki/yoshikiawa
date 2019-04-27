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
	m_skin->SetPosition(m_position);
	m_skin->SetRotation(m_rot);
	m_skin->SetScale(m_scale);
	m_skin->SetEmissionColor({0.7f,0.7f,0.7f});
	m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
	return true;
}
void Lever::Update()
{
	if (m_num == 0) {
		m_time = 12.0f;
	}
	else {
		m_time = 20.0f;
	}
	CVector3 diff = m_position - m_player->GetPosition();
	diff.y = 0;
		if (diff.LengthSq() <= 100.0f*100.0f&& m_timer >= 2.0f&&m_player->GetColor() ==0|| m_timer >= m_time&& !m_State) {
			if (m_State) {
				m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
				m_State = false;
			}
			else {
				m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
				m_State = true;
			}
			m_timer = 0.0f;
		}
		m_timer += GameTime().GetFrameDeltaTime();
	
}