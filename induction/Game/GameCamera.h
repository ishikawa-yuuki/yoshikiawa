#pragma once
#include "GameData.h"
#include "tkEngine/camera/tkSpringCamera.h"
class Player;
class Human;
class Title;
class TitleGround;
class Stage_Select;
class SSPlayer;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void follow();
	void Hutu();
	void SetCameraDegree(const GameData::CameraDegree& degree)
	{
		m_degreexz = degree.s_degreexz;
		m_degreey = degree.s_degreey;
	}
private:
	// �~�̒��S���W�ł��B
	CVector3 m_PlayerPos;
	//�p�x
	float m_degreexz = 0.0f;
	float m_degreey = 30.0f;
	//��]���x
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//�p�x�����W�A���P�ʂɒ���������
	double m_radianx = 0.0f;
	double m_radiany = 0.0f;
	//���a�`
	const float m_r = 200.0f;

	CVector3 m_position = CVector3::Zero;
	Player* m_player;
	Human* m_human;
	CSpringCamera m_springCamera;
	float m_refreshTimer = 2.0f;
	//�������������_�ł��B
	CVector3 m_target = CVector3::Zero;
	CVector3 m_ToPos = { 0.0f,450.0f,0.0f };
	Title* m_title = nullptr;
	TitleGround* m_titleground = nullptr;
	float m_degree = 0.0f;
	CVector3 m_titletarget;

	//�X�e�[�W�Z���N�g
	Stage_Select* m_stageselect = nullptr;
	SSPlayer* m_ssplayer = nullptr;
};

