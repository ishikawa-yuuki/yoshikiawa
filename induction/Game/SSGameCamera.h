#pragma once
class SSPlayer;
//ステージ選択専用
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

