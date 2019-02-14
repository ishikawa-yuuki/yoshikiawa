#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class GameCamera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move(); // �v���C���[�̊�{�I�ȓ���
	CVector3 GetPosition() const{ // �v���C���[�̏ꏊ��Ԃ��֐��B
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
	GameCamera* m_gamecamera = nullptr;
};

