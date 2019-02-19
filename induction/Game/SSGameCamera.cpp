#include "stdafx.h"
#include "SSPlayer.h"
#include "SSGameCamera.h"


SSGameCamera::SSGameCamera()
{
}


SSGameCamera::~SSGameCamera()
{
}
bool SSGameCamera::Start()
{
	
	m_ssplayer = FindGO<SSPlayer>("SSPlayer");
	//カメラを設定。
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	return true;
}
void SSGameCamera::Update()
{
	// 
	 CVector3 target = m_ssplayer->GetPosition();
	target.y = 0;
	target.y += 235.0f;	//注視点はプレイヤーのちょっと上にする。

						//続いて視点を計算する。
	CVector3 position = target;
	//視点は注視点からy方向に+100、Z方向に-500にする。
	//position.y += 300.0f;
	position.z -= 200.0f;
	//メインカメラに注視点と視点を設定して更新する。
	MainCamera().SetTarget(target);
	MainCamera().SetPosition(position);
	MainCamera().Update();
}