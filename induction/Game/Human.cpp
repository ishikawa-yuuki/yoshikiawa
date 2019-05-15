#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "MistEnemy.h"
#include "Game.h"
#include "GameOver.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Poison.h"
#include "Stone.h"
#include "Fade.h"
#include "Exit.h"
#include "Light_Object.h"
#include "Stage_Select.h"
#include "Title.h"
#include "TitleGround.h"
#include  "GameData.h"
//ライトの強さを計算する。
float CalcLightPower(CVector3 charaPos, CVector3 lightPos, CVector4 attn)
{
	float len = (charaPos - lightPos).Length();
	float lightRate = len / attn.x;
	float lightPower = std::max<float>(1.0 - lightRate * lightRate, 0.0f);
	return pow(lightPower, attn.y);
}
Human::Human()
{
}


Human::~Human()
{
	DeleteGO(m_skinModelRender);
	if (m_title == nullptr) {
		DeleteGO(m_nearPointLight);
	}
}

bool Human::Start()
{

	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	m_fade = FindGO<Fade>("Fade");
	
	m_mistenemy = FindGO<MistEnemy>("mist");
	m_exit = FindGO<Exit>("Exit");
	m_title = FindGO<Title>("Title");
	if (m_title == nullptr) {
		m_animClip[enAnimationClip_idle].Load(L"animData/Human/idle.tka");
		//m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
		m_animClip[enAnimationClip_run].Load(L"animData/Human/run.tka");
		//m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
		//m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
		m_animClip[enAnimationClip_KneelDown].Load(L"animData/Human/KneelDown.tka");
		m_animClip[enAnimationClip_clear].Load(L"animData/Human/clear.tka");
		//アニメクリップをすべてロード、全部使う必要は特にないです。


		for (int i = 0; i < enAnimationClip_num; i++) {
			m_animClip[i].SetLoopFlag(true);
		}
		//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

		//m_animClip[enAnimationClip_jump].SetLoopFlag(false);
		m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
		//m_animClip[enAnimationClip_damage].SetLoopFlag(false);
		m_animClip[enAnimationClip_clear].SetLoopFlag(false);
		//trueにしたら問題がある奴だけfalseに直した。

		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/Human/Human.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
		m_charaCon.Init(
			20.0f,
			30.0f,
			m_position
		);
	}
	else {
		m_animClip[enAnimationClip_idle].Load(L"animData/Human/idle.tka");
		//m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
		m_animClip[enAnimationClip_run].Load(L"animData/Human/run.tka");
		//m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
		//m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
		m_animClip[enAnimationClip_KneelDown].Load(L"animData/Human/KneelDown.tka");
		m_animClip[enAnimationClip_clear].Load(L"animData/Human/clear.tka");
		//アニメクリップをすべてロード、全部使う必要は特にないです。


		for (int i = 0; i < enAnimationClip_num; i++) {
			m_animClip[i].SetLoopFlag(true);
		}
		//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

		//m_animClip[enAnimationClip_jump].SetLoopFlag(false);
		m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
		//m_animClip[enAnimationClip_damage].SetLoopFlag(false);
		m_animClip[enAnimationClip_clear].SetLoopFlag(false);
		//trueにしたら問題がある奴だけfalseに直した。

		m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender->Init(L"modelData/TitleGround/humant.cmo", m_animClip, enAnimationClip_num, enFbxUpAxisZ);
		//m_skinModelRender->Init(L"modelData/TitleGround/human_title.cmo");
		m_charaCon.Init(
			20.0f,
			30.0f,
			m_position
		);
		m_titleground = FindGO<TitleGround>("TitleGround");
	}
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetEmissionColor({3.3f, 3.3f, 3.3f});
	m_skinModelRender->SetPosition(m_position);
	
	return true;
}

void Human::Update()
{
	if (m_title != nullptr) {
		if (m_title->isStop()) {
			m_degree -= m_titleground->GetCutSpeed() * m_speed * GameTime().GetFrameDeltaTime();
			CQuaternion rot;
			rot.SetRotationDeg(CVector3::AxisX, m_degree);
			m_skinModelRender->SetRotation(rot);
		}
		//m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
		return;
	}
	AnimeControll();
	//if (m_player->GetStartMove() == true) {
		if (!m_StartMoveFin) {
			GameStartMove();
		}
		else if (m_mistenemy->Getstate() == 2)
		{
			TakingMove();
		}
		else
		{
				/*QueryGOs<Light_Object>("LightObject", [&](Light_Object* light) {*/
					//light->GetlightOn() == true;
				//ランタンの数分、GetLightOn()関数を調べて、
				//その中にGetLightOnがtrueになっているランタンがあればm_nearlightに代入。
				Light_Move();
		}
		Turn();
		Hanntei();
		CVector3 Pos = m_position + m_Bedspeed;
		isDead();
		isClear();
		m_charaCon.SetPosition(Pos);
		m_skinModelRender->SetPosition(Pos);
	//}
}

void Human::GameStartMove()
{
	CVector3 diff;
	diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (diff.LengthSq() <105.0f * 105.0f) {
		m_movespeed = CVector3::Zero;
		m_StartMoveFin = true;
	}
	else {
		m_movespeed.z = -400.0f;
		//m_position += m_movespeed;
	}

	if (m_charaCon.IsOnGround()) {
		m_movespeed.y = 0.0f;
	}
	else {
		m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
	}

	m_position = m_charaCon.Execute(m_movespeed, GameTime().GetFrameDeltaTime());
}

void Human::Move()
{
	/*const int light_Yellow = 0;
	const int light_Red = 1;
	if (!m_Clear_one) {
		if (m_player->GetColor() == light_Yellow) {
			//死なない時の普通の処理
			if (!m_isDead) {
				CVector3 diff = m_position - m_player->GetPosition();
				//Yの数値は除外
				diff.y = 0.0f;
				if (diff.LengthSq() <= 105.0f * 105.0f) {//プレイヤーと近ければhumanは止まる
					m_movespeed = CVector3::Zero;
				}
				else {
					auto humanspeed = 30.0f;
					m_movespeed = m_player->GetPosition() - m_position;
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();

					m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0f;
					if (diff.LengthSq() >= 800.0f*800.0f) {//プレイヤーと離れすぎたときにだせるmovespeedの最高速
						diff.y = 0.0f;
						diff.Normalize();
						diff *= -30.0f;//-だと近づく+なら遠のく
						m_movespeed = diff;
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
					else {//playerと離れすぎず近すぎないときの処理
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
				}
			}
			else
			{
				//死んだときの処理
				m_movespeed = CVector3::Zero;
			}
		}
		else if (m_player->GetColor() == light_Red) {//赤色になった時の処理、とりあえず止まってる
			m_movespeed = CVector3::Zero;
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}

		if (m_charaCon.IsOnGround()) {
			m_movespeed.y = 0.0f;
		}
		else {
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}
	}
	//動く床と自分のスピードを足す。
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());*/
}

void Human::TakingMove()
{
	if (!m_Clear_one) {
			//死なない時の普通の処理
			if (!m_isDead) {
				CVector3 diff = m_position - m_mistenemy->GetPosition();
				CVector3 diff_p = m_position - m_player->GetPosition();
				//Yの数値は除外
				diff.y = 0.0f;
				diff_p.y = 0.0f;
				if (diff.LengthSq() <= 105.0f * 105.0f) {//プレイヤーと近ければhumanは止まる
					m_movespeed = CVector3::Zero;
				}
				else {
					auto humanspeed = 30.0f;
					m_movespeed = m_mistenemy->GetPosition() - m_position;
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();

					m_movespeed *= diff.LengthSq() / (400.0f * 400.0f) * 12.0f;
					if (diff.LengthSq() >= 800.0f*800.0f) {//プレイヤーと離れすぎたときにだせるmovespeedの最高速
						diff.y = 0.0f;
						diff.Normalize();
						diff *= -10.0f;//-だと近づく+なら遠のく
						m_movespeed = diff;
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
					else {//playerと離れすぎず近すぎないときの処理
						m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
					}
				}
			}
			else
			{
				//死んだときの処理
				m_movespeed = CVector3::Zero;
			}
		}
		if (m_charaCon.IsOnGround()) {
			m_movespeed.y = 0.0f;
		}
		else {
			m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
		}
	//動く床と自分のスピードを足す。
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
}

void Human::Light_Move()
{
	if (!m_Clear_one) {
		//死なない時の普通の処理
		if (!m_isDead) {
			
			m_nearLen = 100000.0f;
			//int nearLightNo = -1;
			m_nearPointLight = nullptr;
			/*Game* game = FindGO<Game>("Game");*/
			const auto& lightList = m_game->GetLightObjectList();
			float ligPowerMax = 0.0f;
			//一番光の強さが強いライトをランタンから調べる。
			for (int i = 0; i < lightList.size(); i++) {
				if (lightList[i]->GetLightOn()) {
					float ligPower = CalcLightPower(
						m_position, 
						lightList[i]->GetPosition(), 
						lightList[i]->GetPointLightAttn()
					);

					//どのランタンの光が一番影響を与えているか調べる。
					if (ligPowerMax < ligPower) {
						ligPowerMax = ligPower;	
						m_nearPointLight = lightList[i]->GetPointLight();
					}
				}
			}
			//次は星
			float ligPower = CalcLightPower(m_position, m_player->GetPosition(), m_player->GetPointLightAttn());
			if (ligPower > ligPowerMax) {
				m_nearPointLight = m_player->GetPointLight();
			}
			//光が届いているライトがあったら、そこについていく。
			if (m_nearPointLight != nullptr) {
				if (mistflag) {
					mistflag = false;
				}
				auto humanspeed = 300.0f;
				m_movespeed = m_nearPointLight->GetPosition() - m_position;
				auto len = m_movespeed.Length();
				if (len > 200.0f) {
					m_movespeed.y = 0.0f;
					m_movespeed.Normalize();
					m_movespeed = m_movespeed * humanspeed;
				}
				else {
					m_movespeed = CVector3::Zero;
				}
			}
			else {
				m_movespeed = CVector3::Zero;
				//ミストエネミーを呼ぶもの
				if (!mistflag) {
					m_enemytimer--;
				}
				if (m_enemytimer < 0) {
					mistflag = true;
					m_enemytimer = Random().GetRandInt() % 500 + 200;
				}
			}
		}
		else
		{
			//死んだときの処理
			m_movespeed = CVector3::Zero;
		}
	}
	if (m_charaCon.IsOnGround()) {
		m_movespeed.y = 0.0f;
	}
	else {
		m_movespeed.y -= 10000.0f*GameTime().GetFrameDeltaTime();
	}
	//動く床と自分のスピードを足す。
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
}

void Human::Turn()
{
	if (!m_isDead) {
		if (fabsf(m_movespeed.x) <= 0.001f    //fabsfは絶対値。m_movespeed.x&m_movespeedzが
			&&fabsf(m_movespeed.z)<= 0.001f) {//0.001以下の時には何もしない。
			return;
		}
		else {
			float angle = atan2(m_movespeed.x, m_movespeed.z);
			m_qrot.SetRotation(CVector3::AxisY, angle);
		}
		m_skinModelRender->SetRotation(m_qrot);
	}
}
void Human::Range()
{
	const float range = 800.0f * 800.0f;
	CVector3 diff = m_position - m_player->GetPosition();
	if (diff.LengthSq() < range) {
		m_volume = 0.5f;
	}
	else if (diff.LengthSq() < range * 1.5) {
		m_volume = 0.3f;
	}
	else if (diff.LengthSq() < range * 3) {
		m_volume = 0.15f;
	}
}
//アニメーションを管理する関数、プレイヤーのスピードで変わる。
//クリアとゲームオーバーの時は機能しない。
void Human::AnimeControll()
{
	m_kari += GameTime().GetFrameDeltaTime();
	//prefab::CSoundSource* ss;
	if (!m_isDead) {
		if (!m_Clear_one) {
			const float run_true = 100.0f*100.0f;
			const float walk_true = 10.0f*10.0f;
			//	m_movespeed.y = 0.0f;
			if (m_position.y <= -200.0f) {
				m_isDead = true;
			}
			else if (m_movespeed.LengthSq() > run_true) {
				m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2);
				if (m_kari >= 0.4) {
					prefab::CSoundSource*ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/run.wav");
					Range();
					ss->SetVolume(m_volume);
					ss->Play(false);
					m_kari = 0;
				}
				
			}
		/*	else if (m_movespeed.LengthSq() > walk_true) {
				m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2);
				if (m_kari >= 0.5) {
					prefab::CSoundSource*ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/walk.wav");
					ss->SetVolume(0.5f);
					ss->Play(false);
					m_kari = 0.0f;
				}*/
			//}
			else {
				m_skinModelRender->PlayAnimation(enAnimationClip_idle, 0.2);
			}
		}
	}
}

//void Human::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
//{
//	m_font.Begin(renderContext);
//	wchar_t MoveSPeeed[100];
//	swprintf(MoveSPeeed, L"x%f,y%f,z%f", m_movespeed.x, m_movespeed.y, m_movespeed.z);
//	m_font.Draw(MoveSPeeed, { 0,0 });
//	m_font.End(renderContext);
//}

void Human::isDead()
{
	if (!m_game->GetifPose()) {//!= true修正
		//敵もギミックもないので今のところはボタン押すだけで死ぬスペランカーです。
		if (!m_Clear_one) {//クリア状態でないなら下へ
			if (!m_siboustop) {
				if (Pad(0).IsTrigger(enButtonB)
					|| m_isDead) {
					//叫び声
					prefab::CSoundSource* sound = nullptr;
					sound = NewGO<prefab::CSoundSource>(0);
					sound->Init(L"sound/woman.wav");
					sound->SetVolume(0.05f);
					sound->Play(false);
					m_siboustop = true;
					m_isDead = true; //これがtrueになれば死
					m_game->GetDamage();//gameクラスにダメージ中であることを知らせている。死んでるけど・・・
					m_skinModelRender->PlayAnimation(enAnimationClip_KneelDown, 0.2f);
				}
			}
			else {
				//死亡時のアニメーションが終わったらGameOverクラスへ
				if (!m_skinModelRender->IsPlayingAnimation() //== false
					&& !m_isGameOver //!= true
					) {
					//ここで暗転
					m_isGameOver = true;
				}
			}
		}
	}
}
//動くオブジェクトの判定
void Human::Hanntei()
{
	 m_Bedspeed = CVector3::Zero;
		QueryGOs<MoveBed>("MoveBed1", [&](MoveBed* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) ) {//== true
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = move->GetPosition() - move->GetLastPos();
					//ボックスの移動速度を求める
					//CVector3 boxMoveSpeed;
					//boxMoveSpeed = boxMoveValue;
						// GameTime().GetFrameDeltaTime();
					m_Bedspeed += boxMoveValue; //boxMoveSpeed;
				}
			});
			return true;
		});

		QueryGOs<MoveBed_zengo>("MoveBed2", [&](MoveBed_zengo* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) ) {//== true
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = move->GetPosition() - move->GetLastPos();
					//ボックスの移動速度を求める
					//CVector3 boxMoveSpeed;
					//boxMoveSpeed = boxMoveValue;
					// GameTime().GetFrameDeltaTime();
					m_Bedspeed += boxMoveValue;//boxMoveSpeed;
				}
			});
			return true;
		});
		QueryGOs<Poison>("Poison", [&](Poison* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject)) {//== true
					isKill();
				}
			});
			return true;
		});
		QueryGOs<Stone>("Stone", [&](Stone * move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject & contactObject) {
				if (ghostObj->IsSelf(contactObject)) {//== true
					isKill();
				}
			});
			return true;
		});
}
//クリアしたかどうか。
void Human::isClear()
{
	//m_lightObjectは中間ポイントになったので、ゴールのためのオブジェにはなりません。
	//代わりに違うやつ使いまひょ。
	CVector3 diff = m_position - m_exit->GetPosition();
	diff.y = 0.0f;
	if (!m_skinModelRender->IsPlayingAnimation()  && m_Clear_one) {
		m_skinModelRender->PlayAnimation(enAnimationClip_run, 0.2f);
		m_movespeed.z -= 6000.0f * GameTime().GetFrameDeltaTime();
	}
	else {
		if (diff.LengthSq() < 70.0f*70.0f
			&& !m_Clear_one) {
			m_skinModelRender->PlayAnimation(enAnimationClip_clear, 0.2f);
			m_Clear_one = true;
			m_movespeed = CVector3::Zero;
			GameData::GetInstance().SetStageClear();
		}
	}
	if (m_Clear_one) {
		m_timer += 1 * GameTime().GetFrameDeltaTime();
		//m_timerfragつける。
		if (m_timer >= 6.0f) {
			m_timer = 0.0f;
			m_game->GameOwari();
			NewGO<Stage_Select>(0,"Stage_Select");
		}
		else if (m_timer >= 3.0f) {
			m_fade->StartFadeOut();
		}
	}
}

void Human::lanpos(CVector3 pos)
{
	CVector3 diff = pos - m_position;

	if (diff.LengthSq() <= 105.0f * 105.0f) {//プレイヤーと近ければhumanは止まる
		m_movespeed = CVector3::Zero;
	}
	else {
		auto humanspeed = 300.0f;
		m_movespeed = diff;
		m_movespeed.y = 0.0f;
		m_movespeed.Normalize();
		m_movespeed = m_movespeed * humanspeed;
	}
	CVector3 tpos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(tpos, GameTime().GetFrameDeltaTime());
}