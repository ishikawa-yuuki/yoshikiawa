#pragma once
class Fade;
class Help : public IGameObject
{
public:
	Help();
	~Help();
	bool Start();
	void Update();
	void SetisTransStage()
	{
		m_istransstage = true;
	}
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	bool m_istransstage = false;
};

