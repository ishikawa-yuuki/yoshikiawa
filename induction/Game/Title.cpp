#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "Stage_Select.h"
#include "Help.h"
#include "Credit.h"
#include "TitleGround.h"
#include "Human.h"
#include "Player.h"
#include "GameCamera.h"
Title::Title()
{
}


Title::~Title()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_arrow);
	DeleteGO(m_bgm);
	DeleteGO(m_player);
	DeleteGO(m_human);
	DeleteGO(m_titleground);
	DeleteGO(m_gamecamera);
	DeleteGO(m_ptLight);
}

bool Title::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/title/title2.dds",1280.0f,720.0f);
	m_menu1 = NewGO<prefab::CSpriteRender>(0);
	m_menu1->Init(L"sprite/title/start.dds", 1280.0f, 720.0f);
	m_menu2 = NewGO<prefab::CSpriteRender>(0);
	m_menu2->Init(L"sprite/title/manual.dds", 1280.0f, 720.0f);
	m_menu3 = NewGO<prefab::CSpriteRender>(0);
	m_menu3->Init(L"sprite/title/credit.dds", 1280.0f, 720.0f);
	m_arrow = NewGO<prefab::CSpriteRender>(0);
	m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/kari.wav");
	m_bgm->Play(true);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_level.Init(L"level/title/title.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"titleground")) {
			return true;
		}
		//offランタン
		else if (objdata.EqualObjectName(L"Human")) {
			m_human = NewGO<Human>(0, "Human");
			m_human->SetPosition(objdata.position);
			m_human->SetRotation(objdata.rotation);
			return true;
		}
		
		return false;
		});
	m_titleground = NewGO<TitleGround>(0);
	//m_human = NewGO<Human>(0, "Human");
	//m_human->SetPosition(CVector3(200.0f,0.0f,200.0f));
	m_player = NewGO<Player>(0, "Player");
	m_player->SetPosition(CVector3::Zero);
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	shadow::DirectionShadowMap().Disable();
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.05f, 0.05f, 0.05f });
	//全方位シャドウを有効にする
	shadow::OminiDirectionShadowMap().Enable();
	//シーンの明るさを落とす。
	postEffect::Tonemap().SetLuminance(0.1f);
	m_ptLight = NewGO<prefab::CPointLight>(0);
	CVector3 pointlightpos = m_human->GetPosition();
	pointlightpos.y += 100.0f;
	m_ptLight->SetPosition(pointlightpos);//位置決め
	CVector3 color = { 30.0f,30.0f,30.0f };
	m_ptLight->SetColor(color);//色決め
	attn.x = 700.0f;
	attn.y = 5.0f;
	m_ptLight->SetAttn(attn);
	return true;
}

void Title::Update()
{
	
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			if (m_select == select1) {
				NewGO<Stage_Select>(0, "Stage_Select");
				DeleteGO(this);
			}
			else if (m_select == select2) {
				NewGO<Help>(0, "Help");
				DeleteGO(this);
			}
			else if (m_select == select3) {
				NewGO<Credit>(0, "Credit");
				DeleteGO(this);
			}
		}
	}
		Choice();
	
}
void Title::Choice()
{
	prefab::CSoundSource* ss;
	const float arrow_move = -100.0f;//弓の移動距離
	if (Pad(0).IsTrigger(enButtonDown)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		switch (m_select) {
		case select1:
			m_select = select2;
			m_arrowPos.y += arrow_move;
			break;
		case select2:
			m_select = select3;
			m_arrowPos.y += arrow_move;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonUp)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		switch (m_select) {
		case select2:
			m_select = select1;
			m_arrowPos.y -= arrow_move;
			break;
		case select3:
			m_select = select2;
			m_arrowPos.y -= arrow_move;
			break;
		}
	}
	else if (Pad(0).IsTrigger(enButtonA)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/decision1.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		if (m_select == select1) {
			m_istransstageselect = true;
		}
		/*m_isWaitFadeout = true;
		m_fade->StartFadeOut();*/
	}

	m_arrow->SetPosition(m_arrowPos);
}