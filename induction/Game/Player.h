#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"
class GameCamera;
class Human;
class StarDust;
class Title;
class Game;
class TitleGround;
class Player : public IGameObject
{
private:
	//�����ɏ������ق����s���������̂�
    //��������private�ɂ��Ă��܂��B
	enum Color {
		hikari_hutu,
		hikari_black,
		hikari_explosion
	};
	
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
		case hikari_explosion:
			number = 2;
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
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
private:
	CVector3 m_position = { 0.0f,0.0f,500.0f };
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	prefab::CSkinModelRender* m_skin = nullptr;
	GameCamera* m_gamecamera = nullptr;
	Human* m_human = nullptr;
	StarDust* m_stardust = nullptr;
	Game* m_game = nullptr;
	CCharacterController m_charaCon;
	prefab::CPointLight* m_ptLight = nullptr;
	//�ʏ��Ԃ̌��̗́B�������p
	const CVector3 m_pointLigDefaultAttn = {1000.0f, 10.0f, 0.0f};
	//�ϓ�������̗́B��p
	CVector3 m_attn = { 1000.0f,10.0f,0.0f };
	float m_explosionTimer = 0;
	//�ŏ��̃v���C���[�̋������I��������ǂ����B
	bool m_StartMoveFin = false;
	Title* m_title = nullptr;
	//�u���b�N�z�[���ɂȂ鎞�Ɍ������ӂ�銴���𒲐����邽�߂̕ϐ�
	float m_ahureru = 0;

	prefab::CSoundSource* m_sound = nullptr;
	TitleGround* m_titleground = nullptr;
	CVector3 m_protposition = CVector3::Zero;
	float m_degree = 0.0f;
	Color m_color = hikari_hutu;
};

