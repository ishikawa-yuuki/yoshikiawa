#include "stdafx.h"
#include "Human.h"
#include "Player.h"
#include "Game.h"
#include "GameOver.h"
#include "MoveBed.h"

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
	//m_position.y = 150;
	//m_skinModelRender->SetPosition(m_position);
	return true;
}

void Human::Update()
{
	//Playerである光の信号を受け取ったら
	//行動を変える関数を考えています、、、<-move()に書いてます。

	Move();
	Turn();
	AnimeControll();
	Hanntei();
	isDead();
}

void Human::Move()
{
	const int light_Yellow = 0;
	const int light_Red = 1;
	if (m_player->GetColor() == light_Yellow) {
		if (!m_isDead) {
			CVector3 diff = m_position - m_player->GetPosition();
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
					diff.Normalize();
					diff*=-40.0f;//-だと近づく+なら遠のく
					m_movespeed = diff;
					m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
				}
				else {//playerと離れすぎず近すぎないときの処理
					m_movespeed = m_movespeed * humanspeed;// *GameTime().GetFrameDeltaTime();
				}
			}
		}
	}
	else if (m_player->GetColor() == light_Red) {//赤色になった時の処理、とりあえず止まってる
		m_movespeed = CVector3::Zero;
	}
	m_movespeed.y -= 50.0f*GameTime().GetFrameDeltaTime();
	CVector3 pos = m_movespeed + m_Bedspeed;
	m_position = m_charaCon.Execute(pos, GameTime().GetFrameDeltaTime());
	m_charaCon.SetPosition(m_position);
	m_skinModelRender->SetPosition(m_charaCon.GetPosition());
}

void Human::Turn()
{
	if (!m_isDead) {
		if (fabsf(m_movespeed.x) <= 0.001f    //fabsfは絶対値。m_movespeed.x&m_movespeedzが
			&&fabsf(m_movespeed.z <= 0.001f)) {//0.001以下の時には何もしない。
			return;
		}
		else {
			float angle = atan2(m_movespeed.x, m_movespeed.z);
			m_qrot.SetRotation(CVector3::AxisY, angle);
		}
		m_skinModelRender->SetRotation(m_qrot);
	}
}

void Human::AnimeControll()//アニメーションを管理する関数、プレイヤーのスピードで変わる。
{
	if (!m_isDead) {
		const float run_true = 5.5f*5.5f;
		const float walk_true = 0.45f*0.45f;
		if (m_movespeed.LengthSq() > run_true) {
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
		if (!m_isDead) {
			if (Pad(0).IsTrigger(enButtonB)) {
				m_isDead = true; //これがtrueになれば死
				m_game->GetDamage();//gameクラスにダメージ中であることを知らせている。死んでるけど・・・
				m_skinModelRender->PlayAnimation(enAnimationClip_KneelDown, 0.2f);
				m_movespeed = CVector3::Zero;
			}
		}
		else {
			//死亡時のアニメーションが終わったらGameOverクラスへ
			if (m_skinModelRender->IsPlayingAnimation() == false
				&& m_isGameOver != true) {
				m_isGameOver = true;
				//m_skinModelRender->PlayAnimation(enAnimationClip_clear, 0.2f);
				NewGO<GameOver>(0);
			}
		}
	}
}
void Human::Hanntei()
{
	 m_Bedspeed = CVector3::Zero;
		QueryGOs<MoveBed>("MoveBed", [&](MoveBed* move) {
			CPhysicsGhostObject* ghostObj = move->GetGhost();
			PhysicsWorld().ContactTest(m_charaCon, [&](const btCollisionObject& contactObject) {
				if (ghostObj->IsSelf(contactObject) == true) {
					//このフレームのボックスの移動量を計算
					CVector3 boxMoveValue;
					boxMoveValue = move->GetPosition() - move->GetLastPos();
					//ボックスの移動速度を求める
					CVector3 boxMoveSpeed;
					boxMoveSpeed = boxMoveValue / GameTime().GetFrameDeltaTime();
					m_Bedspeed += boxMoveSpeed;
				}
			});
			return true;
		});
}