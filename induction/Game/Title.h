#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Choice(); //タイトルシーンの選択
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f }; // 弓の初期位置、select1の横にある。
	enum Select {
		select1,//stage選択画面
		select2,//操作方法画面
		select3//クレジット
	};
	Select m_select = select1;
	bool m_isWaitFadeout = false;//trueなら画面を切り替える。
	Fade* m_fade = nullptr;
};

