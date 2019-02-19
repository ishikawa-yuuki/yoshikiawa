#pragma once
class Game;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	Game* m_game;
};

