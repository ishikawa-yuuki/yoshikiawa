#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class MoveBed_zengo : public IGameObject
{
public:
	MoveBed_zengo();
	~MoveBed_zengo();
	bool Start();
	void Update();
	
	void SetProtPos(const CVector3& pos)
	{
		m_protpos = pos;
	}
	//レベルで設置した所にm_positionを置く
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//レベルで設定した大きさを代入する。
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const
	{
		return m_position;
	}
	// 1フレーム前のプレイヤーの場所を返す関数。
	CVector3 GetLastPos() const
	{
		return m_lastFramepos;
	}
	//ゴーストオブジェクトの情報を返す関数。
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = { 0.0f, 0.0f, -900.0f };
	//ボックス形状専用
	CVector3 m_ppos = m_position;
	//初期位置
	CVector3 m_protpos = m_position;
	CVector3 m_moveSpeed = { 0.0f, 0.0f, 2.0f };
	//１フレーム前の位置
	CVector3 m_lastFramepos = m_position;
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
	//レベルデザイン用のスケールを足しました
	CVector3 m_scale = CVector3::Zero;
};