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
	DeleteGO(m_ptLight);
}

bool TitleGround::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/TitleGround/titleground.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale*2.5f);
	m_skinModelRender->SetShadowReceiverFlag(true);
	m_skinModelRender2 = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender2->Init(L"modelData/TitleGround/titleground_doukutsu.cmo");
	m_skinModelRender2->SetPosition(m_position*0.95);
	m_skinModelRender2->SetScale(m_scale);
	m_skinModelRender2->SetActiveFlag(false);
	m_title = FindGO<Title>("Title");
	m_ptLight = NewGO<prefab::CPointLight>(0);
	m_ptLight->SetColor({ 10.0f, 10.0f, 10.0f });//1000,1000,1000‚ÅLED‚Ý‚½‚¢‚ÈŒõ‚ªo‚é
	
	m_ptLight->SetAttn(m_pointLigDefaultAttn);
	return true;
}

void TitleGround::Update()
{
	if (!m_title->isStop()) {
		m_degree += m_adddegree * GameTime().GetFrameDeltaTime();
		m_rotation.SetRotationDeg(CVector3::AxisX, m_degree);
		m_skinModelRender->SetRotation(m_rotation);
		if (m_title->isTransStageSelect()) {
			//m_skinModelRender->SetShadowCasterFlag(true);
			m_skinModelRender2->SetActiveFlag(true);
			m_degree2 += m_adddegree * GameTime().GetFrameDeltaTime();
			m_rotation2.SetRotationDeg(CVector3::AxisX, m_degree2);
			CVector3 pointLigPos = m_lightposBase;
			m_rotation2.Apply(pointLigPos);
			m_ptLight->SetPosition(pointLigPos);
			m_skinModelRender2->SetRotation(m_rotation2);
			//m_skinModelRender2->SetEmissionColor({ 0.2f, 0.2f, 0.2f });
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
