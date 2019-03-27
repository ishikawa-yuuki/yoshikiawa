#include "stdafx.h"
#include "Exit.h"
#include "Human.h"

Exit::Exit()
{
}


Exit::~Exit()
{
	DeleteGO(m_skinModelRender);
}

bool Exit::Start()
{
	m_human = FindGO<Human>("Human");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Goal/Goal.cmo");

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_qrot);
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Exit::Update()
{

}