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
	if (m_num == 9|| m_num == 8) {
		m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
		m_State = false;
	}
	else {
		m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
	}
	
	return true;
}
void Lever::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 0.5f;
	}
	else if (diff.LengthSq() < range * 1.5) {
		m_volume = 0.25f;
	}
	else {
		m_volume = 0.0f;
	}
}
void Lever::Update()
{
	prefab::CSoundSource* sound = nullptr;
	//制限時間（短め）
	if (m_num == 0) {
		m_time = 12.0f;
	}
	//制限時間（長め）
	else {
		m_time = 20.0f;
	}
	CVector3 diff = m_position - m_player->GetPosition();
	diff.y = 0;
	//制限時間なしver
	if (m_num == 9 || m_num == 8) {
		CVector3 diff = m_position - m_player->GetPosition();
		diff.y = 0;
		if (diff.LengthSq() <= 100.0f * 100.0f && m_player->GetColor() == 0) {
			//一回きりのレバー
			if (!m_State) {
				sound = NewGO<prefab::CSoundSource>(0);
				sound->Init(L"sound/Lever_kari.wav");
				sound->Play(false);
				Range();
				sound->SetVolume(m_volume);
			}
			m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
			m_State = true;
			
		}
	}
	else if (diff.LengthSq() <= 100.0f*100.0f&& m_timer >= 2.0f&&m_player->GetColor() ==0|| m_timer >= m_time&& !m_State) {
			if (m_State) {
				m_skin->PlayAnimation(enAnimationClip_OFF, 0.2);
				m_State = false;
				sound = NewGO<prefab::CSoundSource>(0);
				sound->Init(L"sound/Lever_kari.wav");
				sound->Play(false);
				Range();
				sound->SetVolume(m_volume);
			}
			else {
				m_skin->PlayAnimation(enAnimationClip_ON, 0.2);
				m_State = true;
				sound = NewGO<prefab::CSoundSource>(0);
				sound->Init(L"sound/Lever_kari.wav");
				sound->Play(false);
				Range();
				sound->SetVolume(m_volume);
			}
			m_timer = 0.0f;
		}
		m_timer += GameTime().GetFrameDeltaTime();
	
}