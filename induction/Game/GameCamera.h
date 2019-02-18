#pragma once

#include "tkEngine/camera/tkSpringCamera.h"
class Player;
class Human;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void follow();
	void Hutu();
private:
	CVector3 m_PlayerPos; // �~�̒��S���W�ł��B�O�����ɃE�\�R�����g�����Ă܂����c
	//�p�x
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	//��]���x
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//�p�x�����W�A���P�ʂɒ���������
	double m_radianx = 0.0f;
	double m_radiany = 0.0f;

	const float m_r = 200.0f;//���a�`

	CVector3 m_position;
	Player* m_player;
	Human* m_human;
	CSpringCamera m_springCamera;
	CVector3 m_target;//�������������_�ł��B
	CVector3 m_ToPos = { 0.0f,450.0f,0.0f };
};

