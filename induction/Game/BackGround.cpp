#include "stdafx.h"
#include "BackGround.h"
#include "SSPlayer.h"

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
}
bool BackGround::Start()
{
	PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/StageMap/Stage1.cmo");//仮ステージ
	//CVector3 scale = { 20.0f,20.0f,20.0f };
	//m_skinModelRender->SetScale(scale);//思ったより小さかったので20倍
	m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, CVector3::One, m_skinModelRender);

	return true;
}
void BackGround::Update()
{

}