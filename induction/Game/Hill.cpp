#include "stdafx.h"
#include "Hill.h"
#include "Human.h"

Hill::Hill()
{
}


Hill::~Hill()
{
	DeleteGO(m_skinModelRender);
}

bool Hill::Start()
{
	m_human = FindGO<Human>("Human");

	m_animeClip[enAnimationClip_move].Load(L"animData/Hill/move.tka");

	//for•¶‚Å‚Æ‚è‚ ‚¦‚¸ƒ[ƒh‚µ‚½“z‚ç‚·‚×‚ÄLoopFlag‚ğtrue‚É‚µ‚½B
	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animeClip[i].SetLoopFlag(true);
	}
	

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Hill/Hill.cmo",m_animeClip,enAnimationClip_num,enFbxUpAxisZ);
	m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.2);
	return true;
}

void Hill::Update()
{
	CVector3 diff_h = m_human->GetPosition() - m_position;
	diff_h.y = 0.0f;
	if (m_timer < 60) {
		m_timer += 60 * GameTime().GetFrameDeltaTime();
		diff_h.Normalize();
		m_position += diff_h * 50.0f * GameTime().GetFrameDeltaTime();
	}
	else {
		m_timer += 60 * GameTime().GetFrameDeltaTime();
		m_position = m_position;
		if (m_timer > 100) {
			m_timer = 0;
		}
	}
	m_skinModelRender->SetPosition(m_position);
}