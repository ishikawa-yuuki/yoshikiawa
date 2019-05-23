#pragma once
#include "SSPlayer.h"
#include "GameData.h"
#include "tkEngine/character/tkCharacterController.h"
class SSPlayer;
class Stage_Select;
class SSpoint;
//ステージ選択専用
class SSHuman : public IGameObject
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Stop();
	void Move();
	void TransStage();
	//プレイヤーのアニメの変更
	void Animation_Turn();
	//void PostRender(CRenderContext& rc);
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const { 
		return m_position;
	}
	//座標を取得
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//停止中かどうかを取得
	bool GetisStop()
	{
		return m_state == SSPlayer::enState_Stop;
	}
	//ステージの番号を取得
	GameData::StageNumber GetStageNumber()  const
	{
		return m_stage;
	}
	//ステージの番号を設定
	void SetStageNumber(const GameData::StageNumber& stagenumber)
	{
		m_stage = stagenumber;
	}
	//回転を設定
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
private:
	GameData::StageNumber m_stage = GameData::enState_Stage1;
	SSPlayer::State m_state = SSPlayer::enState_Stop;
	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_skin = nullptr;
	SSPlayer* m_ssplayer = nullptr;
	Stage_Select* m_stageselect = nullptr; 
	SSPoint* m_sspoint = nullptr;
	CVector3 m_position;
	CVector3 m_movespeed;
	CQuaternion m_qrot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;
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
	CCharacterController m_charaCon;
	//CFont m_font;
};

