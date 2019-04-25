#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Human.h"
#include "Player.h"
#include "Enemy.h"
#include "MistEnemy.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Title.h"
#include "Light_Object.h"
#include "Light_Object2.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Exit.h"
#include "Poison.h"
#include "Lever.h"
#include "Lightstand.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_human);
	DeleteGO(m_enemy);
	DeleteGO(m_mistenemy);
	DeleteGO(m_background);
	DeleteGO(m_exit);

	for (auto&moveBed : m_moveBedList) {
		DeleteGO(moveBed);
	}
	for (auto&moveBed_zengo : m_moveBed_zengoList) {
		DeleteGO(moveBed_zengo);
	}
	for (auto&moveBed_zengo_long : m_moveBed_zengo2List) {
		DeleteGO(moveBed_zengo_long);
	}
	for (auto&m_lightobject : m_lightobjectList) {
		DeleteGO(m_lightobject);
	}
	for (auto&m_lever : m_leverList) {
		DeleteGO(m_lever);
	}
	for (auto&m_poison :m_poisonList) {
		DeleteGO(m_poison);
	}
	/*for (auto&m_Lightstand : m_Lightstand1List) {
		DeleteGO(m_Lightstand);
	}*/
	//for (auto&m_lightobject2 : m_lightobjectList) {
	//	DeleteGO(m_lightobject2);
	//}
	DeleteGO(m_gamecamera);
}

bool Game::Start()
{
	shadow::DirectionShadowMap().Disable();
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.1f, 0.1f, 0.1f });
	//シーンの明るさを落とす。
	postEffect::Tonemap().SetLuminance(0.01f);
	m_player = NewGO<Player>(0, "Player");
	m_human = NewGO<Human>(0, "Human");
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	m_fade = FindGO<Fade>("Fade");
	m_mistenemy = NewGO<MistEnemy>(0, "mist");//後でlevelに組み込み
	
	m_level.Init(L"level/kari_yuuki.tkl", [&](LevelObjectData& objdata) {
		if (objdata.EqualObjectName(L"Stage1")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			return true;
		}
		//offランタン
		else if (objdata.ForwardMatchName(L"lanthanum1")) {	
			Light_Object* m_lightobject = NewGO<Light_Object>(0, "LightObject");
			m_lightobject->SetPosition(objdata.position);//試験したいなら{0,0,0}
			m_lightobjectList.push_back(m_lightobject);
		
			return true;
		}
		//onランタン
		else if (objdata.EqualObjectName(L"lanthanum2")) {
			Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
			m_onlightObject->SetPosition(objdata.position);
			m_onlightObject->SetLight();
			m_lightobjectList.push_back(m_onlightObject);
			return true;
		}
		//動く床は2種類ある、MoveBedは横移動するもの
		else if (objdata.EqualObjectName(L"MoveBed1")) {
			MoveBed* movebed = NewGO<MoveBed>(0,"MoveBed1");
			//m_movebed = NewGO<MoveBed>(0, "MoveBed");
			movebed->SetPosition(objdata.position);
			movebed->SetScale(objdata.scale);
			movebed->SetProtPos(objdata.position);
			m_moveBedList.push_back(movebed);
			return true;
		}
		//動く床は2種類ある、MoveBed2は前後移動するもの
		else if (objdata.EqualObjectName(L"MoveBed2")) {
			MoveBed_zengo* movebed2 = NewGO<MoveBed_zengo>(0, "MoveBed2");
			//m_movebed = NewGO<MoveBed>(0,"MoveBed2");
			movebed2->SetPosition(objdata.position);
			movebed2->SetScale(objdata.scale);
			movebed2->SetRot(objdata.rotation);
			movebed2->SetProtPos(objdata.position);
			m_moveBed_zengoList.push_back(movebed2);
			return true;
		}
		//MoveBed2_longは移動距離が長くなる。
		else if (objdata.EqualObjectName(L"MoveBed2_long")) {
			MoveBed_zengo* movebed2_long = NewGO<MoveBed_zengo>(0, "MoveBed2");
			//m_movebed = NewGO<MoveBed>(0,"MoveBed2");
			movebed2_long->SetPosition(objdata.position);
			movebed2_long->SetScale(objdata.scale);
			movebed2_long->SetRot(objdata.rotation);
			movebed2_long->SetProtPos(objdata.position);
			movebed2_long->isLongFrag();
			m_moveBed_zengo2List.push_back(movebed2_long);
			return true;
		}
		//オブジェクトねーーむ確認
		else if (objdata.EqualObjectName(L"Goal")) {
			m_exit = NewGO<Exit>(0, "Exit");
			m_exit->SetPosition(objdata.position);
			m_exit->SetQrot(objdata.rotation);
			m_exit->SetScale(objdata.scale);
			return true;
		}
		//黒エネミー、黒ユニティ
		else if (objdata.EqualObjectName(L"BlackUnityChan")) {
			m_enemy = NewGO<Enemy>(0, "Enemy");
			m_enemy->SetPosition(objdata.position);
			m_enemy->SetRotation(objdata.rotation);
			return true;
		}
		else if (objdata.ForwardMatchName(L"Lever")) {
			int num = _wtoi(&objdata.name[5]);
			Lever*m_lever = NewGO<Lever>(n,"Lever");
			m_lever->SetPosition(objdata.position);
			m_lever->SetRotation(objdata.rotation);
			m_lever->SetScale(objdata.scale);
			//m_lever->SetLeverNumber(num);
			m_leverList.push_back(m_lever);
			
			return true;
		}
		else if (objdata.ForwardMatchName(L"huzitubo")) {
				int num = _wtoi(&objdata.name[8]);
				Poison*m_poison = NewGO<Poison>(0, "Poison");
				m_poison->SetPosition(objdata.position);
				m_poison->SetPoisonNumber(num);
				m_poisonList.push_back(m_poison);
			
			
			return true;
		}
		else if (objdata.ForwardMatchName(L"Lightstand")) {
			int num = _wtoi(&objdata.name[10]);
			Lightstand* m_Lightstand = NewGO<Lightstand>(0, "Lightstand");
			m_Lightstand->SetNum(num);
			m_Lightstand->SetPosition(objdata.position);
			m_Lightstand->SetRotation(objdata.rotation);
			m_Lightstand->SetScale(objdata.scale);
			
			m_Lightstand1List.push_back(m_Lightstand);
			return true;
		}
		return false;
	});
	m_fade->StartFadeIn();

	//全方位シャドウを有効にする
	shadow::OminiDirectionShadowMap().Enable();

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
	if (m_Gamesyuuryou) {
		m_Gamesyuuryou = false;
		DeleteGO(this);
	}

	m_human = FindGO<Human>("Human");
	auto nearPointLig = m_human->GetNearPointLight();
	if (nearPointLig == nullptr) {
		//ヒューマンが向かっていっているライトがないときは
		nearPointLig = m_player->GetPointLight();
	}
	if (nearPointLig != nullptr) {
		shadow::OminiDirectionShadowMap().SetLightPosition(nearPointLig->GetPosition());
		shadow::OminiDirectionShadowMap().SetDistanceAffectedByLight(nearPointLig->GetAttn().x);
		shadow::OminiDirectionShadowMap().SetShadowBias(0.002f);
		shadow::OminiDirectionShadowMap().SetNearClip(10.0f);
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