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
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Perspective);
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
	m_PlayerPos = m_player->GetPosition();
	CVector3 stickR;
	stickR.x = -Pad(0).GetRStickXF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.y = Pad(0).GetLStickYF();	//�A�i���O�X�e�B�b�N��x�̓��͗ʂ��擾�B
	stickR.z = 0.0f;
	//�E�X�e�B�b�N�̓���
	//�E�X�e�B�b�N
	m_sdegreexz = -stickR.x * 1.0f;
	m_sdegreey = -stickR.y*1.0f;

	//��]�x���Z
	m_degreey += m_sdegreey;
	m_degreexz += m_sdegreexz;
	//�㉺�����̃J�����ړ����Œ�
	m_degreey = 30.0f;
	/*if (m_degreey >= 30.0f) {//camera��������ɓ������v���O����
	m_degreey = 30.0f;         //���������܂苭����ɂ͓����Ȃ��B
	}
	if (m_degreey <= 10.0f) {
	m_degreey = 10.0f;
	}*/
	/*if (m_degreexz >= 70.0f) {
	m_degreexz = 70.0f;
	}
	if (m_degreexz <= -70.0f) {
	m_degreexz = -70.0f;
	}*/

	//�p�x�����W�A���P�ʂɒ���
	m_radianx = M_PI / 180 * m_degreexz;
	m_radiany = M_PI / 180 * m_degreey;
	Hutu();
	//follow();
	//m_target.z += 350.0f;
	//���_z
	MainCamera().SetTarget(m_target);
	//���W
	MainCamera().SetPosition(m_position);
	//�J�����̍X�V�B
	MainCamera().Update();
}

void GameCamera::Hutu()
{
	m_target = { 0.0f,0.0f,0.0f };
	m_target.y += 20.0f;
	m_target += m_player->GetPosition();
	//�����_���v�Z����B
	//target.y += 200.0f;
	//Y������ɉ�]������B
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY, m_radianx);
	CVector3 ToPos = { 0.0f, 0.0f, 3.0f };
	qRot.Multiply(ToPos);
	//�㉺�̉�]�B
	//�܂��͉񂷎����v�Z����B
	CVector3 rotAxis;

	rotAxis.Cross(ToPos, CVector3::AxisY);
	//�x�N�g���𐳋K������B
	rotAxis.Normalize();
	qRot.SetRotation(rotAxis, m_radiany);
	qRot.Multiply(ToPos);
	ToPos *= m_r;
	m_position = m_target + ToPos * 1.75f;

	/*ps = toPos / r;
	CVector3 rotAxis3;
	rotAxis3.Cross(toPos, CVector3::AxisY);
	rotAxis3.Normalize();
	rotAxis3.y -= rotAxis3.y;
	ps = rotAxis3;*/

	ToPos *= 2;
	//m_toPos.y = 0.0f;
	m_target -= ToPos;
	ToPos *= 1.5f;
	/*toPos.x = -r * cos(radianx);
	toPos.y = r * sin(radiany);
	toPos.z=r*(sin(radianx)+cos(radiany));*/
	//toPos.z = r * sin(radianx);
}

//���͎g���Ȃ�follow�֐��A
void GameCamera::follow()
{
	//�v���C���[�ɒǏ]����΂˃J����
	//�������ɂ͎��R�ɉ�]�����邱�Ƃ��ł���悤�ɂ������B
	CVector3 Old_Topos = m_ToPos;
	CVector3 HumanPos = m_human->GetPosition();
	CVector3 diff = m_PlayerPos - HumanPos;
	float len = diff.LengthSq();
	if (len >= 300.0f*300.0f) {
		m_ToPos += {0.0f, 4.0f, 0.0f};//���񂾂񗣂��
		if (m_ToPos.y > 950.0f) {
			m_ToPos = Old_Topos; //�J���������ɗ��ꂷ���Ȃ��悤�Œ�
		}
	}
	else if (len <= 150.f) {
		m_ToPos -= {0.0f, 6.0f, 0.0f};//�ǂ�ǂ�ߊ��
		if (m_ToPos.y < 450.0f) {
			m_ToPos = Old_Topos;//�J���������Ɋ�肷���Ȃ��悤�Œ�
		}
	}
	CVector3 CameraPos = m_PlayerPos + m_ToPos;
	MainCamera().SetTarget(m_PlayerPos);//�v���C���[�̈ʒu�𒍎��_�ɂ���B
	MainCamera().SetPosition(CameraPos);
	MainCamera().Update();
}