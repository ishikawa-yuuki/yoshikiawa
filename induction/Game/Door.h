#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Game;
class Door : public IGameObject
{
public:
	Door();
	~Door();
	bool Start();
	void Update();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	void SetRot(const CQuaternion& rot) {
		m_rot = rot;
	}
	void SetNum(int number)
	{
		num = number;
	}
private:
	Game* m_game;
	prefab::CSkinModelRender* m_skin = nullptr;
	CPhysicsStaticObject m_StaticObject;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	float m_timer = 0.0f;
	enum DoorAnimationClip {
		enAnimationClip_STOP,
		enAnimationClip_OPEN,
		enAnimationClip_num
	};
	//アニメーションクリップ詰め合わせ
	CAnimationClip m_animClip[enAnimationClip_num];
	//0なら二つ、1なら一つ
	int num = 0;
};

