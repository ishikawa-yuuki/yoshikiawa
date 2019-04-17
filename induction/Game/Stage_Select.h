#pragma once
class Fade;
class SSPlayer;
class SSHuman;
class SSPoint;
class SSGameCamera;
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
	static const int point = 3;
	SSPoint* m_ssPoint[point] = { nullptr, nullptr, nullptr };
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	//trueなら画面を切り替える。
	bool m_isWaitFadeout = false;
	//タイトル切り替えtrueなら切り替える
	bool m_Tile = false;
	Fade* m_fade = nullptr;
	SSPlayer* m_ssPlayer = nullptr;
	SSHuman* m_ssHuman = nullptr;
	SSGameCamera* m_ssGC = nullptr;
};

