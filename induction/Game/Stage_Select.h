#pragma once
class Fade;
class SSPlayer;
class SSHuman;
class SSGameCamera;
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	bool m_isWaitFadeout = false;//trueなら画面を切り替える。
	bool m_Tile = false;
	Fade* m_fade = nullptr;
	SSPlayer* m_ssPlayer = nullptr;
	SSHuman* m_ssHuman = nullptr;
	SSGameCamera* m_ssGC = nullptr;
};

