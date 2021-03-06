#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Fade.h"
#include "Human.h"
#include "Player.h"
//#include "Enemy.h"
#include "MistEnemy.h"
#include "Hill.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Title.h"
#include "Light_Object.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Exit.h"
#include "Poison.h"
#include "Lever.h"
#include "Lightstand.h"
#include "Door.h"
#include "Stone.h"
#include "GameData.h"
#include "Stage_Select.h"
#include "CheckPoint.h"
Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_human);
	/*DeleteGO(m_enemy);*/
	DeleteGO(m_mistenemy);
	DeleteGO(m_background);
	DeleteGO(m_exit);
	DeleteGO(m_sky);
	DeleteGO(m_gamecamera);
	switch (m_gamedata->GetStageNumber()) {
	case GameData::enState_Stage1:
		for (auto& moveBed : m_moveBedList) {
			DeleteGO(moveBed);
		}
		for (auto& moveBed_zengo : m_moveBed_zengoList) {
			DeleteGO(moveBed_zengo);
		}
		for (auto& moveBed_zengo_long : m_moveBed_zengo2List) {
			DeleteGO(moveBed_zengo_long);
		}
		for (auto& m_lightobject : m_lightobjectList) {
			DeleteGO(m_lightobject);
		}
		for (auto& m_lever : m_leverList) {
			DeleteGO(m_lever);
		}
		for (auto& m_poison : m_poisonList) {
			DeleteGO(m_poison);
		}
		for (auto& m_Lightstand : m_Lightstand1List) {
			DeleteGO(m_Lightstand);
		}
		break;
	case GameData::enState_Stage2:
		for (auto& m_poison : m_poisonList) {
			DeleteGO(m_poison);
		}
		for (auto& m_lever : m_leverList) {
			DeleteGO(m_lever);
		}
		for (auto& m_lightobject : m_lightobjectList) {
			DeleteGO(m_lightobject);
		}
		for (auto& m_Lightstand : m_Lightstand1List) {
			DeleteGO(m_Lightstand);
		}
		for (auto& m_stone : m_StoneList) {
			DeleteGO(m_stone);
		}
		for (auto& door : m_DoorList) {
			DeleteGO(door);
		}
		break;
	case GameData::enState_Stage3:
		for (auto& m_poison : m_poisonList) {
			DeleteGO(m_poison);
		}
		for (auto& m_lever : m_leverList) {
			DeleteGO(m_lever);
		}
		for (auto& m_Lightstand : m_Lightstand1List) {
			DeleteGO(m_Lightstand);
		}
		for (auto& m_lightobject : m_lightobjectList) {
			DeleteGO(m_lightobject);
		}
		for (auto& m_stone : m_StoneList) {
			DeleteGO(m_stone);
		}
		for (auto& m_hill : m_hillList) {
			DeleteGO(m_hill);
		}
		break;
	case GameData::enState_Stage4:
		for (auto& m_poison : m_poisonList) {
			DeleteGO(m_poison);
		}
		for (auto& m_lever : m_leverList) {
			DeleteGO(m_lever);
		}
		for (auto& m_Lightstand : m_Lightstand1List) {
			DeleteGO(m_Lightstand);
		}
		for (auto& m_lightobject : m_lightobjectList) {
			DeleteGO(m_lightobject);
		}
		for (auto& m_hill : m_hillList) {
			DeleteGO(m_hill);
		}
		for (auto& door : m_DoorList) {
			DeleteGO(door);
		}
		break;
	case GameData::enState_Stage5:
		for (auto& m_poison : m_poisonList) {
			DeleteGO(m_poison);
		}
		for (auto& m_hill : m_hillList) {
			DeleteGO(m_hill);
		}
		for (auto& m_lightobject : m_lightobjectList) {
			DeleteGO(m_lightobject);
		}
		for (auto& m_Lightstand : m_Lightstand1List) {
			DeleteGO(m_Lightstand);
		}
		break;
	/*case GameData::enState_Stage6:
		for (auto& m_poison : m_poisonList) {
		DeleteGO(m_poison);
	    }
     	for (auto& m_lever : m_leverList) {
		DeleteGO(m_lever);
     	}
	    for (auto& moveBed : m_moveBedList) {
		DeleteGO(moveBed);
	    }
	   for (auto& moveBed_zengo_long : m_moveBed_zengo2List) {
		DeleteGO(moveBed_zengo_long);
	    }
			break;*/
	}
	QueryGOs<prefab::CEffect>(m_gamedata->GetEffectName(), [&](prefab::CEffect* effect) {
		DeleteGO(effect);
		return true;
		});
	if (m_checkpoint != nullptr) {
		DeleteGO(m_checkpoint);
	}
}

bool Game::Start()
{
	m_gamedata = &GameData::GetInstance();
	shadow::DirectionShadowMap().Disable();
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.1f, 0.1f, 0.1f });
	//シーンの明るさを落とす。
	postEffect::Tonemap().SetLuminance(0.01f);
	
	//試験的なコード。今はレベルに対応していないのでここに書きます。
	//NewGO<Hill>(0, "Hill");

	m_human = NewGO<Human>(0, "Human");
	m_player = NewGO<Player>(0, "Player");
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	m_fade = FindGO<Fade>("Fade");
	m_mistenemy = NewGO<MistEnemy>(0, "mist");//後でlfevelに0組み込み
	m_sky = NewGO<prefab::CSky>(0, "Sky");
	m_sky->SetScale({ 5000.0f,5000.0f,5000.0f });
	m_sky->SetEmissionColor({ 0.05f, 0.05f, 0.05f });

	
	//m_pos.x += 500.0f;
	switch (m_gamedata->GetStageNumber()) {
	case GameData::enState_Stage1:
		Stage1();
		break;
	case GameData::enState_Stage2:
		Stage2();
		break;
	case GameData::enState_Stage3:
		Stage3();
		break;
	case GameData::enState_Stage4:
		Stage4();
		break;
	case GameData::enState_Stage5:
		Stage5();
		break;
	
	}

	m_fade->StartFadeIn();

	//全方位シャドウを有効にする
	shadow::OminiDirectionShadowMap().Enable();
	if (m_gamedata->GetisStartCheckPoint() && m_checkpoint != nullptr) {
		m_human->SetPosition(m_checkpoint->GetPosition());
		//ごり押し
		CVector3 m_pos = m_checkpoint->GetPosition();
	  switch (m_gamedata->GetStageNumber()) {
	   case GameData::enState_Stage1:
		m_pos.x -= 500.0f;
		break;
	   case GameData::enState_Stage2:
		   m_pos.z -= 500.0f;
		break;
	   case GameData::enState_Stage3:
		m_pos.z -= 500.0f;
		break;
	   case GameData::enState_Stage4:
		   m_pos.x += 500.0f;
		break;
	   case GameData::enState_Stage5:
		   m_pos.z -= 500.0f;
		break;
	
	   }
		m_player->SetPosition(m_pos);
		m_gamecamera->SetCameraDegree(m_gamedata->GetCheckPointCameraDegree());
	}
 	return true;
}

void Game::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Stage_Select>(0,"Stage_Select");
			DeleteGO(this);
		}
	}
	else {
		if (m_isgameover) {
			m_timer2 += GameTime().GetFrameDeltaTime();
			if (m_timer2 >= m_time2) {
				m_fade->StartFadeOut();
				m_isWaitFadeout = true;
			}
		}
		Pose();
	}
	if (m_Gamesyuuryou) {
		m_Gamesyuuryou = false;
		DeleteGO(this);
	}

	m_sky->SetPosition(m_player->GetPosition());
	//m_human = FindGO<Human>("Human");
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
	if (m_checkpoint != nullptr) {
		CVector3 diff = m_human->GetPosition() - m_checkpoint->GetPosition();
		if (diff.LengthSq() <= 550.0f*550.0f) {
			m_gamedata->SetStageCheck();
			m_checkpoint->SetPass(true);
		}
	}
}

void Game::Pose()
{
	const float tate = 150.0f;
	const float yoko = 280.0f;
	//スティックの入力量を受け取る
	if (!m_isPose) { //!=trueとか==trueとかをなくしました。
		if (!m_damege) {
			if (Pad(0).IsTrigger(enButtonStart)) {
				m_isPose = true;
			}
			return;
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonRight)) {
			switch (m_state) {
			case togame:
				m_state = retire;
				m_arrowpos.x = 0.0f;
				break;
			}
		}
		else if (Pad(0).IsTrigger(enButtonLeft)) {
			switch (m_state)
			{
			case Game::retire:
				m_state = togame;
				m_arrowpos.x = -400.0f;
				break;
			}
		}
		if (Pad(0).IsTrigger(enButtonA)) {
			switch (m_state)
			{
			case Game::retire:
				m_isPose = false;
				m_fade->StartFadeOut();
				m_isWaitFadeout = true;
				m_isbutton = true;
				break;
			case Game::togame:
				m_isPose = false;
				m_isbutton = true;
				break;
			}
		}
	
	}
}
void Game::Stage1()
{
	
	m_level.Init(L"level/level_Stage01.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"Stage1")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			return true;
		}
		////offランタン
		//else if (objdata.ForwardMatchName(L"lanthanum1")) {
		//	Light_Object* m_lightobject = NewGO<Light_Object>(0, "LightObject");
		//	m_lightobject->SetPosition(objdata.position);//試験したいなら{0,0,0}
		//	m_lightobject->SetScale(objdata.scale);
		//	m_lightobject->SetRotation(objdata.rotation);
		//	m_lightobjectList.push_back(m_lightobject);

		//	return true;
		//}
		//onランタン
		else if (objdata.EqualObjectName(L"lanthanum2")) {
			Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
			m_onlightObject->SetPosition(objdata.position);
			m_onlightObject->SetScale(objdata.scale);
			m_onlightObject->SetRotation(objdata.rotation);
			m_onlightObject->SetLight();
			m_lightobjectList.push_back(m_onlightObject);
			return true;
		}
		//大きいランタン
		else if (objdata.EqualObjectName(L"Big_lanthanum")) {
			Light_Object* m_biglightObject = NewGO<Light_Object>(0, "Big_LightObject");
			m_biglightObject->SetPosition(objdata.position);
			m_biglightObject->SetScale(objdata.scale);
			m_biglightObject->SetRotation(objdata.rotation);
			m_biglightObject->SetLight();
			m_biglightObject->Biglight();
			m_lightobjectList.push_back(m_biglightObject);
			return true;
		}
		//動く床は2種類ある、MoveBedは横移動するもの
		else if (objdata.EqualObjectName(L"MoveBed1")) {
			MoveBed* movebed = NewGO<MoveBed>(0, "MoveBed1");
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
		/*else if (objdata.EqualObjectName(L"BlackUnityChan")) {
			m_enemy = NewGO<Enemy>(0, "Enemy");
			m_enemy->SetPosition(objdata.position);
			m_enemy->SetRotation(objdata.rotation);
			return true;
		}*/
		else if (objdata.ForwardMatchName(L"Lever")) {
			int num = _wtoi(&objdata.name[5]);
			Lever* m_lever = NewGO<Lever>(n, "Lever");
			m_lever->SetPosition(objdata.position);
			m_lever->SetRotation(objdata.rotation);
			m_lever->SetScale(objdata.scale);
			m_lever->SetLeverTime(num);
			m_leverList.push_back(m_lever);

			return true;
		}
		//ガス
		else if (objdata.ForwardMatchName(L"huzitubo")) {
			int num = _wtoi(&objdata.name[8]);
			Poison* m_poison = NewGO<Poison>(0, "Poison");
			m_poison->SetPosition(objdata.position);
			m_poison->SetPoisonNumber(num);
			//レバーで動く
			m_poison->SetPoisonMoveNumber(1);
			m_poisonList.push_back(m_poison);


			return true;
		}
		//松明
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
		//オブジェクトねーーむ確認
		else if (objdata.EqualObjectName(m_checkpointname)) {
			m_checkpoint = NewGO<CheckPoint>(0, "CheckPoint");
			m_checkpoint->SetPosition(objdata.position);
			m_checkpoint->SetPass(m_gamedata->GetisStageCheck(m_gamedata->GetStageNumber()));
			return true;
		}
		return false;
		});
}
void Game::Stage2()
{
	m_level.Init(L"level/level_Stage02.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"Stage2")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			m_background->SetPosition(objdata.position);
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
		//ガス
		else if (objdata.ForwardMatchName(L"huzitubo")) {
			int num = _wtoi(&objdata.name[8]);
			Poison* m_poison = NewGO<Poison>(0, "Poison");
			m_poison->SetPosition(objdata.position);
			m_poison->SetPoisonNumber(num);
			//順番に噴き出す
			m_poison->SetPoisonMoveNumber(2);
			m_poisonList.push_back(m_poison);


			return true;
		}
		//レバー
		else if (objdata.ForwardMatchName(L"Lever")) {
			int num = _wtoi(&objdata.name[5]);
			Lever* m_lever = NewGO<Lever>(n, "Lever");
			m_lever->SetPosition(objdata.position);
			m_lever->SetRotation(objdata.rotation);
			m_lever->SetScale(objdata.scale);
			m_lever->SetLeverTime(num);
			m_leverList.push_back(m_lever);

			return true;
		}
		//松明
		else if (objdata.ForwardMatchName(L"Lightstand")) {
			//Lightstandの種類
			//int num = _wtoi(&objdata.name[10]);
			//Lightstandを手動でオンオフにする。
			int lever = _wtoi(&objdata.name[11]);
			
			Lightstand* m_Lightstand = NewGO<Lightstand>(0, "Lightstand");
			//???numを使ってできない。
			m_Lightstand->SetNum(1);
			if (lever == 0 || lever == 1) {
				m_Lightstand->LightLever();
				m_Lightstand->SetLeverNum(lever);
			}
			m_Lightstand->SetPosition(objdata.position);
			m_Lightstand->SetRotation(objdata.rotation);
			m_Lightstand->SetScale(objdata.scale);

			m_Lightstand1List.push_back(m_Lightstand);
			return true;
		}
		//岩
		else if (objdata.ForwardMatchName(L"Stone")) {
			int num = _wtoi(&objdata.name[5]);
			Stone* m_stone = NewGO<Stone>(0, "Stone");
			m_stone->SetStoneNumber(num);
			//Stone２の調整
			if (num == 2) {
				m_stone->SetStoneScaleNum(num);
			}
			m_stone->SetScale(objdata.scale);
			m_stone->SetRot(objdata.rotation);
			m_stone->SetPosition(objdata.position);
			m_stone->SetProtPosition(objdata.position);
			
			m_StoneList.push_back(m_stone);
			return true;
		}
		//ドア
		else if (objdata.EqualObjectName(L"Door")) {
			Door*door = NewGO<Door>(0, "Door");
			door->SetPosition(objdata.position);
			door->SetScale(objdata.scale);
			door->SetNum(0);
			m_DoorList.push_back(door);
			return true;
		}
		//onランタン
		else if (objdata.EqualObjectName(L"lanthanum2")) {
			Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
			m_onlightObject->SetPosition(objdata.position);
			m_onlightObject->SetScale(objdata.scale);
			m_onlightObject->SetRotation(objdata.rotation);
			m_onlightObject->SetLight();
			m_lightobjectList.push_back(m_onlightObject);
			return true;
		}
		else if (objdata.EqualObjectName(m_checkpointname)) {
			m_checkpoint = NewGO<CheckPoint>(0, "CheckPoint");
			m_checkpoint->SetPosition(objdata.position);
			m_checkpoint->SetPass(m_gamedata->GetisStageCheck(m_gamedata->GetStageNumber()));
			return true;
		}
		return false;
	});
}
void Game::Stage3()
{
	m_level.Init(L"level/level_Stage03.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"Stage3")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			m_background->SetPosition(objdata.position);
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
		//ガス
		else if (objdata.ForwardMatchName(L"huzitubo")) {
			int num = _wtoi(&objdata.name[8]);
			Poison* m_poison = NewGO<Poison>(n, "Poison");
			m_poison->SetPosition(objdata.position);
			////レバーで噴き出す
			if (num == 0 ||num == 1) {
				m_poison->SetPoisonNumber(num);
				m_poison->SetPoisonMoveNumber(1);
			}//常に噴き出す
			if (num == 4){
				m_poison->SetPoisonNumber(num);
				m_poison->SetPoisonMoveNumber(num);
		     }
			if (num == 3) {
				m_poison->SetPoisonNumber(1);
				m_poison->SetPoisonMoveNumber(num);
				
			}
			m_poisonList.push_back(m_poison);
			return true;
		}
		//レバー
		else if (objdata.ForwardMatchName(L"Lever")) {
			int num = _wtoi(&objdata.name[5]);
			Lever* m_lever = NewGO<Lever>(n, "Lever");
			m_lever->SetPosition(objdata.position);
			m_lever->SetRotation(objdata.rotation);
			m_lever->SetScale(objdata.scale);
			m_lever->SetLeverTime(1);
			m_leverList.push_back(m_lever);

			return true;
		}
		//岩
		else if (objdata.ForwardMatchName(L"Stone")) {
			int num = _wtoi(&objdata.name[5]);
			Stone* m_stone = NewGO<Stone>(n, "Stone");
			m_stone->SetStoneNumber(num);
			//Stone２の調整
			m_stone->SetStoneScaleNum(0);
			m_stone->SetScale(objdata.scale);
			m_stone->SetRot(objdata.rotation);
			m_stone->SetPosition(objdata.position);
			m_stone->SetProtPosition(objdata.position);

			m_StoneList.push_back(m_stone);
			return true;
		}
		//松明
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
		//onランタン
		else if (objdata.EqualObjectName(L"lanthanum2")) {
			Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
			m_onlightObject->SetPosition(objdata.position);
			m_onlightObject->SetScale(objdata.scale);
			m_onlightObject->SetRotation(objdata.rotation);
			m_onlightObject->SetLight();
			m_lightobjectList.push_back(m_onlightObject);
			return true;
		}
		//ヒル
		else if (objdata.EqualObjectName(L"Hill")) {
			Hill* m_hill = NewGO<Hill>(0, "Hill");
			m_hill->SetPosition(objdata.position);
			m_hill->SetRotation(objdata.rotation);
			m_hill->SetScale(objdata.scale);
			m_hillList.push_back(m_hill);
			return true;
		}
		//チェックポイント
		else if (objdata.EqualObjectName(m_checkpointname)) {
			m_checkpoint = NewGO<CheckPoint>(0, "CheckPoint");
			m_checkpoint->SetPosition(objdata.position);
			m_checkpoint->SetPass(m_gamedata->GetisStageCheck(m_gamedata->GetStageNumber()));
			return true;
		}
		return false;
	});

}
void Game::Stage4()
{
	m_level.Init(L"level/level_Stage04.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"Stage4")) {
			m_background = NewGO<BackGround>(0, "BackGround");
			m_background->SetPosition(objdata.position);
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
		//ヒル
		else if (objdata.EqualObjectName(L"Hill")) {
			Hill* m_hill = NewGO<Hill>(0, "Hill");
			m_hill->SetPosition(objdata.position);
			m_hill->SetRotation(objdata.rotation);
			m_hill->SetScale(objdata.scale);
			m_hillList.push_back(m_hill);
			return true;
		}
		//ドア
		else if (objdata.EqualObjectName(L"Door")) {
			Door* door = NewGO<Door>(0, "Door");
			door->SetPosition(objdata.position);
			door->SetScale(objdata.scale);
			door->SetRot(objdata.rotation);
			door->SetNum(1);
			m_DoorList.push_back(door);
			return true;
		}
		//レバー
		else if (objdata.ForwardMatchName(L"Lever")) {
			int num = _wtoi(&objdata.name[5]);
			Lever* m_lever = NewGO<Lever>(n, "Lever");
			m_lever->SetPosition(objdata.position);
			m_lever->SetRotation(objdata.rotation);
			m_lever->SetScale(objdata.scale);
			m_lever->SetLeverTime(num);
			m_leverList.push_back(m_lever);

			return true;
		}
		//ガス
		else if (objdata.ForwardMatchName(L"huzitubo")) {
			int num = _wtoi(&objdata.name[8]);
			Poison* m_poison = NewGO<Poison>(n, "Poison");
			m_poison->SetPosition(objdata.position);
			//常に噴き出す
			if (num == 4) {
				m_poison->SetPoisonNumber(num);
				m_poison->SetPoisonMoveNumber(num);
			}
			else {
				m_poison->SetPoisonNumber(num);
				m_poison->SetPoisonMoveNumber(2);

			}
			m_poisonList.push_back(m_poison);
			return true;
		}
		//松明
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
		//onランタン
		else if (objdata.EqualObjectName(L"lanthanum2")) {
			Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
			m_onlightObject->SetPosition(objdata.position);
			m_onlightObject->SetScale(objdata.scale);
			m_onlightObject->SetRotation(objdata.rotation);
			m_onlightObject->SetLight();
			m_lightobjectList.push_back(m_onlightObject);
			return true;
		}
		//チェックポイント
		else if (objdata.EqualObjectName(m_checkpointname)) {
			m_checkpoint = NewGO<CheckPoint>(0, "CheckPoint");
			m_checkpoint->SetPosition(objdata.position);
			m_checkpoint->SetPass(m_gamedata->GetisStageCheck(m_gamedata->GetStageNumber()));
			return true;
		}
		return false;
	});
}
void Game::Stage5()
{
	m_level.Init(L"level/level_Stage05.tkl", [&](LevelObjectData & objdata) {
			if (objdata.EqualObjectName(L"Stage5")) {
				m_background = NewGO<BackGround>(0, "BackGround");
				m_background->SetPosition(objdata.position);
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
			
			//ガス
			else if (objdata.ForwardMatchName(L"huzitubo")) {
				int num = _wtoi(&objdata.name[8]);
				Poison* m_poison = NewGO<Poison>(n, "Poison");
				m_poison->SetPosition(objdata.position);
					m_poison->SetPoisonNumber(num);
					m_poison->SetPoisonMoveNumber(num);
				m_poisonList.push_back(m_poison);
				return true;
			}
			//ヒル
			else if (objdata.ForwardMatchName(L"Hill")) {
				int num = _wtoi(&objdata.name[4]);
				Hill* m_hill = NewGO<Hill>(0, "Hill");
				m_hill->SetKill(num);
				m_hill->SetPosition(objdata.position);
				m_hill->SetRotation(objdata.rotation);
				m_hill->SetScale(objdata.scale);
				m_hillList.push_back(m_hill);
				return true;
			}
			//onランタン
			else if (objdata.EqualObjectName(L"lanthanum2")) {
				Light_Object* m_onlightObject = NewGO<Light_Object>(0, "OnLightObject");
				m_onlightObject->SetPosition(objdata.position);
				m_onlightObject->SetScale(objdata.scale);
				m_onlightObject->SetRotation(objdata.rotation);
				m_onlightObject->SetLight();
				m_lightobjectList.push_back(m_onlightObject);
				return true;
			}
			//大きいランタン
			else if (objdata.EqualObjectName(L"Big_lanthanum")) {
				int num = _wtoi(&objdata.name[13]);
				Light_Object* m_biglightObject = NewGO<Light_Object>(0, "Big_LightObject");
				m_biglightObject->SetPosition(objdata.position);
				m_biglightObject->SetScale(objdata.scale);
				m_biglightObject->SetRotation(objdata.rotation);
				m_biglightObject->SetLight();
				m_biglightObject->Biglight();
				m_lightobjectList.push_back(m_biglightObject);
				return true;
			}
			//最後に設置しているランタン
			else if (objdata.ForwardMatchName(L"Lastlanthanum")) {
				Light_Object* m_LastlightObject = NewGO<Light_Object>(0, "LastLightObject");
				int num = _wtoi(&objdata.name[13]);
				m_LastlightObject->SetPosition(objdata.position);
				m_LastlightObject->SetScale(objdata.scale);
				m_LastlightObject->SetRotation(objdata.rotation);
				m_LastlightObject->Lastlightnumber(num);
				m_LastlightObject->Lastlight();
				m_lightobjectList.push_back(m_LastlightObject);
				return true;
			}
			//松明
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
			//チェックポイント
			else if (objdata.EqualObjectName(m_checkpointname)) {
				m_checkpoint = NewGO<CheckPoint>(0, "CheckPoint");
				m_checkpoint->SetPosition(objdata.position);
				m_checkpoint->SetPass(m_gamedata->GetisStageCheck(m_gamedata->GetStageNumber()));
				return true;
			}
			return false;
	});
	
}

void Game::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	if (m_human->GetisGameOver()) {
		if (m_timer >= 1.0f) {
			m_timer = 1.0f;
			m_isgameover = true;
		}
		m_font.Begin(renderContext);
		CVector4 Red = { m_timer,0.0f,0.0f,1.0f };
		wchar_t aaa[20];
		swprintf(aaa, L"GAME  OVER");
		m_font.Draw(aaa, { 0.0f,200.0f }, Red, 0.0f, 2.3f);
		m_font.End(renderContext);
		m_timer += GameTime().GetFrameDeltaTime() / 2;
	}
	else if (m_isPose) {
		CVector4 Yellow = { 1.0f,1.0f,0.0f,1.0f };
		CVector4 Transparent = { 0.5f,0.5f,0.0f,1.0f };
		m_font.Begin(renderContext);
		if (m_state == retire) {
			wchar_t aaa[20];
			swprintf(aaa, L"RETIRE");
			m_font.Draw(aaa, { 180.0f,00.0f }, Yellow, 0.0f, 1.3f);
			wchar_t aaa2[20];
			swprintf(aaa2, L"CONTINUE");
			m_font.Draw(aaa2, { -200.0f,00.0f }, Transparent, 0.0f, 1.3f);

		}
		else {
			wchar_t aaa[20];
			swprintf(aaa, L"RETIRE");
			m_font.Draw(aaa, { 180.0f,00.0f }, Transparent, 0.0f, 1.3f);
			wchar_t aaa2[20];
			swprintf(aaa2, L"CONTINUE");
			m_font.Draw(aaa2, { -200.0f,00.0f }, Yellow, 0.0f, 1.3f);
		}
		m_font.End(renderContext);
	}

}