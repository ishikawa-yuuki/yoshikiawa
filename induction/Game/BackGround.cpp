#include "stdafx.h"
#include "BackGround.h"


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
	m_skinModelRender->Init(L"modelData/stage_test.cmo");//���X�e�[�W
	CVector3 scale = { 20.0f,20.0f,20.0f };
	m_skinModelRender->SetScale(scale);//�v������菬���������̂�20�{
	return true;
}
void BackGround::Update()
{

}