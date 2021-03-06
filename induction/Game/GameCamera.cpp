#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Human.h"
#define _USE_MATH_DEFINES //M_PI(円周率)を呼び出し
#include <math.h>
#include "Title.h"
#include "TitleGround.h"
#include "Stage_Select.h"
#include "SSPlayer.h"
#include "Game.h"

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
	MainCamera().SetFar(20000.0f);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
	//ばねカメラの初期化
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	m_title = FindGO<Title>("Title");
	m_titleground = FindGO<TitleGround>("TitleGround");
	if (m_title != nullptr) {
		m_degreexz = 165.0f;
	}
	m_stageselect = FindGO<Stage_Select>("Stage_Select");
	m_ssplayer = FindGO<SSPlayer>("SSPlayer");
	return true;
}

void GameCamera::Update()
{
	const int explosion = 2;
	//isBlackHole();
	//GetColorで返されたのがexplosionでなければこっち
	m_refreshTimer -= GameTime().GetFrameDeltaTime();
		if (m_refreshTimer > 0.0f) {
			m_springCamera.Refresh();

		}
		if (m_stageselect != nullptr) {
			if (!m_ssplayer->GetisTransStage()) {
				m_PlayerPos = m_ssplayer->GetPosition();
			}
			//CVector3 stickR;
			//stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
			//stickR.y = Pad(0).GetLStickYF();	//アナログスティックのxの入力量を取得。
			//stickR.z = 0.0f;
			////右スティックの入力
			////右スティック
			//m_sdegreexz = -stickR.x * 1.5f;
			////m_sdegreey = -stickR.y * 1.5f;
			////回転度加算
			//m_degreey += m_sdegreey;
			//m_degreexz += m_sdegreexz;
			//角度をラジアン単位に直す
			m_radianx = M_PI / 180 * m_degreexz;
			m_radiany = M_PI / 180 * m_degreey;
			Hutu();
			//follow();
			//m_target.z += 350.0f;
			//視点z
			m_springCamera.SetTarget(m_target);
			//座標
			m_springCamera.SetPosition(m_position);
			//カメラの更新。
			m_springCamera.Update();
		}
		else if (m_human->GetisDead() == false) {
			if (m_human->GetisClear() == false) {
				if (m_title != nullptr) {
					if (m_title->isStop()) {
						/*	m_degreey += m_titleground->GetCutSpeed() * GameTime().GetFrameDeltaTime();
							CVector3 pos = m_titletarget;							pos.Cross(CVector3::AxisY);
							CQuaternion qRot;
							qRot.SetRotationDeg(pos, -m_titleground->GetCutSpeed() * GameTime().GetFrameDeltaTime());
							qRot.Multiply(m_PlayerPos);*/
					}
					else {
						m_PlayerPos = m_title->GetCameraTarget();
						m_titletarget = m_PlayerPos;
						m_titletarget.Normalize();
						m_degreey = 25.0f;
					}
				}
				else {
					m_PlayerPos = m_player->GetPosition();
					CVector3 stickR;
					stickR.x = -Pad(0).GetRStickXF();	//アナログスティックのxの入力量を取得。
					stickR.y = Pad(0).GetLStickYF();	//アナログスティックのxの入力量を取得。
					stickR.z = 0.0f;
					//右スティックの入力
					//右スティック
					m_sdegreexz = -stickR.x * 1.5f;
					//m_sdegreey = -stickR.y * 1.5f;
				}

				//回転度加算
				m_degreey += m_sdegreey;
				m_degreexz += m_sdegreexz;
				//上下方向のカメラ移動を固定
				//m_degreey = 30.0f;
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
				//Playerがブラックホールになる前の状態の時
				if (m_player != nullptr) {
					if (m_player->GetColor() == explosion) {
						//縦にカメラが揺れる。ガクガクしている。
						m_position.y += Random().GetRandInt() % 5000 * GameTime().GetFrameDeltaTime();
						m_position.x += Random().GetRandInt() % 1200 * GameTime().GetFrameDeltaTime();

					}
				}
				//follow();
				//m_target.z += 350.0f;
				//視点z
				m_springCamera.SetTarget(m_target);
				//座標
				m_springCamera.SetPosition(m_position);
				//カメラの更新。
				m_springCamera.Update();

			}
		}
}

void GameCamera::Hutu()
{
	m_target = { 0.0f,0.0f,0.0f };
	if (m_title != nullptr) {
		m_target.y += 150.0f;
	}
	else {
		m_target.y += 20.0f;
	}
	if (m_title != nullptr) {
		m_target += m_PlayerPos;
	}
	else if (m_stageselect != nullptr) {
		m_target += m_PlayerPos;
	}
	else {
		m_target += m_player->GetPosition();
	}
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
	//m_target -= ToPos;
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
	
	//CVector3 HumanPos = m_human->GetPosition();
	//HumanPos.y += 50.0f;

	//
	//CVector3 Old_Topos = m_ToPos;
	////カメラを更新。
	////注視点を計算する。
	//CVector3 target = m_player->m_position;
	////プレイヤの足元からちょっと上を注視点とする。
	//target.y += 50.0f;

	//CVector3 toCameraPosOld = m_toCameraPos;
	////パッドの入力を使ってカメラを回す。
	//float x = Pad(0).GetRStickXF();
	//float y = Pad(0).GetRStickYF();
	////Y軸周りの回転
	//CQuaternion qRot;
	//qRot.SetRotationDeg(CVector3::AxisY, 2.0f * x);
	//qRot.Multiply(m_toCameraPos);
	////X軸周りの回転。
	//CVector3 axisX;
	//axisX.Cross(CVector3::AxisY, m_toCameraPos);
	//axisX.Normalize();
	//qRot.SetRotationDeg(axisX, 2.0f * y);
	//qRot.Multiply(m_toCameraPos);
	////カメラの回転の上限をチェックする。
	////注視点から視点までのベクトルを正規化する。
	////正規化すると、ベクトルの大きさが１になる。
	////大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	//CVector3 toPosDir = m_toCameraPos;
	//toPosDir.Normalize();
	//if (toPosDir.y < -0.5f) {
	//	//カメラが上向きすぎ。
	//	m_toCameraPos = toCameraPosOld;
	//}
	//else if (toPosDir.y > 0.8f) {
	//	//カメラが下向きすぎ。
	//	m_toCameraPos = toCameraPosOld;
	//}
	//
	////視点を計算する。
	//CVector3 pos = target + m_toCameraPos;
	////バネカメラに注視点と視点を設定する。
	//m_springCamera.SetTarget(target);
	//m_springCamera.SetPosition(pos);

	////バネカメラの更新。
	//m_springCamera.Update();
	////float len = diff.LengthSq();
	////if (len >= 300.0f*300.0f) {
	////	m_ToPos += {0.0f, 4.0f, 0.0f};//だんだん離れる
	////	if (m_ToPos.y > 950.0f) {
	////		m_ToPos = Old_Topos; //カメラが光に離れすぎないよう固定
	////	}
	////}
	////else if (len <= 150.f) {
	////	m_ToPos -= {0.0f, 6.0f, 0.0f};//どんどん近寄る
	////	if (m_ToPos.y < 450.0f) {
	////		m_ToPos = Old_Topos;//カメラが光に寄りすぎないよう固定
	////	}
	////}

	//CVector3 CameraPos = m_PlayerPos + m_ToPos;
	//MainCamera().SetTarget(m_PlayerPos);//プレイヤーの位置を注視点にする。
	//MainCamera().SetPosition(CameraPos);
	//MainCamera().Update();
}
