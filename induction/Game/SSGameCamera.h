#pragma once
class SSPlayer;
//�X�e�[�W�I���p
class SSGameCamera : public IGameObject
{
public:
	SSGameCamera();
	~SSGameCamera();
	bool Start();
	void Update();
private:
	SSPlayer * m_ssplayer = nullptr;
	
};

