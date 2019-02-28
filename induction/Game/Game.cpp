#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Human.h"
#include "Player.h"
#include "MoveBed.h"
#include "Title.h"
#include "Light_Object.h"
#include "GameCamera.h"
#include "BackGround.h"
Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_human);
	DeleteGO(m_background);
	for (auto&moveBed : m_moveBedList) {
		DeleteGO(moveBed);
	}
	for (auto&moveBed2 : m_moveBedList2) {
		DeleteGO(moveBed2);
	}
	DeleteGO(m_gamecamera);
	DeleteGO(m_lightobject);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_human = NewGO<Human>(0, "Human");
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	m_fade = FindGO<Fade>("Fade");


	m_level.Init(L"level/level_Stage01.tkl", [&](LevelObjectData& objdata) {
		if (objdata.EqualObjectName(L"Stage1")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			return true;
		}
		if (objdata.EqualObjectName(L"lanthanum")) {
			m_lightobject = NewGO<Light_Object>(0, "LightObject");
			m_lightobject->SetPosition(objdata.position);
			return true;
		}
		//動く床は2種類ある、MoveBed1は横移動するもの
		if (objdata.EqualObjectName(L"MoveBed1")) {
			MoveBed* movebed = NewGO<MoveBed>(0,"MoveBed1");
			//m_movebed = NewGO<MoveBed>(0, "MoveBed");
			movebed->SetPosition(objdata.position);
			m_moveBedList.push_back(movebed);
			return true;
		}
		//動く床は2種類ある、MoveBed2は前後移動するもの
		if (objdata.EqualObjectName(L"MoveBed2")) {
			MoveBed* movebed2 = NewGO<MoveBed>(0, "MoveBed2");
			//m_movebed = NewGO<MoveBed>(0, "MoveBed2");
			movebed2->SetPosition(objdata.position);
			m_moveBedList2.push_back(movebed2);
			return true;
		}
	});
	m_fade->StartFadeIn();
	return true;
}

void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0);
			DeleteGO(this);
		}
	}
	else {
			Pose();
	}
	if (m_Gamesyuuryou != false) {
		m_Gamesyuuryou = false;
		DeleteGO(this);
	}
}

void Game::Pose()
{
	const float tate = 150.0f;
	const float yoko = 280.0f;
	if (!m_isPose) { //!=trueとか==trueとかをなくしました。
		if (!m_damege) {
			if (Pad(0).IsTrigger(enButtonStart)) {
				m_isPose = true;

				m_sprite_Retire = NewGO<prefab::CSpriteRender>(0);
				m_sprite_toGame = NewGO<prefab::CSpriteRender>(0);
				m_sprite_arrow = NewGO<prefab::CSpriteRender>(0);

				m_sprite_Retire->Init(L"sprite/retire.dds", yoko, tate);
				m_sprite_toGame->Init(L"sprite/BacktoGame.dds", yoko, tate);
				m_sprite_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);

				m_sprite_Retire->SetPosition(m_Retirepos);
				m_sprite_toGame->SetPosition(m_toGamepos);
				m_sprite_arrow->SetPosition(m_arrowpos);
			}
			return;
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonRight)) {
			switch (m_state) {
			case retire:
				m_state = togame;
				m_arrowpos.x = 0.0f;
				break;
			}
		}
		else if (Pad(0).IsTrigger(enButtonLeft)) {
			switch (m_state)
			{
			case Game::togame:
				m_state = retire;
				m_arrowpos.x = -400.0f;
				break;
			}
		}
		if (Pad(0).IsTrigger(enButtonA)) {
			switch (m_state)
			{
			case Game::retire:
				DeleteGO(m_sprite_Retire);
				DeleteGO(m_sprite_toGame);
				DeleteGO(m_sprite_arrow);
				m_isPose = false;
				m_fade->StartFadeOut();
				m_isWaitFadeout = true;
				break;
			case Game::togame:
				DeleteGO(m_sprite_Retire);
				DeleteGO(m_sprite_toGame);
				DeleteGO(m_sprite_arrow);
				m_isPose = false;
				break;
			}
		}
		m_sprite_arrow->SetPosition(m_arrowpos);
	}
}