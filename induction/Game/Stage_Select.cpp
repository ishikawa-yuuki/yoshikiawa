#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPlayer.h"
#include "SSHuman.h"
#include "SSPoint.h"
#include "SSGameCamera.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "GameCamera.h"
#include "GameData.h"
#include "Help.h"
Stage_Select::Stage_Select()
{
}


Stage_Select::~Stage_Select()
{
	DeleteGO(m_ssPlayer);
	DeleteGO(m_ssHuman);
	//DeleteGO(m_ssGC);
	DeleteGO(m_skin);
	DeleteGO(m_sky);
	for (int i = 0; i < m_sspointList.size(); i++) {
		DeleteGO(m_sspointList[i - 1]);
	}
	DeleteGO(m_gamecamera);
}

bool Stage_Select::Start()
{
	m_gamedata = &GameData::GetInstance();
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.1f, 0.1f, 0.1f });
	postEffect::Tonemap().SetLuminance(0.05f);
	//シーンの明るさを落とす。
	m_level.Init(L"level/stageselect/stageselect.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"stageselect_ground")) {
			m_skin = NewGO<prefab::CSkinModelRender>(0);
			m_skin->Init(L"modelData/StageSelect/stageselect_ground.cmo");
			m_skin->SetPosition(objdata.position);//
			m_physicsStaticObject.CreateMesh(CVector3::Zero, CQuaternion::Identity, CVector3::One, m_skin);
			m_skin->SetShadowReceiverFlag(true);
			return true;
		}
		//Humanの座標を取得
		else if (objdata.ForwardMatchName(L"Human")) {
			int num = _wtoi(&objdata.name[5]);
			if (num == 1) {
				m_humanrot = objdata.rotation;
			}
			m_humanpositionList[num] = objdata.position;
			return true;
		}
		//Playerを生成
		else if (objdata.ForwardMatchName(L"player")) {
			int num = _wtoi(&objdata.name[6]);

			m_playerpositionList[num] = objdata.position;
			return true;
		}
		else if (objdata.ForwardMatchName(L"light")) {
			int num = _wtoi(&objdata.name[5]);
			SSPoint* point = NewGO<SSPoint>(0, "Light");
			point->SetPosition(objdata.position);
			point->SetRotation(objdata.rotation);
			point->SetNumber(GameData::StageNumber(num));
			m_sspointList[num] = point;
			return true;
		}
		return false;
		});
	m_pos = m_playerpositionList[1];
	//m_ssGC = NewGO<SSGameCamera>(0, "SSGameCamera");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_sky = NewGO<prefab::CSky>(0, "Sky");
	//m_sky->SetSkyCubeMapFilePath(L"sprite/naibu.dds");
	m_sky->SetScale({ 24000.0f,5000.0f,5000.0f });
	m_sky->SetEmissionColor({ 0.01f, 0.01f, 0.01f });
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	for (int i = 0; i < m_sspointList.size(); i++) {
		m_sspointList[i + 1]->SetPlayerPosition(m_playerpositionList[i + 1]);
		m_sspointList[i + 1]->SetHumanPosition(m_humanpositionList[i + 1]);
	}
	m_ssPlayer = NewGO<SSPlayer>(0, "SSPlayer");
	m_ssPlayer->SetStageNumber(m_gamedata->GetStageNumber());
	m_ssHuman = NewGO<SSHuman>(0, "SSHuman");
	m_ssHuman->SetRotation(m_humanrot);
	m_ssHuman->SetStageNumber(m_gamedata->GetStageNumber());
	m_ssPlayer->SetPosition(m_playerpositionList[m_gamedata->GetStageNumber()]);
	m_ssHuman->SetPosition(m_humanpositionList[m_gamedata->GetStageNumber()]);
	//全方位シャドウ関係
	shadow::DirectionShadowMap().Disable();
	shadow::OminiDirectionShadowMap().Enable();
	//全方位シャドウの影響範囲を設定する。
	shadow::OminiDirectionShadowMap().SetDistanceAffectedByLight(1000);
	shadow::OminiDirectionShadowMap().SetLightPosition(m_ssPlayer->GetPosition());
	return true;
}

void Stage_Select::Update()
{
	shadow::OminiDirectionShadowMap().SetLightPosition(m_ssPlayer->GetPosition());
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
		    if(m_Tile) {
			  NewGO<Title>(0, "Title");
			  DeleteGO(this);
		     }
		     else {
				if (!m_gamedata->GetisFirstEnterStage()) {
					m_gamedata->SetisEnterStage();
					NewGO<Help>(0, "Help")->SetisTransStage();
					DeleteGO(this);
				}
				else {
					NewGO<Game>(0, "Game");
					DeleteGO(this);
				}
			 }
		 }
	}
	else {
		if (m_ssPlayer->GetisStage()) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		else if (Pad(0).IsTrigger(enButtonB)) {
			m_isWaitFadeout = true;
			m_Tile = true;
			m_fade->StartFadeOut();
		}
	}
}

