#pragma once
class SSPlayer;
class SSGameCamera : public IGameObject//�X�e�[�W�I���p
{
public:
	SSGameCamera();
	~SSGameCamera();
	bool Start();
	void Update();
private:
	SSPlayer * m_ssplayer = nullptr;
	CVector3 SSPlayerPos; // target(�����_)�ł��B
};

