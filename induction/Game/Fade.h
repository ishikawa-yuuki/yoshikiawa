#pragma once
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start()override;
	void Update()override;
	void PostRender(CRenderContext&rc) override;
	void StartFadeIn() {
		m_state = enState_FadeIn;
	}
	void StartFadeOut() {
		m_state = enState_FideOut;
	}
	bool IsFade() const {
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const{
		return m_currentAlpha;
	}
private:
	enum enState_Fade {
		enState_FadeIn,
		enState_FideOut,
		enState_Idle
	};
	CShaderResourceView m_texture;
	CSprite m_sprite;
	enState_Fade m_state = enState_Idle;
	float m_currentAlpha = 1.0f;
};

