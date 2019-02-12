#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	return true;
}

void Player::Update()
{
	Move();
	m_effect->SetPosition(m_position);
}

void Player::Move()
{
	float pl_speed = 10.0f;//���̑��x
	float L_Stick_X = Pad(0).GetLStickXF();
	float L_Stick_Y = Pad(0).GetLStickYF();

	CVector3 CameraForword = MainCamera().GetForward(); // �J�����̑O�����̎擾
	CVector3 CameraRight = MainCamera().GetRight();  //�J�����̉������̎擾

	CameraForword.y = 0.0f;
	CameraForword.Normalize();//�������E�O
	CameraRight.y = 0.0f;
	CameraRight.Normalize();//�������E��

	m_position += CameraForword * L_Stick_Y * pl_speed;
	m_position += CameraRight * L_Stick_X * pl_speed;

}