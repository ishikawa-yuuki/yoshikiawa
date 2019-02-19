#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
class GameCamera;
class Player : public IGameObject
{
private:
	//�����ɏ������ق����s���������̂�
	//��������private�ɂ��Ă��܂��B
	enum Color {
		hikari_hutu,
		hikari_red
	};
	Color m_color = hikari_hutu;
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Move(); // �v���C���[�̊�{�I�ȓ���
	void Color_Change();//���̐F�ύX�A���`�F�N���̃N�����N�C���[�W�A
	CVector3 GetPosition() const{ // �v���C���[�̏ꏊ��Ԃ��֐��B
		return m_position;
	}

	/*���̐F��ς��܂�*/
	Color GetColor()const {//���̐F��Ԃ���//�@�@�@�|�C���^�g���Ƃ�����������Ȃ��B
		return m_color;
	}
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
	GameCamera* m_gamecamera = nullptr;
};

