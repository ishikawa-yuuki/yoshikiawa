#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_effect);
}

bool Player::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	m_position.y = 100.0f;
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position//0,100,0
	);
	m_charaCon.Execute(m_position);
	m_charaCon.SetPosition(m_position);
	m_effect->SetPosition(m_position);
	
	return true;
}

void Player::Update()
{
	//�v���C���[�̌��̐F��ς���Human�ɊȒP�Ȏw�����o����悤��
	//����ȃv���O�������l���Ă܂��A�A�A�A
	Color_Change();
	Move();
	m_effect->SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
}

void Player::Move()
{
	const float pl_speed = 600.0f;//���̑��x
	float L_Stick_X = Pad(0).GetLStickXF();
	float L_Stick_Y = Pad(0).GetLStickYF();

	CVector3 CameraForword = MainCamera().GetForward(); // �J�����̑O�����̎擾
	CVector3 CameraRight = MainCamera().GetRight();  //�J�����̉������̎擾

	CameraForword.y = 0.0f;
	CameraForword.Normalize();//�������E�O
	CameraRight.y = 0.0f;
	CameraRight.Normalize();//�������E��
	m_moveSpeed = CVector3::Zero;
	m_moveSpeed += CameraForword * L_Stick_Y * pl_speed;
	m_moveSpeed += CameraRight * L_Stick_X * pl_speed;
	m_position =m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
}

void Player::Color_Change()
{
	if (Pad(0).IsTrigger(enButtonUp)) {
		switch (m_color) {
		case hikari_hutu:
			m_color = hikari_red;
			m_effect->Release();
			m_effect->Play(L"effect/red_hikari.efk");
			m_effect->SetScale({ 30.0f,30.0f,30.0f });
		}
	}
	else if (Pad(0).IsTrigger(enButtonDown)) {
		switch (m_color){
		case hikari_red:
			m_color = hikari_hutu;
			m_effect->Release();
			m_effect->Play(L"effect/hikari.efk");
			m_effect->SetScale({ 30.0f,30.0f,30.0f });
		}
	}
}