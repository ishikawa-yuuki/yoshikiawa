#pragma once
#include "tkEngine/Physics/tkPhysicsStaticObject.h"

class SSPlayer;
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
private:
	CPhysicsStaticObject m_physicsStaticObject;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	SSPlayer* m_ssplayer;
};