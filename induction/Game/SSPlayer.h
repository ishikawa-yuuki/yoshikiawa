#pragma once
#include "tkEngine/light/tkPointLight.h"
#include "GameData.h"
class Stage_Select;
class SSPoint;
class GameData;
class SSHuman;
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
	void Stop();
	void TransStage();
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const 
	{ 
		return m_position;
	}
	//選択したステージの番号
	GameData::StageNumber GetStagenum() const
	{
		return m_stage;
	}
	//今スタートできるか調べる関数
	bool GetOK() const
	{
		return m_SelectOK;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//ステージの番号を設定
	void SetStageNumber(const GameData::StageNumber& stagenumber)
	{
		m_stage = stagenumber;
	}
	//ステージ遷移の前段階かどうか
	bool GetisTransStage() const
	{
		return m_state == enState_TransStage;
	}
	//ステージに遷移するかどうか
	bool GetisStage() const
	{
		return m_timer >= m_transtime;
	}
	bool GetisMoveHuman() const
	{
		return m_timer >= m_movetime;
	}
	enum State {
		enState_Move,					//移動
		enState_Stop,					//停止
		enState_TransStage				//ゲームに遷移
	};
	const float m_speed = 500.0f;
	const float m_distance = 20.0f * 20.0f;
	const float m_transspeed = 300.0f;
	const float m_transtime = 1.5f;
	const float m_movetime = 0.4f;
private:
	GameData::StageNumber m_stage = GameData::enState_Stage1;
	State m_state = enState_Stop;
	//trueならスタート
	bool m_SelectOK = true;
	//trueなら移動中
	bool m_State = false;
	Stage_Select * m_SS = nullptr;
	SSPoint * m_sspoint = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	prefab::CPointLight* m_ptLight = nullptr;
	GameData* m_gamedata = nullptr;
	SSHuman* m_sshuman = nullptr;
	float m_timer = 0.0f;

};

