#pragma once
class Help : public IGameObject
{
public:
	Help();
	~Help();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
};

