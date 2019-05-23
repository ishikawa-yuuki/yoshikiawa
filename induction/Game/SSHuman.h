#pragma once
#include "SSPlayer.h"
#include "GameData.h"
#include "tkEngine/character/tkCharacterController.h"
class SSPlayer;
class Stage_Select;
class SSpoint;
//�X�e�[�W�I���p
class SSHuman : public IGameObject
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Stop();
	void Move();
	void TransStage();
	//�v���C���[�̃A�j���̕ύX
	void Animation_Turn();
	//void PostRender(CRenderContext& rc);
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const { 
		return m_position;
	}
	//���W���擾
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//��~�����ǂ������擾
	bool GetisStop()
	{
		return m_state == SSPlayer::enState_Stop;
	}
	//�X�e�[�W�̔ԍ����擾
	GameData::StageNumber GetStageNumber()  const
	{
		return m_stage;
	}
	//�X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const GameData::StageNumber& stagenumber)
	{
		m_stage = stagenumber;
	}
	//��]��ݒ�
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
private:
	GameData::StageNumber m_stage = GameData::enState_Stage1;
	SSPlayer::State m_state = SSPlayer::enState_Stop;
	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_skin = nullptr;
	SSPlayer* m_ssplayer = nullptr;
	Stage_Select* m_stageselect = nullptr; 
	SSPoint* m_sspoint = nullptr;
	CVector3 m_position;
	CVector3 m_movespeed;
	CQuaternion m_qrot = CQuaternion::Identity;
	CQuaternion m_rotation = CQuaternion::Identity;
	enum HumanAnimationClip {
		enAnimationClip_idle,
		//	enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_clear,
		enAnimationClip_KneelDown,
		enAnimationClip_num
	};
	//�A�j���[�V�����N���b�v�l�ߍ��킹
	CAnimationClip m_animClip[enAnimationClip_num];
	CCharacterController m_charaCon;
	//CFont m_font;
};

