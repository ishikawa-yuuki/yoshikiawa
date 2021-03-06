#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Stone :public IGameObject
{
public:
	Stone();
	~Stone();
	bool Start();
	void Update();
	void Range();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	void SetProtPosition(CVector3 const& pos) {
		m_protposition = pos;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	void SetRot(const CQuaternion& rot) {
		m_rot = rot;
	}
	//回転、スピード
	void SetStoneNumber(const int& number) {
		m_num = number;
	};
	//大きさが違うときのに使う用
	void SetStoneScaleNum(const int& number) {
		m_scalenum = number;
	};
	//ゴーストオブジェクトの情報を返す関数。
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}
private:
	CPhysicsGhostObject m_GhostObject;
	CCharacterController m_charaCon;
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CSoundSource* m_sound = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_skinposition = CVector3::Zero;
	CVector3 m_protposition = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CVector3 m_axis = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	const float MOVE_SPEED = 11.5f * 60.0f;
	const float MOVE_SPEED_HIGH = 13.0f * 60.0f;
	const float ANGLE_SEED = 6.0f;
	float pos = 0;
	float m_timer = 0;
	//岩の転がる向きを決める。
	int m_num = 0;
	//岩の回転
	float m_angle = 0.0f;
	//岩の音
	float m_volume = 0.0f;
	//岩の大きさによる変更
	int m_scalenum = 0;
	Player* m_player;
	
};

