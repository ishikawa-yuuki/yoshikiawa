#include "stdafx.h"
#include "Stone.h"


Stone::Stone()
{
}


Stone::~Stone()
{
	DeleteGO(m_skin);
}
bool Stone::Start()
{
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Stone/Stone.cmo");
	m_skin->SetPosition(m_position);
	m_skin->SetScale(m_scale);
	m_skin->SetRotation(m_rot);
	m_GhostObject.CreateBox(
		m_position,
		m_rot,
		{100.0f,100.0f ,100.0f }
	);
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);
	return true;
}
void Stone::Update()
{
	//岩をうまく転がせない
	m_moveSpeed.z = MOVE_SPEED;
	/*if (!m_charaCon.IsOnGround()) {
		m_moveSpeed.y -= 10000.0f * GameTime().GetFrameDeltaTime();
	}*/
	
	m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
	//毎フレーム少しづつ回転させていく。
	CQuaternion addRot;
	addRot.SetRotationDeg(
		{ 1, 0, 0 },		//回転軸。今回はX軸を指定している。
		3.0f			//加算する回転角度。
	);
	m_rot *= addRot;
	m_skin->SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
	m_GhostObject.SetPosition(m_position);
	m_skin->SetRotation(m_rot);
	
}
