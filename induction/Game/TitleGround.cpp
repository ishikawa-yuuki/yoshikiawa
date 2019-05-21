#include "stdafx.h"
#include "TitleGround.h"
#include "Title.h"

TitleGround::TitleGround()
{
}


TitleGround::~TitleGround()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_skinModelRender2);
}

bool TitleGround::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/TitleGround/titleground.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale*2.5f);
	m_skinModelRender2 = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender2->Init(L"modelData/TitleGround/titleground_doukutsu.cmo");
	m_skinModelRender2->SetPosition(m_position*0.95);
	m_skinModelRender2->SetScale(m_scale);
	m_skinModelRender2->SetActiveFlag(false);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_title = FindGO<Title>("Title");
	return true;
}

void TitleGround::Update()
{
	if (!m_title->isStop()) {
		m_degree += m_adddegree * GameTime().GetFrameDeltaTime();
		m_rotation.SetRotationDeg(CVector3::AxisX, m_degree);
		m_skinModelRender->SetRotation(m_rotation);
		if (m_title->isTransStageSelect()) {
			m_skinModelRender2->SetActiveFlag(true);
			m_degree2 += m_adddegree * GameTime().GetFrameDeltaTime();
			m_rotation2.SetRotationDeg(CVector3::AxisX, m_degree2);
			m_skinModelRender2->SetRotation(m_rotation2);
		}
	}
	else {
	/*	m_degree += m_cutdegree * GameTime().GetFrameDeltaTime();
		m_rotation.SetRotationDeg(CVector3::AxisX, m_degree);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender2->SetActiveFlag(true);
		m_degree2 += m_cutdegree * GameTime().GetFrameDeltaTime();
		m_rotation2.SetRotationDeg(CVector3::AxisX, m_degree2);
		m_skinModelRender2->SetRotation(m_rotation2);*/
	}
}
