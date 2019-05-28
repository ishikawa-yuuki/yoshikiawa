#include "stdafx.h"
#include "SSPoint.h"
#include "GameData.h"

SSPoint::SSPoint()
{
}


SSPoint::~SSPoint()
{
	DeleteGO(m_skin);
	if (m_pointlight != nullptr) {
		DeleteGO(m_pointlight);
	}
}
bool SSPoint::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/LightObject/lanthanum.cmo");//仮ステージ
	GameData* gamedata = &GameData::GetInstance();
	if (gamedata->GetisStageClear(m_stagenumber)) {
		m_state = enState_Clear;
		m_pointlight = NewGO<prefab::CPointLight>(0);
		m_lightpos = m_position;
		//m_positionより少し上に
		m_lightpos.y += 100.0f;
		m_pointlight->SetAttn(m_Attn);
		m_pointlight->SetColor(m_color);
		m_pointlight->SetPosition(m_position);
	}
	else {
		if (gamedata->GetisStageClear(GameData::StageNumber(m_stagenumber - 1))) {
			m_state = enState_Release;
		}
		else {
			m_state = enState_noRelease;
		}
	}
	m_skin->SetShadowCasterFlag(true);
	return true;
}
void SSPoint::Update()
{
	m_skin->SetPosition(m_position);
	m_skin->SetRotation(m_rotation);
}