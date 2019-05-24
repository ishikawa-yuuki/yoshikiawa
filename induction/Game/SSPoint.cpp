#include "stdafx.h"
#include "SSPoint.h"
#include "GameData.h"

SSPoint::SSPoint()
{
}


SSPoint::~SSPoint()
{
	DeleteGO(m_skin);
}
bool SSPoint::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/LightObject/lanthanum.cmo");//仮ステージ
	GameData* gamedata = &GameData::GetInstance();
	if (gamedata->GetisStageClear(m_stagenumber)) {
		m_state = enState_Clear;
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