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
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CEffect* m_effect;
	CVector3 m_position = CVector3::Zero;
	CPhysicsStaticObject m_StaticObject;
	float m_timer = 0.0f;
};

