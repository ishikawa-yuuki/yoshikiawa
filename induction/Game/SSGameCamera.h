#pragma once
class SSPlayer;
class SSGameCamera : public IGameObject//ステージ選択専用
{
public:
	SSGameCamera();
	~SSGameCamera();
	bool Start();
	void Update();
private:
	SSPlayer * m_ssplayer = nullptr;
	
};

