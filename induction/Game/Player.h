#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"
class GameCamera;
class Human;
class StarDust;
class Player : public IGameObject
{
private:
	//�����ɏ������ق����s���������̂�
    //��������private�ɂ��Ă��܂��B
	enum Color {
		hikari_hutu,
		hikari_black
	};
	Color m_color = hikari_hutu;
public:
	Player();
	~Player();
	bool Start();
	void Update();
	// �v���C���[�̊�{�I�ȓ���
	void Move(); 
	// �v���C���[���Q�[�����n�߂鎞�̓����B
	void GameStartMove();
	//���̐F�ύX�A���`�F�N���̃N�����N�C���[�W�A
	void Color_Change();
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const
	{ 
		return m_position;
	}
	//�v���C���[�̍ŏ��̈ړ����I���������Ԃ��֐��B
	bool GetStartMove()const
	{
		return m_StartMoveFin;
	}
	/*���̐F��ς��܂�*/
	//���̐F��Ԃ��� int�^�ɂȂ����B�B�B
	int GetColor(){
		int number = 0;
		switch (m_color)
		{
		case hikari_hutu:
			number = 0;
			break;
		case hikari_black:
			number = 1;
			break;
		}
		return number;
	}
	CVector4 GetPointLightAttn() const
	{
		return m_ptLight->GetAttn();
	}
	prefab::CPointLight* GetPointLight() const
	{
		return m_ptLight;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,500.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	prefab::CSkinModelRender* m_skin = nullptr;
	GameCamera* m_gamecamera = nullptr;
	Human* m_human = nullptr;
	StarDust* m_stardust = nullptr;
	CCharacterController m_charaCon;
	prefab::CPointLight* m_ptLight = nullptr;

	//�ŏ��̃v���C���[�̋������I��������ǂ����B
	bool m_StartMoveFin = false;
};

