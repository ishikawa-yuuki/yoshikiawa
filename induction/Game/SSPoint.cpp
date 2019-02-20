#include "stdafx.h"
#include "SSPoint.h"


SSPoint::SSPoint()
{
}


SSPoint::~SSPoint()
{
	DeleteGO(m_skin);
}
bool SSPoint::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/StageSelect/StagePoint.cmo");//仮ステージ
	return true;
}
void SSPoint::Update()
{
	m_skin->SetPosition(m_position);
}