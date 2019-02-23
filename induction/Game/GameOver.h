#pragma once
class Game;
class Fade;
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
	Fade* m_fade = nullptr;
	bool m_isWaitFadeout = false;
};

