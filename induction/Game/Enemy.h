#pragma once
//#include "Path.h"
#include "tkEngine/character/tkCharacterController.h"
//#include "EnemyMoveLoop.h"
class Human;
class Game;
class Enemy :public IGameObject
{
public:
	Enemy();
	~Enemy();
	const float MOVE_SPEED = 150.0f;
	const float RADIUS = 20.0f;
	enum EnemyAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_num
	};
	bool Start();
	void Update();
	void SearchPlayer();
	CVector3 GetPosition() const{
		return m_position;
	}
	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	
	/*void PlayAnimation(EnemyAnimationClip  animNo)
	{
		m_skin->PlayAnimation(animNo);
	}
	void Move(float deltaTime, CVector3 move)
	{
		(void)deltaTime;
		m_position = m_charaCon.Execute(move);
	}
	void Init(const wchar_t* movePathFilePath)
	{
		m_movePath.Load(movePathFilePath);
	}*/
	//敵の前方向を取得。
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	//	プレイヤーを発見したか判定。
	bool IsFindPlayer() const
	{
		return m_isFindPlayer;
	}
	void NotifyRestart();
	void Move();
	void Turn();
private:
	enum State{
		State1,
		State2,
		State3,
		State4
	};
	float m_timer =0;
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = CVector3::Zero;//{-200.0f, 0.0f, 500.0f};
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_prot = m_position;
	CQuaternion m_rotation = CQuaternion::Identity;
	CVector3 m_forward = CVector3::AxisZ;
	Human* m_human = nullptr;
	Game* m_game = nullptr;
	State m_state = State1;
	//Path m_movePath;								//!<移動パス。
	//EnemyMoveLoop m_pathMoveLoop;
	CAnimationClip m_animClip[enAnimationClip_num];
	CCharacterController m_charaCon;
	bool m_isFindPlayer = false;
  
};