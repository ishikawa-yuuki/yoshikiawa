#pragma once
class SSPlayer : public IGameObject//ステージ選択専用
{
public:
	SSPlayer();
	~SSPlayer();
	bool Start();
	void Update();
	void Move(); // プレイヤーの基本的な動き
	CVector3 GetPosition() const { // プレイヤーの場所を返す関数。
		return m_position;
	}
	int GetStagenum() {//選択したステージの番号
		return m_stage;
	}
	enum Stage {
		stage1 = 1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
};

