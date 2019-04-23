#include "stdafx.h"
#include "Lightstand.h"


Lightstand::Lightstand()
{
}


Lightstand::~Lightstand()
{
	DeleteGO(m_skin);
}
bool Lightstand::Start()
{
	
	if (num == 0) {
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Lightstand01.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);
		m_position.y = 10;
	}
	else if (num == 1) {
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Torches.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);
		m_position.y += 50;
		m_position.x += 30;
	}
	else if(num == 2){
		m_skin = NewGO<prefab::CSkinModelRender>(0);
		m_skin->Init(L"modelData/StageObject/Lightstand02.cmo");
		m_skin->SetPosition(m_position);
		m_skin->SetRotation(m_rot);
		m_skin->SetScale(m_scale);
		m_StaticObject.CreateBox(
			m_position,
			CQuaternion::Identity,
			{ 100.0f, 500.0f, 100.0f }
		);
	}
	
	return true;
}
void Lightstand::Update()
{
	if (m_timer >= 0.5f) {
		prefab::CEffect*  effect = NewGO<prefab::CEffect>(0);
	    effect->Play(L"effect/Fire.efk");
		effect->SetPosition(m_position);
		m_timer = 0.0f;
	}
	m_timer += GameTime().GetFrameDeltaTime();
}
	
