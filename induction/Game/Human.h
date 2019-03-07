#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
class Fade;
class Light_Object;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//ゲーム最初に行う関数。
	void GameStartMove();
	//ゲーム中の普通の動きをするときの関数
	void Move();
	void Turn();
	//プレイヤーのアニメの変更
	void AnimeControll();
	//やったか！を判定する
	void isDead();
	//動く床の判定
	void Hanntei();
	//クリアかどうか
	void isClear();

	/*void PostRender(CRenderContext& rc);*/

	//現在のポジションの値を返す関数。
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	//ゲーム初動が終わったかの関数。
	bool GetStartMove()const
	{
		return m_StartMoveFin;
	}

	//死んだかどうかを返す関数
	bool GetisDead()const 
	{
		return m_isDead;
	}
	//クリアしたかどうかを返す関数
	bool GetisClear()const
	{
		return m_Clear_one;
	}
	//ゲームオーバーかどうか返す関数
	bool GetisGameOver()const {
		return m_isGameOver;
	}
	//humanを倒すときの関数、enemyとかが使うと思います。
	void isKill() 
	{
		if (!m_isDead) {
			m_isDead = true;
		}
	}
private:
	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player;
	Game* m_game;
	Fade* m_fade;
	Light_Object* m_lightObject;
	CVector3 m_position = { 0.0f,0.0f,700.0f };
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_Bedspeed = CVector3::Zero;
	CQuaternion m_qrot = CQuaternion::Identity;
	CCharacterController m_charaCon;
	enum HumanAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_clear,
		enAnimationClip_KneelDown,
		enAnimationClip_num
	};
	//アニメーションクリップ詰め合わせ
	CAnimationClip m_animClip[enAnimationClip_num];
	//調べるためのフォント、何かに使うかも
	CFont m_font;
	//初動が終わったかを返す。
	bool m_StartMoveFin = false;
	//死んだかどうか
	bool m_isDead = false;
	//ゲームオーバーかどうか
	bool m_isGameOver = false;
	//一回しか殺したくないのでストッパー。
	bool m_siboustop = false;
	//ゲームオーバーを一回だけ出すけんね
	bool m_gameover_one = false;
	//ゲームクリアも一回だけ。
	bool m_Clear_one = false;
	//ゲームクリアの余韻用
	float m_timer = 0;
};

