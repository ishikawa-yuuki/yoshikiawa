#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;//
};

