#include "stdafx.h"
#include "Stage_Select.h"
#include "SSPlayer.h"
#include "SSHuman.h"
#include "SSGameCamera.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"


Stage_Select::Stage_Select()
{
}


Stage_Select::~Stage_Select()
{
	//DeleteGO(m_spriteRender);
	DeleteGO(m_fade);
	DeleteGO(m_ssPlayer);
	DeleteGO(m_ssHuman);
	DeleteGO(m_ssGC);
	DeleteGO(m_skin);
}

bool Stage_Select::Start()
{
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/Stage_Select.dds", 1280.0f, 720.0f);
	//m_arrow = NewGO<prefab::CSpriteRender>(0);
	//m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	m_fade = NewGO<Fade>(0, "Fade");
	m_fade->StartFadeIn();
	m_ssPlayer = NewGO<SSPlayer>(0, "SSPlayer");
	m_ssHuman = NewGO<SSHuman>(0, "SSHuman");
	m_ssGC = NewGO<SSGameCamera>(0, "SSGameCamera");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
    m_skin->Init(L"modelData/StageSelect/SS.cmo");//仮ステージ
	m_skin->SetScale({ 2.0f,2.0f, 2.0f });//
	return true;
}

void Stage_Select::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
		    if(m_Tile == true) {
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
					 NewGO<Game>(0, "Game");
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
	else {
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