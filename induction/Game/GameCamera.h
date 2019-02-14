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
private:
	//角度
	float m_degreexz = 0.0f;
	//回転速度
	float m_sdegreexz = 0.0f;
	float m_radianx = 0.0f;

	CVector3 m_position;
	Player* m_player;
	Human* m_human;
	CSpringCamera m_springCamera;
	CVector3 PlayerPos; // target(注視点)です。
	CVector3 m_ToPos = { 0.0f,0.0f,0.0f };
};

