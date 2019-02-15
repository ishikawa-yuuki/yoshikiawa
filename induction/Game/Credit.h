#pragma once
class Fade;
class Credit : public IGameObject
{
public:
	Credit();
	~Credit();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	bool  m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

