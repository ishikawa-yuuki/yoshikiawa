#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
class Lightstand : public IGameObject
{
public:
	Lightstand();
	~Lightstand();
	bool Start();
	void Update();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	void SetNum(const int& n) {
		num = n;
	}
private:
	int num = 0;
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CEffect*  m_effect = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsStaticObject m_StaticObject;
	float m_timer = 0.0f;
};

