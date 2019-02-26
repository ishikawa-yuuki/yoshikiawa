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
	// �~�̒��S���W�ł��B
	CVector3 m_PlayerPos;
	//�p�x
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	//��]���x
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//�p�x�����W�A���P�ʂɒ���������
	double m_radianx = 0.0f;
	double m_radiany = 0.0f;
	//���a�`
	const float m_r = 200.0f;

	CVector3 m_position;
	Player* m_player;
	Human* m_human;
	CSpringCamera m_springCamera;
	//�������������_�ł��B
	CVector3 m_target;
	CVector3 m_ToPos = { 0.0f,450.0f,0.0f };
};

