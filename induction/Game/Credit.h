#pragma once
class Credit : public IGameObject
{
public:
	Credit();
	~Credit();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
};

