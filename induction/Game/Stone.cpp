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
	if (m_num == 2) {
		m_GhostObject.CreateBox(
			m_position,
			m_rot,
			{ 650.0f,650.0f ,650.0f }//{100,100,100}
		);
	}
	else {
		m_GhostObject.CreateBox(
			m_position,
			m_rot,
			{ 820.0f,700.0f ,800.0f }//{100,100,100}
		);
	}
	
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);
	return true;
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
		m_moveSpeed.z = MOVE_SPEED;
		m_axis = CVector3::AxisX;
		m_angle = ANGLE_SEED;
		break;
	case 3:
		m_moveSpeed.z = -MOVE_SPEED;
		m_axis = CVector3::AxisX;
		m_angle = -ANGLE_SEED;
		break;
	}
	/*m_moveSpeed.z = MOVE_SPEED;
	m_axis = CVector3::AxisX;*/
		if (!m_charaCon.IsOnGround()) {
			
			m_timer += GameTime().GetFrameDeltaTime();
			m_moveSpeed.y -= 10000.0f * GameTime().GetFrameDeltaTime();
			
		}
		else {
			m_moveSpeed.y = 0;
		}
		
			m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
			m_skinposition = m_position;
			//base 50
			m_skinposition.y += 300;
			//–ˆƒtƒŒ[ƒ€­‚µ‚Ã‚Â‰ñ“]‚³‚¹‚Ä‚¢‚­B
			CQuaternion addRot;
			addRot.SetRotationDeg(
				m_axis,		//‰ñ“]Ž²B¡‰ñ‚ÍXŽ²‚ðŽw’è‚µ‚Ä‚¢‚éBxc
			    m_angle			    //‰ÁŽZ‚·‚é‰ñ“]Šp“xB
		);
		m_rot *= addRot;
		//—Ž‰º‚µ‚½‚Ì‚ÅÅ‰‚Ìposition‚ÉˆÚ“®
		if (m_timer >= 0.5f) {
				m_timer = 0;
				m_moveSpeed = CVector3::Zero;
				m_position = m_protposition;
		}
		m_skin->SetPosition(m_skinposition);
		m_charaCon.SetPosition(m_position);
		m_GhostObject.SetPosition(m_skinposition);
		m_skin->SetRotation(m_rot);
}
