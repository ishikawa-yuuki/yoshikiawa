#include "stdafx.h"
#include "Credit.h"
#include "Fade.h"
#include "Title.h"

Credit::Credit()
{
}


Credit::~Credit()
{
	DeleteGO(m_sky);
	DeleteGO(m_bgm);
}
bool Credit::Start()
{
	shadow::DirectionShadowMap().Disable();
	//環境光をおふっふ
	LightManager().SetAmbientLight({ 0.05f, 0.05f, 0.05f });
	//全方位シャドウを有効にする
	shadow::OminiDirectionShadowMap().Enable();
	//シーンの明るさを落とす。
	postEffect::Tonemap().SetLuminance(0.2f);
	MainCamera().SetPosition({ 0.0f, 0.0f, 0.0f });
	MainCamera().SetTarget({ -100.0f,-100.0f,-100.0f });
	MainCamera().SetFar(10000.0f);
	MainCamera().SetNear(1.0f);
	MainCamera().Update();
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_sky = NewGO<prefab::CSky>(0, "Sky");
	//m_sky->SetSkyCubeMapFilePath(L"sprite/sky.dds");
	m_sky->SetScale({ 500.0f,500.0f,500.0f });
	m_sky->SetEmissionColor({ 0.05f, 0.05f, 0.05f });
	m_characterList[0] = L"制作";
	m_characterList[1] = L"メインプログラマー\n\n　 Yoshinaga　Satoshi";
	m_characterList[2] = L"サブプログラマー\n\n 　Ishikawa　Yuuki";
	m_characterList[3] = L"サブプログラマー\n\n 　Komura　Athushi";
	m_characterList[4] = L"開発環境";
	m_characterList[5] = L"C++\n\nVisual Studio2017\n\nVisual Studio2019";
	m_characterList[6] = L"使用ツール";
	m_characterList[7] = L"3DSMAX\n\nEffekseer\n\nFireAlpaca";
	m_characterList[8] = L"Presented by TeamBikklers";
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/credit.wav");
	m_bgm->SetVolume(2.0f);
	m_bgm->Play(false);
	return true;
}
void Credit::Update()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Title>(0,"Title");
			DeleteGO(this);
		}
	}
	else if (m_transscene || Pad(0).IsTrigger(enButtonB)) {
		m_isWaitFadeout = true;
		m_fade->StartFadeOut();
	}
}

void Credit::PostRender(CRenderContext& renderContext) //何かを調べるためのポストレンダラ、今は移動スピード。
{
	
	const float Timer2 = 2.4f;
	const float Timer3 = 12.0f;
	const float Scale = 1.6f;
	const float Speed = 3.0f / 5.7f;
	CVector4 White = CVector4::White;
	if (m_owari) {
		m_timer3 += GameTime().GetFrameDeltaTime();
		if (m_timer3 >= Timer3) {
			m_transscene = true;
		}
	}
	else if (!m_owari) {
		if (m_stop) {
			m_timer2 += GameTime().GetFrameDeltaTime() * Speed;
			if (m_timer2 >= Timer2) {
				m_stop = false;
				m_timer2 = 0.0f;
			}
		}
		else {
			if (m_addtimer) {
				m_timer += GameTime().GetFrameDeltaTime() * Speed;
			}
			else {
				m_timer -= GameTime().GetFrameDeltaTime() * Speed;
			}

			if (m_timer >= 1.0f && m_addtimer) {
				m_timer = 1.0f;
				m_addtimer = false;
				m_stop = true;
				if (m_number + 1 == m_characterList.size()) {
					m_owari = true;
					return;
				}
			}
			else if (m_timer <= 0.2f && !m_addtimer) {
				m_timer = 0.2f;
				m_addtimer = true;
				m_number += 1;
			}

		}
	}
	White = White * m_timer;
	White.w = 1.0f;
	m_font.Begin(renderContext);
	m_font.Draw(m_characterList[m_number], { 0.0f,100.0f }, White, 0.0f, Scale);
	m_font.End(renderContext);
}