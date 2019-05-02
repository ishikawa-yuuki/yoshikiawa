#include "stdafx.h"
#include "BackGround.h"
#include "SSPlayer.h"
#include "Stage_Number.h"

BackGround::BackGround()
{
}



BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
}
bool BackGround::Start()
{
	m_stagenum = FindGO<Stage_Number>("Stage_Number");
	PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);

	
	switch (m_stagenum->GetStageNumber())
	{
	case 1:
		m_skinModelRender->Init(L"modelData/StageMap/Stage1.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		break;
	case 2:
		m_skinModelRender->Init(L"modelData/StageMap/Stage2.cmo");//仮ステージ
		//CVector3 scale = { 20.0f,20.0f,20.0f };
		//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);
		m_skinModelRender->SetPosition(m_position);
		break;
	}
	//反射テクスチャをロードする。
	m_refTexture.CreateFromDDSTextureFromFile(L"sprite/ref.dds");

	m_skinModelRender->FindMaterial([&](CModelEffect * mat) {
		mat->SetSpecularMap(m_refTexture.GetBody());
		});
	m_skinModelRender->SetShadowReceiverFlag(true);
	DeleteGO(m_stagenum);
	return true;
}
void BackGround::Update()
{

}