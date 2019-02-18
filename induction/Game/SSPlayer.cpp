#include "stdafx.h"
#include "SSPlayer.h"


SSPlayer::SSPlayer()
{
}


SSPlayer::~SSPlayer()
{
	DeleteGO(m_effect);
}
bool SSPlayer::Start()
{
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });
	return true;
}

void SSPlayer::Update()
{
	Move();
	m_effect->SetPosition(m_position);
}

void SSPlayer::Move()
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
