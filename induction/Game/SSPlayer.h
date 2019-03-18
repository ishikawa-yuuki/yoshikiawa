#pragma once
#include "tkEngine/light/tkPointLight.h"

class Stage_Select;
class SSPoint;
//�X�e�[�W�I���p
class SSPlayer : public IGameObject
{
public:
	SSPlayer();
	~SSPlayer();
	bool Start();
	void Update();
	// �v���C���[�̊�{�I�ȓ���
	void Move(); 
	void MoveState();
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const 
	{ 
		return m_position;
	}
	//�I�������X�e�[�W�̔ԍ�
	int GetStagenum() const
	{
		return m_stage;
	}
	//���X�^�[�g�ł��邩���ׂ�֐�
	bool GetOK() const
	{
		return m_SelectOK;
	}
	enum Stage {
		stage1 = 1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
private:
	//true�Ȃ�X�^�[�g
	bool m_SelectOK = true;
	//true�Ȃ�ړ���
	bool m_State = false;
	Stage_Select * m_SS = nullptr;
	SSPoint * m_sspoint = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect;
	prefab::CPointLight* m_ptLight = nullptr;
};

