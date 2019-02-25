#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	void Move();
	void Turn();
	void AnimeControll();//プレイヤーのアニメの変更
	void isDead();//やったか！を判定する
	void Hanntei();
	/*void PostRender(CRenderContext& rc);*/
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//死んだかどうかを返す関数
	bool GetisDead()const 
	{
		return m_isDead;
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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;//スキンモデルレンダラー
	Player* m_player;
	Game* m_game;
	CVector3 m_position = CVector3::Zero;
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
	CAnimationClip m_animClip[enAnimationClip_num];//アニメーションクリップ詰め合わせ
	CFont m_font;//調べるためのフォント、何かに使うかも
	bool m_isDead = false;//死んだかどうか
	bool m_isGameOver = false;//ゲームオーバーかどうか
	bool m_siboustop = false;//一回しか殺したくないのでストッパー。
};

