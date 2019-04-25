#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Human.h"
#include "StarDust.h"
#include "tkEngine/light/tkPointLight.h"
Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_effect);
	DeleteGO(m_ptLight);
	DeleteGO(m_stardust);
	DeleteGO(m_skin);
}

bool Player::Start()
{
	m_human = FindGO<Human>("Human");
	//m_stardust = NewGO<StarDust>(0,"StarDust");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/siro.cmo");
	m_skin->SetEmissionColor({50.0f, 50.0f, 20.0f});
	m_effect = NewGO<prefab::CEffect>(0);
	/*m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });*/
	m_position.y = 50.0f;
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position//0,100,0
	);
	//いらないと思う
	//m_charaCon.Execute(m_position);
	//m_charaCon.SetPosition(m_position);
	//m_effect->SetPosition(m_position);
	m_ptLight = NewGO<prefab::CPointLight>(0);
	m_ptLight->SetColor({ 1000.0f, 1000.0f, 1000.0f });//1000,1000,1000でLEDみたいな光が出る
	CVector3 attn;
	attn.x = 1000.0f;
	attn.y = 10.0f;
	m_ptLight->SetAttn(attn);
	
	
	
	return true;
}

void Player::Update()
{
	//プレイヤーの光の色を変えてHumanに簡単な指示を出せるような
	//そんなプログラムを考えてます、、、、
	Color_Change();
	if (m_StartMoveFin) {
		if (m_human->GetStartMove()) {//== true
			Move();
		}
	}
	else {
		GameStartMove();
	}
	//Move();
	//m_effect->SetPosition(m_position);
	m_skin->SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
	m_ptLight->SetPosition(m_position);
	
	//static CVector3 attn = { 1000.0f , 10.0f, 1.0f};
	//m_ptLight->SetAttn(attn);
}

void Player::GameStartMove()
{
	m_moveSpeed.z = -500.0f;
	if (m_position.z <= -500.0f) {
		m_moveSpeed = CVector3::Zero;
		m_StartMoveFin = true;
	}
	//いらないと思う
	//m_position += m_moveSpeed;
	m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
}

void Player::Move()
{
	if (!m_human->GetisDead()) {// == false
		if (!m_human->GetisClear() ) {//== false
			//光の速度
			const float pl_speed = 600.0f;
			float L_Stick_X = Pad(0).GetLStickXF();
			float L_Stick_Y = Pad(0).GetLStickYF();

			//カメラの前方向の取得
			CVector3 CameraForword = MainCamera().GetForward();
			//カメラの横方向の取得
			CVector3 CameraRight = MainCamera().GetRight();

			CameraForword.y = 0.0f;
			//方向情報・前
			CameraForword.Normalize();
			CameraRight.y = 0.0f;
			//方向情報・横
			CameraRight.Normalize();
			m_moveSpeed = CVector3::Zero;
			m_moveSpeed += CameraForword * L_Stick_Y * pl_speed;
			m_moveSpeed += CameraRight * L_Stick_X * pl_speed;
			m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
		}
	}
}

void Player::Color_Change()
{
	//停止ではなくブラックホールモードになりました。使用はまだ変わってませんが…
	if (Pad(0).IsTrigger(enButtonUp)) {
		switch (m_color) {
		case hikari_hutu:
			m_color = hikari_black;
			/*m_effect = NewGO<prefab::CEffect>(0);*/
			//m_effect->Release();
			m_effect->Play(L"effect/blackhole.efk");
			m_effect->SetScale({ 30.0f,30.0f,30.0f });
			CVector3 attn;
			attn.x = 100.0f;
			attn.y = 10.0f;
			attn.z = 1.0f;
			m_ptLight->SetAttn(attn);
			/*m_effect->SetPosition(m_position);*/
		}
	}
	else if (Pad(0).IsTrigger(enButtonDown)) {
		switch (m_color){
		case hikari_black:
			m_color = hikari_hutu;
			/*m_effect->Release();
			m_effect->Play(L"effect/hikari.efk");
			m_effect->SetScale({ 30.0f,30.0f,30.0f });*/
			CVector3 attn;
			attn.x = 1000.0f;
			attn.y = 10.0f;
			attn.z = 1.0f;
			m_ptLight->SetAttn(attn);
		}
	}
}