#pragma once
class Fade;
class SSPlayer;
class SSGameCamera;
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
	void Choice(); //ステージ選択するための関数
private:
	
	enum Stage {
		stage1,
		stage2,
		stage3
	};
	bool m_isWaitFadeout = false;//trueなら画面を切り替える。
	bool m_Tile = false;
	Fade* m_fade = nullptr;
	Stage m_stage = stage1;
	SSPlayer* m_ssPlayer = nullptr;
	SSGameCamera* m_ssGC = nullptr;
};

