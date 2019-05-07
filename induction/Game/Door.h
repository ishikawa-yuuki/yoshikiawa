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
private:
	Game* m_game;
	prefab::CSkinModelRender* m_skin = nullptr;
	CPhysicsStaticObject m_StaticObject;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	enum DoorAnimationClip {
		enAnimationClip_OPEN,
		enAnimationClip_num
	};
	//アニメーションクリップ詰め合わせ
	CAnimationClip m_animClip[enAnimationClip_num];
};

