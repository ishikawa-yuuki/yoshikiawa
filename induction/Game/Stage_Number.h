#pragma once
class SSPlayer;
class Stage_Number : public IGameObject
{
public:
	Stage_Number();
	~Stage_Number();
	bool Start();
	void Update();
	//�I�������X�e�[�W�̔ԍ���Ԃ�
	//backGround�N���X�ɓ͂���p
	int GetStageNumber()
	{
		return m_stage;
	}
	//�^�C�g���ɖ߂�Ƃ��ɌĂ΂�܂�
	//�^�C�g���ɖ߂������ɂ��̃N���X���������܂��B
	bool IsTitle()
	{
		isTitle = true;
		return isTitle;
	}
	enum StageNum {
		stage1 = 1,
		stage2,
		stage3,
		stagenum
	};
	StageNum m_stage = stagenum;
private:
	SSPlayer* ssplayer;
	bool isTitle = false;
};

