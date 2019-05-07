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
	//モデル表示できないtksファイルもおかしい
	m_animClip[enAnimationClip_OPEN].Load(L"animData/Door/open.tka");
	m_animClip[enAnimationClip_OPEN].SetLoopFlag(false);
	m_game = FindGO<Game>("Game");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Door/Door.cmo", m_animClip, enAnimationClip_num);
	m_skin->SetPosition(m_position);
	m_skin->SetScale(m_scale);
	m_StaticObject.CreateBox(
		m_position,
		CQuaternion::Identity,
		{ 800.0f, 1000.0f, 100.0f }
	); 
	return true;
}
void Door::Update()
{
	const auto& leverList = m_game->GetLeverList();
	if (leverList[0]->IsStateLever()&& leverList[1]->IsStateLever()) {
		m_skin->PlayAnimation(enAnimationClip_OPEN, 0.2);
		m_StaticObject.Release();
	}
}
