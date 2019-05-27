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
	//void PostRender(CRenderContext& renderContext);
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_spriteRender2 = nullptr;
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	bool m_istransstage = false;
	bool m_nextSprite = false;
	//CFont m_font;
};

