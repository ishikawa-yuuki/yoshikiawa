#pragma once
#include "tkEngine/light/tkPointLight.h"

class Stage_Select;
class SSPoint;
//ステージ選択専用
class SSPlayer : public IGameObject
{
public:
	SSPlayer();
	~SSPlayer();
	bool Start();
	void Update();
	// プレイヤーの基本的な動き
	void Move(); 
	void MoveState();
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const 
	{ 
		return m_position;
	}
	//選択したステージの番号
	int GetStagenum() const
	{
		return m_stage;
	}
	//今スタートできるか調べる関数
	bool GetOK() const
	{
		return m_SelectOK;
	}
	enum Stage {
		stage1 = 1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
private:
	//trueならスタート
	bool m_SelectOK = true;
	//trueなら移動中
	bool m_State = false;
	Stage_Select * m_SS = nullptr;
	SSPoint * m_sspoint = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect;
	prefab::CPointLight* m_ptLight = nullptr;
};

