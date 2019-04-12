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
	m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
	return true;
}
void Lever::Update()
{
	CVector3 diff = m_position - m_player->GetPosition();
	diff.y = 0;
	switch (m_levernum) {
	case Lever0:
		if (diff.LengthSq() <= 100.0f*100.0f&& m_timer >= 2.0f) {
			if (m_State[0]) {
				m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
				m_State[0] = false;
			}
			else {
				m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
				m_State[0] = true;
			}
			m_timer = 0;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		break;
	case Lever1:
		if (diff.LengthSq() <= 100.0f*100.0f&& m_timer >= 2.0f) {
			if (m_State[1]) {
				m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
				m_State[1] = false;
			}
			else {
				m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
				m_State[1] = true ;
			}
			m_timer = 0;
		}
		m_timer += GameTime().GetFrameDeltaTime();
		break;
	};
	
}
void Lever::SetLeverNumber(const int num)
{
	switch (num) {
	case 0:
		m_levernum = Lever0;
		break;
	case 1:
		m_levernum = Lever1;
		break;
	}
}