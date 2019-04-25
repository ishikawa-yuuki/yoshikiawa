#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
class Fade;
class MistEnemy;
class Light_Object;
class Light_Object2;
class Exit;
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
	//Mistenemyに連れていかれているときの処理
	void TakingMove();
	//LightObjectを見つけたときの処理
	void Light_Move();
	//足の音の大きさ
	void Range();
	//プレイヤーのアニメの変更
	void AnimeControll();
	//やったか！を判定する
	void isDead();
	//動く床の判定
	void Hanntei();
	//クリアかどうか
	void isClear();
	//ランタンとの距離を把握させる
	void lanpos(CVector3 pos);
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
	//mistenemyが行動を変えるためのスイッチ関数
	bool GetismistEnemy()const {
		return mistflag;
	}
	//humanを倒すときの関数、enemyとかが使うと思います。
	void isKill() 
	{
		if (!m_isDead) {
			m_isDead = true;
		}
	}
	prefab::CPointLight* GetNearPointLight() const
	{
		return m_nearPointLight;
	}
private:
	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player;
	MistEnemy* m_mistenemy;
	Game* m_game;
	Fade* m_fade;
	Exit* m_exit;
	//Light_Object2* m_lightObject2;
	CVector3 m_position = { 0.0f,0.0f,700.0f };
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_Bedspeed = CVector3::Zero;
	CQuaternion m_qrot = CQuaternion::Identity;
	CCharacterController m_charaCon;
	enum HumanAnimationClip {
		enAnimationClip_idle,
	//	enAnimationClip_walk,
		enAnimationClip_run,
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
	//距離調べ
	float m_nearLen = 10000.0f;
	//一番近いライト検索
	prefab::CPointLight* m_nearPointLight = nullptr;
	//mistenemyが近寄るフラグ
	bool mistflag = false;
	//後で消す
	float m_kari = 0.0;
	//足の音
	float m_volume = 0;
};

