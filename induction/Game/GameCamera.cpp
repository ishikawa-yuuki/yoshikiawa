#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Human.h"
#define _USE_MATH_DEFINES //M_PI(円周率)を呼び出し
#include <math.h>

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	 
	m_player = FindGO<Player>("Player");
	m_human = FindGO<Human>("Human");
	//カメラを設定。
	//ニアクリップとファークリップ設定(仮)
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);

	//ばねカメラの初期化
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	
	return true;
}

void GameCamera::Update()
{
//	const float r = 450.0f;
	PlayerPos = m_player->GetPosition();
//
//	CVector3 Stick_R;
//	Stick_R.x = Pad(0).GetRStickXF();
//	Stick_R.y = Pad(0).GetRStickYF();
//	Stick_R.z = 0.0f;
//	右のスティック
//	m_sdegreexz = -Stick_R.x * 1.0f;
//	m_sdegreey = -Stick_R.y * 1.0f;
//
//	m_degreexz += m_sdegreexz;
//	m_degreey += m_sdegreey;
//
//	m_degreey = 45.0f;
//	/*if (m_degreexz >= 70.0f) {
//	m_degreexz = 70.0f;
//	}
//	if (m_degreexz <= -70.0f) {
//	m_degreexz = -70.0f;
//	}
//*/
//	m_radianx = M_PI / 180.0f * m_degreexz;
//	m_radiany = M_PI / 180.0f * m_degreey;
//	CQuaternion qrot;
//	qrot.SetRotation(CVector3::AxisY,m_radianx);
//	CVector3 m_ToPos = { 0.0f,0.0f,2.0f };
//	qrot.Multiply(m_ToPos);
//
//	CVector3 rotAxis;
//	rotAxis.Cross(m_ToPos, CVector3::AxisY);
//	rotAxis.Normalize();
//	qrot.SetRotation(rotAxis, m_radiany);
//	qrot.Multiply(m_ToPos);
//	m_ToPos *= r;
//	m_position = PlayerPos + m_ToPos;
//	m_position.y += 250.0f;
//	
//	/*CVector3 CameraPos = PlayerPos + m_ToPos * 2.0;
//	m_ToPos *= 2;
//	
//	PlayerPos -= m_ToPos;
//	m_ToPos *= 1.5f;*/
	follow();
	//m_springCamera.SetTarget(PlayerPos);//プレイヤーの位置を注視点にする。
	//m_springCamera.SetPosition(m_position);
	//m_springCamera.Update();
}

void GameCamera::follow()
{
	//プレイヤーに追従するばねカメラ
	//横方向には自由に回転させることができるようにしたい。
	CVector3 Old_Topos = m_ToPos;
	CVector3 HumanPos = m_human->GetPosition();
	CVector3 diff = PlayerPos - HumanPos;
	float len = diff.Length();
	if (len >= 300.0f) {
		m_ToPos += {0.0f, 2.0f, 2.0f};//だんだん離れる
		if (m_ToPos.y > 750.0f) {
			m_ToPos = Old_Topos; //カメラが光に離れすぎないよう固定
		}
	}
	else if (len <= 150.f) {
		m_ToPos -= {0.0f, 5.0f, 5.0f};//どんどん近寄る
		if (m_ToPos.y < 450.0f) {
			m_ToPos = Old_Topos;//カメラが光に寄りすぎないよう固定
		}
	}
	CVector3 CameraPos = PlayerPos + m_ToPos;
	m_springCamera.SetTarget(PlayerPos);//プレイヤーの位置を注視点にする。
	m_springCamera.SetPosition(CameraPos);
	m_springCamera.Update();
}