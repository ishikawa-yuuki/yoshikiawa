#pragma once
class CheckPoint:public IGameObject
{
public:
	CheckPoint();
	~CheckPoint();
	bool Start();
	void Update();
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//���W���擾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//�ʉߍς݂��ǂ������擾
	bool GetisPass() const
	{
		return m_pass;
	}
	//�ʉ߂������ǂ�����ݒ�
	void SetPass(bool pass) 
	{
		m_pass = pass;
	}

private:
	bool m_pass = false;
	CVector3 m_position = CVector3::Zero;
};

