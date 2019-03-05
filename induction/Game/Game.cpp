#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Human.h"
#include "Player.h"
#include "Enemy.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Title.h"
#include "Light_Object.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Exit.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_human);
	DeleteGO(m_enemy);
	DeleteGO(m_background);
	DeleteGO(m_exit);
	for (auto&moveBed : m_moveBedList) {
		DeleteGO(moveBed);
	}
	for (auto&moveBed_zengo : m_moveBed_zengoList) {
		DeleteGO(moveBed_zengo);
	}
	DeleteGO(m_gamecamera);
	DeleteGO(m_lightobject);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "Player");
	m_human = NewGO<Human>(0, "Human");
	m_enemy = NewGO<Enemy>(0, "Enemy");
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	m_fade = FindGO<Fade>("Fade");


	m_level.Init(L"level/level_Stage1_sisaku.tkl", [&](LevelObjectData& objdata) {
		if (objdata.EqualObjectName(L"Stage1")) {
			m_background = NewGO<BackGround
			>(0, "BackGround");
			return true;
		}
		if (objdata.EqualObjectName(L"lanthanum")) {
			m_lightobject = NewGO<Light_Object>(0, "LightObject");
			m_lightobject->SetPosition(objdata.position);
			return true;
		}
		//��������2��ނ���AMoveBed�͉��ړ��������
		if (objdata.EqualObjectName(L"MoveBed1")) {
			MoveBed* movebed = NewGO<MoveBed>(0,"MoveBed1");
			//m_movebed = NewGO<MoveBed>(0, "MoveBed");
			movebed->SetPosition(objdata.position);
			movebed->SetScale(objdata.scale);
			m_moveBedList.push_back(movebed);
			return true;
		}
		//��������2��ނ���AMoveBed2�͑O��ړ��������
		if (objdata.EqualObjectName(L"MoveBed2")) {
			MoveBed_zengo* movebed2 = NewGO<MoveBed_zengo>(0, "MoveBed2");
			//m_movebed = NewGO<MoveBed>(0,"MoveBed2");
			movebed2->SetPosition(objdata.position);
			movebed2->SetScale(objdata.scale);
			movebed2->SetProtPos(objdata.position);
			m_moveBed_zengoList.push_back(movebed2);
			return true;
		}
		//�I�u�W�F�N�g�ˁ[�[�ފm�F
		if (objdata.EqualObjectName(L"Goal")) {
			m_exit = NewGO<Exit>(0, "Exit");
			m_exit->SetPosition(objdata.position);
			m_exit->SetQrot(objdata.rotation);
			m_exit->SetScale(objdata.scale);
			return true;
		}
		return false;
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
	if (!m_isPose) { //!=true�Ƃ�==true�Ƃ����Ȃ����܂����B
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