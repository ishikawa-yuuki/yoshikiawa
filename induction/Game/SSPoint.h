#pragma once
#include "GameData.h"
#include "tkEngine/light/tkPointLight.h"
//�X�e�[�W��position
class SSPoint : public IGameObject
{
public:
	SSPoint();
	~SSPoint();
	bool Start();
	void Update();
	//�ԍ���ݒ�
	void SetNumber(const GameData::StageNumber& number)
	{
		m_stagenumber = number;
	}
	//�ԍ����擾
	GameData::StageNumber GetStageNumber() const
	{
		return m_stagenumber;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//�v���C���[�̍��W��ݒ�
	void SetPlayerPosition(const CVector3& pos)
	{
		m_playerposition = pos;
	}
	//�v���C���[�̍��W���擾
	CVector3 GetPlayerPosition() const
	{
		return m_playerposition;
	}
	//Human�̍��W��ݒ�
	void SetHumanPosition(const CVector3& pos)
	{
		m_humanposition = pos;
	}
	//Human�̍��W���擾
	CVector3 GetHumanPosition() const
	{
		return m_humanposition;
	}
	//��]��ݒ�
	void SetRotation(const CQuaternion& rot)
	{
		m_rotation = rot;
	}
	enum State {
		enState_Clear,							//�N���A�ς�
		enState_Release,						//���߂�
		enState_noRelease						//���߂Ȃ�
	};
	//���g�̏�Ԃ��擾
	State GetState()
	{
		return m_state;
	}
private:
	State m_state = enState_noRelease;
	CVector3 m_position = CVector3::Zero;
	prefab::CSkinModelRender* m_skin = nullptr;
	GameData::StageNumber m_stagenumber = GameData::enState_Stage1;
	CVector3 m_playerposition = CVector3::Zero;
	CVector3 m_humanposition = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity;
};

