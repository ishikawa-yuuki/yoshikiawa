#pragma once
#include "tkEngine/Physics/tkPhysicsStaticObject.h"
class Stage_Number;
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CPhysicsStaticObject m_physicsStaticObject;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSoundSource* m_sound = nullptr;
	CVector3 m_position = CVector3::Zero;
	Stage_Number* m_stagenum = nullptr;
	CShaderResourceView m_refTexture; //反射マップ。
};