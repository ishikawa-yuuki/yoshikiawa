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
	// 円の中心座標です。
	CVector3 m_PlayerPos;
	//角度
	float m_degreexz = 0.0f;
	float m_degreey = 0.0f;
	//回転速度
	float m_sdegreexz = 0.0f;
	float m_sdegreey = 0.0f;
	//角度をラジアン単位に直したもの
	double m_radianx = 0.0f;
	double m_radiany = 0.0f;
	//半径～
	const float m_r = 200.0f;

	CVector3 m_position;
	Player* m_player;
	Human* m_human;
	CSpringCamera m_springCamera;
	//こっちが注視点です。
	CVector3 m_target;
	CVector3 m_ToPos = { 0.0f,450.0f,0.0f };
};

