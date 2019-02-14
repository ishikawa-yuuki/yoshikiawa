#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Human.h"
#define _USE_MATH_DEFINES //M_PI(�~����)���Ăяo��
#include <math.h>

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	m_human = FindGO<Human>("Human");
	//�J������ݒ�B
	//�j�A�N���b�v�ƃt�@�[�N���b�v�ݒ�(��)
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);

	//�΂˃J�����̏�����
	m_springCamera.Init(
		MainCamera(),
		1000.0f,
		true,
		5.0f
	);
	return true;
}

void GameCamera::Update()
{
	//�v���C���[�ɒǏ]����΂˃J����
	//�������ɂ͎��R�ɉ�]�����邱�Ƃ��ł���悤�ɂ������B

	PlayerPos = m_player->GetPosition();
	CVector3 HumanPos = m_human->GetPosition();
	CVector3 diff = PlayerPos - HumanPos;
	float len = diff.Length();
	if (len >= 300.0f) {
		m_ToPos += {0.0f, 2.0f, 2.0f};
		if (m_ToPos.y > 750.0f) {
			m_ToPos = { 0.0f,750.0f,750.0f };
		}
	}
	else if(len <= 150.f){
		m_ToPos -= {0.0f, 5.0f, 5.0f};
		if (m_ToPos.y < 450.0f) {
			m_ToPos = { 0.0f,450.0f,450.0f };
		}
	}
	CVector3 CameraPos = PlayerPos + m_ToPos;
	m_springCamera.SetTarget(PlayerPos);//�v���C���[�̈ʒu�𒍎��_�ɂ���B
	m_springCamera.SetPosition(CameraPos);
	m_springCamera.Update();
}