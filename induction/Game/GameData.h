#pragma once
class GameData
{
private:
	GameData();
	~GameData();
public:
	static GameData& GetInstance()
	{
		static GameData gamedata;
		return gamedata;
	}
	enum StageNumber {
		enState_Stage1 = 1,
		enState_Stage2,
		enState_Stage3,
		enState_StageFirst = enState_Stage1,
		enState_StageLast = enState_Stage3
	};
	//�Q�[�����N���A�����I
	void SetStageClear() 
	{
		m_stageclear[m_stagenumber - 1] = true;
	}
	//�X�e�[�W���N���A���Ă��邩�ǂ������擾
	bool GetisStageClear(const int& number)
	{
		return m_stageclear[number - 1];
	}
	//�I�������X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const StageNumber& number)
	{
		m_stagenumber = number;
	}
	//�I�������X�e�[�W���擾
	StageNumber GetStageNumber()
	{
		return m_stagenumber;
	}
	static const int m_stagelimit = 3;								//�X�e�[�W�̐�
public:
	bool m_stageclear[m_stagelimit] = { false,false,false };		//�e�X�e�[�W�̃N���A��
	StageNumber m_stagenumber = enState_Stage1;						//�v���C���[���I�������X�e�[�W�̔ԍ�
};

