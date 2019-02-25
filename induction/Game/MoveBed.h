#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class MoveBed : public IGameObject
{
public:
	MoveBed();
	~MoveBed();
	bool Start();
	void Update();
	CVector3 GetPosition() const {// プレイヤーの場所を返す関数。
		return m_position;
	}
	CVector3 GetLastPos() const {// 1フレーム前のプレイヤーの場所を返す関数。
		return m_lastFramepos;
	}
	CPhysicsGhostObject* GetGhost() {//ゴーストオブジェクトの情報を返す関数。
		return &m_GhostObject;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CVector3 m_position = { 0.0f, 0.0f, -900.0f };//{800.0f, -160.0f, -900.0f};
	CVector3 m_ppos = m_position;//ボックス形状専用
	CVector3 m_protpos = m_position;//初期位置
	CVector3 m_moveSpeed = { 2.0f, 0.0f, 0.0f };
	CVector3 m_lastFramepos = m_position;//１フレーム前の位置
	CPhysicsStaticObject m_StaticObject;
	CPhysicsGhostObject m_GhostObject;
};

