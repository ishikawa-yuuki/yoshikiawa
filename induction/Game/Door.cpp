#include "stdafx.h"
#include "Door.h"
#include "Game.h"
#include "Lever.h"
Door::Door()
{
}


Door::~Door()
{
	DeleteGO(m_skin);
}
bool Door::Start()
{
	m_animClip[enAnimationClip_OPEN].Load(L"animData/Door/open.tka");
	m_animClip[enAnimationClip_OPEN].SetLoopFlag(false);
	m_animClip[enAnimationClip_STOP].Load(L"animData/Door/stop.tka");
	m_animClip[enAnimationClip_STOP].SetLoopFlag(false);
	m_game = FindGO<Game>("Game");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Door/Door.cmo", m_animClip, enAnimationClip_num);
	m_skin->SetPosition(m_position);
	m_skin->SetScale(m_scale); 
	m_StaticObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{ 800.0f, 1000.0f, 80.0f }
	); 
	return true;
}
void Door::Update()
{
	prefab::CSoundSource* sound = nullptr;
	const auto& leverList = m_game->GetLeverList();
	if (leverList[0]->IsStateLever()&& leverList[1]->IsStateLever()) {
		//”à‚ÌŠJ‚­‰¹
		if (m_timer == 0) {
			sound = NewGO<prefab::CSoundSource>(0);
			sound->Init(L"sound/DoorStart.wav");
			sound->Play(false);
		}
		else if(m_timer == 0.2f) {
			sound = NewGO<prefab::CSoundSource>(0);
			sound->Init(L"sound/DoorOpen.wav");
			sound->Play(false);
		}
		m_timer += GameTime().GetFrameDeltaTime();
		m_skin->PlayAnimation(enAnimationClip_OPEN, 0.2);
		m_StaticObject.Release();
	}
}
