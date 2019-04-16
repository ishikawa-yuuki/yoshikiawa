#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPlayer.h"
#include "SSHuman.h"
#include "SSPoint.h"
#include "SSGameCamera.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "Stage_Number.h"


Stage_Select::Stage_Select()
{
}


Stage_Select::~Stage_Select()
{
	DeleteGO(m_ssPlayer);
	DeleteGO(m_ssHuman);
	DeleteGO(m_ssGC);
	DeleteGO(m_skin);
	for (int i = 0; i < point; i++) {
		DeleteGO(m_ssPoint[i]);
	}
}

bool Stage_Select::Start()
{
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.1f, 0.1f, 0.1f });
	//シーンの明るさを落とす。
	postEffect::Tonemap().SetLuminance(0.1f);
	for (int i = 0; i < point; i++) {
		m_ssPoint[i] = NewGO<SSPoint>(0, "SSPoint");
		m_ssPoint[i]->m_position.x += i * 1200;
	}
	m_ssPlayer = NewGO<SSPlayer>(0, "SSPlayer");
	m_ssHuman = NewGO<SSHuman>(0, "SSHuman");
	m_ssGC = NewGO<SSGameCamera>(0, "SSGameCamera");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
    m_skin->Init(L"modelData/StageSelect/SS.cmo");//仮ステージ
	m_skin->SetScale({ 2.0f,2.0f, 2.0f });//
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}

void Stage_Select::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
		    if(m_Tile) {
			  NewGO<Title>(0, "Title");
			  DeleteGO(this);
		     }
		     else {
				 switch (m_ssPlayer->GetStagenum()) {
				 case 1:
					 NewGO<Game>(0, "Game");
					 DeleteGO(this);
					 break;
				 case 2:
					 NewGO<Title>(0, "Title");
					 Stage_Number* stagenum;
					 stagenum = FindGO<Stage_Number>("Stage_Number");
					 stagenum->IsTitle();
					 DeleteGO(this);
					 break;
				 case 3:
					 NewGO<Game>(0, "Game");
					 DeleteGO(this);
					 break;
				 }
			 }
		 }
	}
	else if (m_ssPlayer->GetOK()) {
		if (Pad(0).IsTrigger(enButtonA)) {
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