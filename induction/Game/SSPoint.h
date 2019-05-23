#pragma once
#include "GameData.h"
#include "tkEngine/light/tkPointLight.h"
//ステージのposition
class SSPoint : public IGameObject
{
public:
	SSPoint();
	~SSPoint();
	bool Start();
	void Update();
	//番号を設定
	void SetNumber(const GameData::StageNumber& number)
	{
		m_stagenumber = number;
	}
	//番号を取得
	GameData::StageNumber GetStageNumber() const
	{
		return m_stagenumber;
	}
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//プレイヤーの座標を設定
	void SetPlayerPosition(const CVector3& pos)
	{
		m_playerposition = pos;
	}
	//プレイヤーの座標を取得
	CVector3 GetPlayerPosition() const
	{
		return m_playerposition;
	}
	//Humanの座標を設定
	void SetHumanPosition(const CVector3& pos)
	{
		m_humanposition = pos;
	}
	//Humanの座標を取得
	CVector3 GetHumanPosition() const
	{
		return m_humanposition;
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	enum State {
		enState_Clear,							//クリア済み
		enState_Release,						//挑める
		enState_noRelease						//挑めない
	};
	//自身の状態を取得
	State GetState()
	{
		return m_state;
	}
private:
	State m_state = enState_noRelease;
	CVector3 m_position = CVector3::Zero;
	prefab::CSkinModelRender* m_skin = nullptr;
	GameData::StageNumber m_stagenumber = GameData::enState_Stage1;
	CVector3 m_playerposition = CVector3::Zero;
	CVector3 m_humanposition = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
};

