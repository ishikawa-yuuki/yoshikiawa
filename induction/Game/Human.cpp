#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "MistEnemy.h"
#include "Game.h"
#include "GameOver.h"
#include "MoveBed.h"
#include "MoveBed_zengo.h"
#include "Poison.h"
#include "Fade.h"
#include "Exit.h"
#include "Light_Object.h"
#include "Light_Object2.h"
#include "Stage_Select.h"

Human::Human()
{
}


Human::~Human()
{
	DeleteGO(m_skinModelRender);
}

bool Human::Start()
{
	
	m_player = FindGO<Player>("Player");
	m_game = FindGO<Game>("Game");
	m_fade = FindGO<Fade>("Fade");
	m_lightObject = FindGO<Light_Object>("LightObject");
	m_lightObject2 = FindGO<Light_Object2>("LightObject2");
	m_mistenemy = FindGO<MistEnemy>("mist");
	m_exit = FindGO<Exit>("Exit");

	m_animClip[enAnimationClip_idle].Load(L"animData/unityChan/idle.tka");
	m_animClip[enAnimationClip_walk].Load(L"animData/unityChan/walk.tka");
	m_animClip[enAnimationClip_run].Load(L"animData/unityChan/run.tka");
	m_animClip[enAnimationClip_jump].Load(L"animData/unityChan/jump.tka");
	m_animClip[enAnimationClip_damage].Load(L"animData/unityChan/damage.tka");
	m_animClip[enAnimationClip_KneelDown].Load(L"animData/unityChan/KneelDown.tka");
	m_animClip[enAnimationClip_clear].Load(L"animData/unityChan/clear.tka");
	//アニメクリップをすべてロード、全部使う必要は特にないです。


	for (int i = 0; i < enAnimationClip_num; i++) {
		m_animClip[i].SetLoopFlag(true);
	}
	//for文でとりあえずロードした奴らすべてLoopFlagをtrueにした。

	m_animClip[enAnimationClip_jump].SetLoopFlag(false);
	m_animClip[enAnimationClip_KneelDown].SetLoopFlag(false);
	m_animClip[enAnimationClip_damage].SetLoopFlag(false);
	m_animClip[enAnimationClip_clear].SetLoopFlag(false);
	//trueにしたら問題がある奴だけfalseに直した。
	
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo",m_animClip,enAnimationClip_num,enFbxUpAxisY);
	m_charaCon.Init(
		20.0f,
		30.0f,
		m_position
	);
	m_skinModelRender->SetShadowCasterFlag(true);
	//m_position.y = 150;
	//m_skinModelRender->SetPosition(m_position);
	return true;
}

void Human::Update()
{
	//Playerである光の信号を受け取ったら
	//行動を変える関数を考えています、、、<-move()に書いてます。
	AnimeControll();
	if (m_player->GetStartMove() == true) {
		if (!m_StartMoveFin) {
			GameStartMove();
		}
		else {
			/*QueryGOs<Light_Object>("LightObject", [&](Light_Object* light) {*/
				//light->GetlightOn() == true;
				if (m_lightObject->GetLightOn()) {
					//m_lightObject = light;
					lanpos(m_lightObject->GetPosition());
					/*return false;*/
				}
				else if (m_lightObject2->GetLightOn()) {
					lanpos(m_lightObject2->GetPosition());
				}
				else if (m_mistenemy->Getstate() == 2) {
					TakingMove();
					/*return false;*/
				}
				else {
					Move();
					/*return false;*/
				}
				/*return true;*/
			/*});*/
		}
	}
	//Move();
	Turn();
	Hanntei();
	CVector3 Pos = m_position + m_Bedspeed;
	isDead();
	isClear();
	m_charaCon.SetPosition(Pos);
	m_skinModelRender->SetPosition(Pos);
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
	const int light_Yellow = 0;
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
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
}

void Human::TakingMove()
{
	if (!m_Clear_one) {
			//死なない時の普通の処理
			if (!m_isDead) {
				CVector3 diff = m_position - m_mistenemy->GetPosition();
				//Yの数値は除外
				diff.y = 0.0f;
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
			CVector3 diff = m_position - m_lightObject->GetPosition();
			CVector3 diff2 = m_position - m_lightObject->GetPosition();

			//どのランタンが一番近いか選手権。
			if (diff.LengthSq() > diff2.LengthSq())
			{
				diff = diff2;
			}
			if (diff.Length() < m_nearLen) {
				m_nearLen = diff.Length();
				m_nearLight = m_lightObject;
			}
			//Yの数値は除外
			//diff.y = 0.0f;
			if (diff.LengthSq() <= 105.0f * 105.0f) {//プレイヤーと近ければhumanは止まる
				m_movespeed = CVector3::Zero;
			}
			else {
				auto humanspeed = 300.0f;
				m_movespeed = m_nearLight->GetPosition() - m_position;
				m_movespeed.y = 0.0f;
				m_movespeed.Normalize();
				m_movespeed = m_movespeed * humanspeed;
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
//アニメーションを管理する関数、プレイヤーのスピードで変わる。
//クリアとゲームオーバーの時は機能しない。
void Human::AnimeControll()
{
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
			}
			else if (m_movespeed.LengthSq() > walk_true) {
				m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.2);
			}
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
					m_fade->StartFadeOut();

				}
			}
		}
	}
	if (!m_fade->IsFade()) {
		if (m_isGameOver) {
			if (!m_gameover_one) {
				NewGO<GameOver>(0);
				m_gameover_one = true;
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