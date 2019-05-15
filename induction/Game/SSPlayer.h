#pragma once
#include "tkEngine/light/tkPointLight.h"
#include "GameData.h"
class Stage_Select;
class SSPoint;
class GameData;
class SSHuman;
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
	void Stop();
	void TransStage();
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const 
	{ 
		return m_position;
	}
	//�I�������X�e�[�W�̔ԍ�
	GameData::StageNumber GetStagenum() const
	{
		return m_stage;
	}
	//���X�^�[�g�ł��邩���ׂ�֐�
	bool GetOK() const
	{
		return m_SelectOK;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const GameData::StageNumber& stagenumber)
	{
		m_stage = stagenumber;
	}
	//�X�e�[�W�J�ڂ̑O�i�K���ǂ���
	bool GetisTransStage() const
	{
		return m_state == enState_TransStage;
	}
	//�X�e�[�W�ɑJ�ڂ��邩�ǂ���
	bool GetisStage() const
	{
		return m_timer >= m_transtime;
	}
	bool GetisMoveHuman() const
	{
		return m_timer >= m_movetime;
	}
	enum State {
		enState_Move,					//�ړ�
		enState_Stop,					//��~
		enState_TransStage				//�Q�[���ɑJ��
	};
	const float m_speed = 500.0f;
	const float m_distance = 20.0f * 20.0f;
	const float m_transspeed = 300.0f;
	const float m_transtime = 1.5f;
	const float m_movetime = 0.4f;
private:
	GameData::StageNumber m_stage = GameData::enState_Stage1;
	State m_state = enState_Stop;
	//true�Ȃ�X�^�[�g
	bool m_SelectOK = true;
	//true�Ȃ�ړ���
	bool m_State = false;
	Stage_Select * m_SS = nullptr;
	SSPoint * m_sspoint = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_moveSpeed = CVector3::Zero;
	prefab::CEffect* m_effect = nullptr;
	prefab::CPointLight* m_ptLight = nullptr;
	GameData* m_gamedata = nullptr;
	SSHuman* m_sshuman = nullptr;
	float m_timer = 0.0f;

};

