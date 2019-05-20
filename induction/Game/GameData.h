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
	//�X�e�[�W���N���A�����I
	void SetStageClear() 
	{
		m_stageclear[m_stagenumber - 1] = true;
	}
	//�`�F�b�N�|�C���g�ʉ߂����I
	void SetStageCheck()
	{
		m_stagecheck[m_stagenumber - 1] = true;
	}
	//�X�e�[�W���N���A���Ă��邩�ǂ������擾
	bool GetisStageClear(const StageNumber& number)
	{
		return m_stageclear[number - 1];
	}
	//�`�F�b�N�|�C���g��ʉ߂��Ă��邩�ǂ������擾
	bool GetisStageCheck(const StageNumber& number)
	{
		return m_stagecheck[number - 1];
	}
	//�I�������X�e�[�W�̔ԍ���ݒ�
	void SetStageNumber(const StageNumber& number)
	{
		m_stagenumber = number;
	}
	//�I�������X�e�[�W���擾
	StageNumber GetStageNumber() const
	{
		return m_stagenumber;
	}
	//�G�t�F�N�g�̖��O���擾
	const char* GetEffectName()
	{
		return m_effectname;
	}
	//�`�F�b�N�|�C���g����n�߂邩�ǂ�����ݒ�
	void SetCheckPoint(bool start) 
	{
		m_startcheckpoint = start;
	}
	//�`�F�b�N�|�C���g����n�߂邩�ǂ������擾
	bool GetisStartCheckPoint()
	{
		return m_startcheckpoint;
	}
	//�n�߂ăX�e�[�W�ɓ��������ǂ������擾
	bool GetisFirstEnterStage()
	{
		return m_isfirstenterstage;
	}
	//�X�e�[�W�ɓ������I
	void SetisEnterStage()
	{
		m_isfirstenterstage = true;
	}
	static const int m_stagelimit = 3;								//�X�e�[�W�̐�
public:
	bool m_stageclear[m_stagelimit] = { true,true,false };			//�e�X�e�[�W�̃N���A��
	bool m_stagecheck[m_stagelimit] = { false,false,false };		//�`�F�b�N�|�C���g�̒ʉߏ�
	StageNumber m_stagenumber = enState_Stage1;						//�v���C���[���I�������X�e�[�W�̔ԍ�
	const char* m_effectname = "Effect";							//�X�e�[�W�I�����ɋ����I�ɏ����������G�t�F�N�g�ɖ��O��t����Ƃ��Ɏg��
	bool m_startcheckpoint = false;									//�`�F�b�N�|�C���g����n�߂邩�ǂ���
	bool m_isfirstenterstage = false;
};

