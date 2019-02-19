#include "stdafx.h"
#include "Player.h"


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
	
	return true;
}

void Player::Update()
{
	//プレイヤーの光の色を変えてHumanに簡単な指示を出せるような
	//そんなプログラムを考えてます、、、、
	Color_Change();
	Move();
	m_effect->SetPosition(m_position);
}

void Player::Move()
{
	float pl_speed = 600.0f;//光の速度
	float L_Stick_X = Pad(0).GetLStickXF();
	float L_Stick_Y = Pad(0).GetLStickYF();

	CVector3 CameraForword = MainCamera().GetForward(); // カメラの前方向の取得
	CVector3 CameraRight = MainCamera().GetRight();  //カメラの横方向の取得

	CameraForword.y = 0.0f;
	CameraForword.Normalize();//方向情報・前
	CameraRight.y = 0.0f;
	CameraRight.Normalize();//方向情報・横

	m_position += CameraForword * L_Stick_Y * pl_speed * GameTime().GetFrameDeltaTime();
	m_position += CameraRight * L_Stick_X * pl_speed * GameTime().GetFrameDeltaTime();

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