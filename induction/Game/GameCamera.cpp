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
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
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
	m_PlayerPos = m_player->GetPosition();
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
	stickR.y = Pad(0).GetLStickYF();	//アナログスティックのxの入力量を取得。
	stickR.z = 0.0f;
	//右スティックの入力
	//右スティック
	m_sdegreexz = -stickR.x * 1.0f;
	m_sdegreey = -stickR.y*1.0f;

	//回転度加算
	m_degreey += m_sdegreey;
	m_degreexz += m_sdegreexz;
	//上下方向のカメラ移動を固定
	m_degreey = 30.0f;
	/*if (m_degreey >= 30.0f) {//cameraを上方向に動かすプログラム
	m_degreey = 30.0f;         //ただしあまり強く上には動かない。
	}
	if (m_degreey <= 10.0f) {
	m_degreey = 10.0f;
	}*/
	/*if (m_degreexz >= 70.0f) {
	m_degreexz = 70.0f;
	}
	if (m_degreexz <= -70.0f) {
	m_degreexz = -70.0f;
	}*/

	//角度をラジアン単位に直す
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//follow();
	//m_target.z += 350.0f;
	//視点z
	MainCamera().SetTarget(m_target);
	//座標
	MainCamera().SetPosition(m_position);
	//カメラの更新。
	MainCamera().Update();
}

void GameCamera::Hutu()
{
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += 20.0f;
	m_target += m_player->GetPosition();
	//注視点を計算する。
	//target.y += 200.0f;
	//Y軸周りに回転させる。
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	CVector3 ToPos = { 0.0f, 0.0f, 3.0f };
	qRot.Multiply(ToPos);
	//上下の回転。
	//まずは回す軸を計算する。
	CVector3 rotAxis;

	rotAxis.Cross(ToPos, CVector3::AxisY);
	//ベクトルを正規化する。
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(ToPos);
	ToPos *= m_r;
	m_position = m_target + ToPos * 1.75f;

	/*ps = toPos / r;
	CVector3 rotAxis3;
	rotAxis3.Cross(toPos, CVector3::AxisY);
	rotAxis3.Normalize();
	rotAxis3.y -= rotAxis3.y;
	ps = rotAxis3;*/

	ToPos *= 2;
	//m_toPos.y = 0.0f;
	m_target -= ToPos;
	ToPos *= 1.5f;
	/*toPos.x = -r * cos(radianx);
	toPos.y = r * sin(radiany);
	toPos.z=r*(sin(radianx)+cos(radiany));*/
	//toPos.z = r * sin(radianx);
}

//今は使えないfollow関数、
void GameCamera::follow()
{
	//プレイヤーに追従するばねカメラ
	//横方向には自由に回転させることができるようにしたい。
	CVector3 Old_Topos = m_ToPos;
	CVector3 HumanPos = m_human->GetPosition();
	CVector3 diff = m_PlayerPos - HumanPos;
	float len = diff.LengthSq();
	if (len >= 300.0f*300.0f) {
		m_ToPos += {0.0f, 4.0f, 0.0f};//だんだん離れる
		if (m_ToPos.y > 950.0f) {
			m_ToPos = Old_Topos; //カメラが光に離れすぎないよう固定
		}
	}
	else if (len <= 150.f) {
		m_ToPos -= {0.0f, 6.0f, 0.0f};//どんどん近寄る
		if (m_ToPos.y < 450.0f) {
			m_ToPos = Old_Topos;//カメラが光に寄りすぎないよう固定
		}
	}
	CVector3 CameraPos = m_PlayerPos + m_ToPos;
	MainCamera().SetTarget(m_PlayerPos);//プレイヤーの位置を注視点にする。
	MainCamera().SetPosition(CameraPos);
	MainCamera().Update();
}