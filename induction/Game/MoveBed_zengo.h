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

	//こいつがバグの元かも
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
	//レベルで設定した回転を代入する。
	void SetRot(const CQuaternion& rot) {
		m_rotation = rot;
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
	//この関数が呼ばれると処理が変わる。
	bool isLongFrag() {
		m_islong = true;
		return m_islong;
	}
private:
	const float MOVE_SPEED = 4.0f*60.0f;
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = {0.0f,0.0f,0.0f};
	//初期位置
	CVector3 m_protpos = m_position;
	CVector3 m_moveSpeed = { 0.0f, 0.0f, MOVE_SPEED };
	CQuaternion m_rotation = { 0.0f,0.0f,0.0f, 1.0f };
	//１フレーム前の位置
	CVector3 m_lastFramepos = CVector3::Zero;
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
	//レベルデザイン用のスケールを足しました
	CVector3 m_scale = { 0.0f,0.0f,0.0f };
	//移動する距離が長いか判定
	bool m_islong = false;
	float m_timer = 0.0f;
	
};