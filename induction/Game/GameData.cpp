#include "stdafx.h"
#include "GameData.h"
#include "GameCamera.h"

GameData::GameData()
{
	//�����Ɋe�`�F�b�N�|�C���g�̊p�x�����Ă�����
	m_cameradegreelist.push_back({ 0.0f,degleeY });			//������X�e�[�W1��
	m_cameradegreelist.push_back({ 0.0f,degleeY });         //���X�e�[�W2
	m_cameradegreelist.push_back({ 0.0f,degleeY });         //���X�e�[�W3
	m_cameradegreelist.push_back({ -90.0f,degleeY });       //���X�e�[�W4
	m_cameradegreelist.push_back({ -30.0f,degleeY });       //���X�e�[�W5
}


GameData::~GameData()
{
}