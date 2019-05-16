#pragma once
#include <unordered_map>
class Fade;
class Credit : public IGameObject
{
public:
	Credit();
	~Credit();
	bool Start();
	void Update();
	void PostRender(CRenderContext& renderContext); //何かを調べるためのポストレンダラ
private:
	prefab::CSky* m_sky = nullptr;
	bool  m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	CFont m_font;
	std::unordered_map<int, const wchar_t*> m_characterList;   //プレイヤーの座標のリスト
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	int m_number = 0;
	bool m_addtimer = true;
	bool m_stop = false;
	bool m_owari = false;
	bool m_transscene = false;
	prefab::CSoundSource* m_bgm = nullptr;
	float m_timer3 = 0.0f;
};

