#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"
#include "Human.h"
#include "StarDust.h"
#include "Game.h"
#include "tkEngine/light/tkPointLight.h"
#include "Title.h"
#include "TitleGround.h"
Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_effect);
	DeleteGO(m_ptLight);
	//DeleteGO(m_stardust);
	DeleteGO(m_skin);
	DeleteGO(m_sound);
}

bool Player::Start()
{
	m_title = FindGO<Title>("Title");
	m_human = FindGO<Human>("Human");
	m_game = FindGO<Game>("Game");
	//m_stardust = NewGO<StarDust>(0,"StarDust");
	m_skin = NewGO<prefab::CSkinModelRender>(0);
	m_skin->Init(L"modelData/siro.cmo");
	m_skin->SetEmissionColor({50.0f, 50.0f, 20.0f});
	m_skin->SetScale(CVector3::One * 1.0f);
	m_effect = NewGO<prefab::CEffect>(0);
	m_effect->Play(L"effect/blackhole.efk");
	/*m_effect->Play(L"effect/hikari.efk");
	m_effect->SetScale({ 30.0f,30.0f,30.0f });*/

	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position//0,100,0
	);
	//いらないと思う
	//m_charaCon.Execute(m_position);
	//m_charaCon.SetPosition(m_position);
	m_effect->SetPosition(m_position);
	m_ptLight = NewGO<prefab::CPointLight>(0);
	m_ptLight->SetColor({ 1000.0f, 1000.0f, 1000.0f });//1000,1000,1000でLEDみたいな光が出る
	
	m_ptLight->SetAttn(m_pointLigDefaultAttn);
	
	

	m_titleground = FindGO<TitleGround>("TitleGround");
	m_skin->SetShadowCasterFlag(true);
	if (m_title == nullptr) {
		m_position.y = 50.0f;
	}
	else {
		m_skin->SetEmissionColor({ 2.3f, 2.3f, 0.0f });
		m_ptLight->SetColor({ 10.0f, 10.0f, 10.0f });
	}
	return true;
}

void Player::Update()
{
	if (m_title != nullptr) {
		if (m_title->isStop()) {
			m_degree -= m_titleground->GetCutSpeed() * m_human->m_speed * GameTime().GetFrameDeltaTime();
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisX, -m_titleground->GetCutSpeed() * m_human->m_speed * GameTime().GetFrameDeltaTime());
			rot.Multiply(m_position);
		}
		else {
		/*	m_position = m_title->GetCameraTarget();
			m_position.z -= 70.0f;
			m_position.y += 150.0f;*/
			//m_skin->SetScale(CVector3::One * 0);
		}
		//CVector3 pos = m_title->GetPlayerPosition();
		m_effect->SetPosition(m_position);
		m_skin->SetPosition(m_position);
		m_ptLight->SetPosition(m_position);
		return;
	}
	//プレイヤーの光の色を変えてHumanに簡単な指示を出せるような
	//そんなプログラムを考えてます、、、、
	Color_Change();

	if (m_color == hikari_explosion) {
		if (m_explosionTimer == 0.0f) {
			
			//sound->SetVolume();
		}
		const float explosionTime = 2.0f;
		m_explosionTimer += GameTime().GetFrameDeltaTime();
		m_ahureru -= 3.0f;
		CVector3 endAttn = { 1000.0f + m_ahureru, 10.0f, 1.0f };
		if (m_explosionTimer > explosionTime) {
			//爆発終わり。
			prefab::CSoundSource* sound = nullptr;
			sound = NewGO<prefab::CSoundSource>(0);
			sound->Init(L"sound/BlackHoleStart.wav");
			sound->SetVolume(5.0f);
			sound->Play(false);
			endAttn = { 1000.0f + m_ahureru, 10.0f, 1.0f };
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Release();
			m_effect->Play(L"effect/blackhole_otamesi.efk");
			m_effect->SetScale({ 100.0f,100.0f,100.0f });
			m_skin->SetEmissionColor({ 0.5f, 0.5f, 0.2f });
			m_explosionTimer = explosionTime;
			m_color = hikari_black;
			m_ahureru = 0.0f;
		}
		float t = 1.0f - (m_explosionTimer / explosionTime);
		m_attn.Lerp(pow(t, 10.0f), endAttn, m_pointLigDefaultAttn);
		m_ptLight->SetAttn(m_attn);
	}
	else {
		if (m_color == hikari_black) {
			
			
			if(m_attn.x < 100.0f){
				m_attn.x = 100.0f;
			}
			else {
				m_attn.x -= 80.0f;
			}
		}
		if (m_StartMoveFin) {
			if (m_human->GetStartMove()) {//== true
				Move();
			}
		}
		else {
			GameStartMove();
		}
	}
	//Move();
	m_effect->SetPosition(m_position);
	m_skin->SetPosition(m_position);
	m_charaCon.SetPosition(m_position);
	m_ptLight->SetPosition(m_position);
	
	//static CVector3 attn = { 1000.0f , 10.0f, 1.0f};
	m_ptLight->SetAttn(m_attn);
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
		if (!m_human->GetisClear()) {//== false
			if (!m_game->GetisPose()) {
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
			else {
				m_moveSpeed = CVector3::Zero;
				m_position = m_charaCon.Execute(m_moveSpeed, GameTime().GetFrameDeltaTime());
			}
		}
	}
}

void Player::Color_Change()
{
	
	//停止ではなくブラックホールモードになりました。使用はまだ変わってませんが…
	if (!m_game->GetisPose()) {
		if (m_game->isButton()) {
			m_game->SetisButton();
		}
		else {
			if (Pad(0).IsTrigger(enButtonA)) {
				switch (m_color) {
				case hikari_hutu:
					m_explosionTimer = 0.0f;
					m_color = hikari_explosion;
					m_sound = NewGO<prefab::CSoundSource>(0);
					m_sound->Init(L"sound/BlackHoleUpdate.wav");
					m_sound->SetVolume(5.0);
					m_sound->Play(true);
					break;
				case hikari_black:
					m_color = hikari_hutu;
					m_effect->Release();
					m_effect->Play(L"effect/hikari.efk");
					m_effect->SetScale({ 0.0f,0.0f,0.0f });
					m_skin->SetEmissionColor({ 50.0f, 50.0f, 20.0f });
					m_attn = m_pointLigDefaultAttn;
					m_ptLight->SetAttn(m_attn);
					m_sound->Release();
					break;
				}
#if 0
				///*m_effect = NewGO<prefab::CEffect>(0);*/
				//m_effect->Release();
				//m_effect->Play(L"effect/blackhole.efk");
				//m_effect->SetScale({ 100.0f,100.0f,100.0f });
				//m_skin->SetEmissionColor({ 0.5f, 0.5f, 0.2f });
				//CVector3 attn;
				//attn.x = 100.0f;
				//attn.y = 10.0f;
				//attn.z = 1.0f;
				//m_ptLight->SetAttn(attn);
				///*m_effect->SetPosition(m_position);*/
		case hikari_explosion:
#endif


			}
		}
	}
}