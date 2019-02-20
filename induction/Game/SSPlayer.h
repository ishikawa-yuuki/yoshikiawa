#pragma once
class Stage_Select;
class SSPoint;
class SSPlayer : public IGameObject//ステージ選択専用
{
public:
	SSPlayer();
	~SSPlayer();
	bool Start();
	void Update();
	void Move(); // プレイヤーの基本的な動き
	void MoveState();
	CVector3 GetPosition() const { // プレイヤーの場所を返す関数。
		return m_position;
	}
	int GetStagenum() const{//選択したステージの番号
		return m_stage;
	}
	bool GetOK() const {
		return m_SelectOK;
	}
	enum Stage {
		stage1 = 1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
private:
	bool m_SelectOK = true;
	bool m_State = false;
	bool m_AfterState = false;
	Stage_Select * m_SS = nullptr;
	SSPoint * m_sspoint = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_v = CVector3::Zero;
	prefab::CEffect* m_effect;
};

