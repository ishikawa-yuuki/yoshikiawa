#include "stdafx.h"
#include "BackGround.h"
#include "SSPlayer.h"
#include "GameData.h"

BackGround::BackGround()
{
}



BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_sound);
}
bool BackGround::Start()
{
	m_gamedata = &GameData::GetInstance();
	PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_sound = NewGO<prefab::CSoundSource>(0);
	
	switch (m_gamedata->GetStageNumber())
	{
	case GameData::enState_Stage1:
		m_skinModelRender->Init(L"modelData/StageMap/Stage1.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		break;
	case GameData::enState_Stage2:
		m_skinModelRender->Init(L"modelData/StageMap/Stage2.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		//m_skinModelRender->SetPosition(m_position);
		break;
	case  GameData::enState_Stage3:
		m_skinModelRender->Init(L"modelData/StageMap/Stage3.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		//m_skinModelRender->SetPosition(m_position);
		break;
	case  GameData::enState_Stage4:
		m_skinModelRender->Init(L"modelData/StageMap/Stage4.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		//m_skinModelRender->SetPosition(m_position);
		break;
	case  GameData::enState_Stage5:
		m_skinModelRender->Init(L"modelData/StageMap/Stage5.cmo");//7ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		//m_skinModelRender->SetPosition(m_position);
		break;
	}
	if (m_gamedata->GetStageNumber() <= GameData::enState_Stage4) {
		m_sound->Init(L"sound/wind.wav");
		m_sound->SetVolume(0.1f);
		m_sound->Play(true);
	}
	//反射テクスチャをロードする。
	m_refTexture.CreateFromDDSTextureFromFile(L"sprite/ref.dds");

	m_skinModelRender->FindMaterial([&](CModelEffect * mat) {
		mat->SetSpecularMap(m_refTexture.GetBody());
		});
	m_skinModelRender->SetShadowReceiverFlag(true);
	return true;
}
void BackGround::Update()
{

}