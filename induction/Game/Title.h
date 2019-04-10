#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	//タイトルシーンの選択
	void Choice(); 
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	// 弓の初期位置、select1の横にある。
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f };
	enum Select {
		//stage選択画面
		select1,
		//操作方法画面
		select2,
		//クレジット
		select3
	};
	Select m_select = select1;
	//trueなら画面を切り替える。
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

