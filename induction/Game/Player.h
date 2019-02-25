#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
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
	int GetColor(){//���̐F��Ԃ���//�@�@�@�|�C���^�g���Ƃ�����������Ȃ��B //int�^�ɂȂ����B�B�B
		int number = 0;
		switch (m_color)
		{
		case hikari_hutu:
			number = 0;
			break;
		case hikari_red:
			number = 1;
			break;
		}
		return number;
	}
private:
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect;
	GameCamera* m_gamecamera = nullptr;
	CCharacterController m_charaCon;
};

