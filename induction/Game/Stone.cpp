#include "stdafx.h"
#include "Stone.h"
#include "Player.h"

Stone::Stone()
{
}


Stone::~Stone()
{
	DeleteGO(m_skin);
	DeleteGO(m_sound);
}
bool Stone::Start()
{
	m_player = FindGO<Player>("Player");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/Stone/Stone.cmo");
	m_skin->SetPosition(m_position);
	m_skin->SetScale(m_scale);
	m_skin->SetRotation(m_rot);
	//Scale500の場合
	if (m_scalenum == 2) {
		m_GhostObject.CreateBox(
			m_position,
			m_rot,
			{ 650.0f,650.0f ,650.0f }//{100,100,100}
		);
		pos = 310;
	}//Scale600,700の場合
	else {
		m_GhostObject.CreateBox(
			m_position,
			m_rot,
			{ 800.0f,700.0f ,800.0f }//{100,100,100}
		);
		pos = 330;
	}
	m_sound = NewGO<prefab::CSoundSource>(0);
	m_sound->Init(L"sound/Stone2.wav");
	m_sound->Play(true);
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);
	return true;
}
void Stone::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 1.0f;
	}
	else if (diff.LengthSq() < range * 2.0) {
		m_volume = 0.5f;
	}
	else if (diff.LengthSq() < range * 4.0) {
		m_volume = 0.25f;
	}
	else if(m_volume>= 0.0f){
		m_volume -= 0.01f;
		
	}
	else {
		m_volume = 0.0f;
	}
}
void Stone::Update()
{
	
	switch (m_num) {
	case 0:
		m_moveSpeed.x = MOVE_SPEED;
		m_axis = CVector3::AxisZ;
		m_angle = -ANGLE_SEED;
		break;
	case 1:
		m_moveSpeed.x = -MOVE_SPEED;
		m_axis = CVector3::AxisZ;
		m_angle = ANGLE_SEED;
		break;
	case 2:
		m_moveSpeed.z = MOVE_SPEED;//_HIGH;
		m_axis = CVector3::AxisX;
		m_angle = ANGLE_SEED;
		break;
	case 3:
		m_moveSpeed.z = -MOVE_SPEED;
		m_axis = CVector3::AxisX;
		m_angle = -ANGLE_SEED;
		break;
	case 4:
		m_moveSpeed.x = -MOVE_SPEED;
		m_axis = CVector3::AxisX;
		m_angle = ANGLE_SEED;
		break;
	}
		if (!m_charaCon.IsOnGround()) {
			
			m_timer += GameTime().GetFrameDeltaTime();
			m_moveSpeed.y -= 10000.0f * GameTime().GetFrameDeltaTime();
			//m_sound->SetVolume(0.0f);
		}
		else {
			m_moveSpeed.y = 0;
			
			
		}
		Range();
		m_sound->SetVolume(m_volume);
			m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
			m_skinposition = m_position;
			//base 50
			m_skinposition.y += pos;
			//毎フレーム少しづつ回転させていく。
			CQuaternion addRot;
			addRot.SetRotationDeg(
				m_axis,		//回転軸。今回はX軸を指定している。xc
			    m_angle			    //加算する回転角度。
		);
		m_rot *= addRot;
		//落下したので最初のpositionに移動
		if (m_timer >= 1.0f) {
				m_timer = 0;
				m_moveSpeed = CVector3::Zero;
				m_position = m_protposition;
		}
		m_skin->SetPosition(m_skinposition);
		m_charaCon.SetPosition(m_position);
		m_GhostObject.SetPosition(m_skinposition);
		m_skin->SetRotation(m_rot);
}
