#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include "Game.h"
#include "Stage_Select.h"
#include "Help.h"
#include "Credit.h"
#include "TitleGround.h"
#include "Human.h"
#include "Player.h"
#include "GameCamera.h"
Title::Title()
{
}


Title::~Title()
{
	//DeleteGO(m_spriteRender);
	DeleteGO(m_arrow);
	DeleteGO(m_bgm);
	DeleteGO(m_player);
	DeleteGO(m_human);
	DeleteGO(m_titleground);
	DeleteGO(m_gamecamera);
	//DeleteGO(m_ptLight);
	//for (auto menu : m_menuList) {
	//	DeleteGO(menu);
	//}
	//DeleteGO(m_pressstart);
	DeleteGO(m_sky);
}

bool Title::Start()
{
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/title/title.dds",1280.0f,720.0f);
	//m_spriteRender->SetMulColor(m_transparent);
	//m_pressstart = NewGO<prefab::CSpriteRender>(0);
	//m_pressstart->Init(L"sprite/title/pressstart.dds", 1280.0f, 720.0f);
	//m_pressstart->SetMulColor(m_transparent);
	/*m_menuList.push_back(NewGO<prefab::CSpriteRender>(0));
	m_menuList[0]->Init(L"sprite/title/start.dds", 1280.0f, 720.0f);
	m_menuList.push_back(NewGO<prefab::CSpriteRender>(0));
	m_menuList[1]->Init(L"sprite/title/manual.dds", 1280.0f, 720.0f);
	m_menuList.push_back(NewGO<prefab::CSpriteRender>(0));
	m_menuList[2]->Init(L"sprite/title/credit.dds", 1280.0f, 720.0f);
	for (auto menu : m_menuList) {
		menu->SetMulColor(m_transparent);
	}	*/
	
	m_arrow = NewGO<prefab::CSpriteRender>(0);
	m_arrow->Init(L"sprite/arrow.dds", 32.0f, 32.0f);
	m_arrow->SetMulColor(m_transparent);
	m_bgm = NewGO<prefab::CSoundSource>(0);
	m_bgm->Init(L"sound/kari.wav");
	m_bgm->Play(true);
	m_level.Init(L"level/title/title.tkl", [&](LevelObjectData & objdata) {
		if (objdata.EqualObjectName(L"titleground")) {
			return true;
		}
		//Human�̍��W���擾
		else if (objdata.EqualObjectName(L"Human")) {
		/*	m_human = NewGO<Human>(0, "Human");
			m_human->SetPosition(objdata.position);
			m_human->SetRotation(objdata.rotation);*/
			m_cameratargetpos = objdata.position;
			m_cameratargetpos.x = 0.0f;
			m_cameratargetpos.z = 0.0f;
			return true;
		}
		//Player�𐶐�
		else if (objdata.EqualObjectName(L"player")) {
			m_player = NewGO<Player>(0, "Player");
			m_player->SetPosition(objdata.position);
			m_playerposition = objdata.position;
			return true;
		}
		return true;
		});
	m_playerposition.y = m_cameratargetpos.y;
	m_titleground = NewGO<TitleGround>(0, "TitleGround");
	m_human = NewGO<Human>(0, "Human");
	m_human->SetPosition(CVector3(00.0f,0.0f,00.0f));
	m_gamecamera = NewGO<GameCamera>(0, "GameCamera");
	shadow::DirectionShadowMap().Disable();
	//���������ӂ���
	LightManager().SetAmbientLight({ 0.01f, 0.01f, 0.01f });
	//�S���ʃV���h�E��L���ɂ���
	shadow::OminiDirectionShadowMap().Enable();
	//�V�[���̖��邳�𗎂Ƃ��B
	postEffect::Tonemap().SetLuminance(0.1f);
	//m_ptLight = NewGO<prefab::CPointLight>(0);
	//CVector3 pointlightpos = m_human->GetPosition();
	//pointlightpos.y += 100.0f;
	//m_ptLight->SetPosition(pointlightpos);//�ʒu����
	//CVector3 color = { 0.01f,0.01f,0.01f };
	//m_ptLight->SetColor(color);//�F����
	//attn.x = 700.0f;
	//attn.y = 5.0f;
	//m_ptLight->SetAttn(attn);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_sky = NewGO<prefab::CSky>(0, "Sky");
	//m_sky->SetSkyCubeMapFilePath(L"sprite/sky.dds");
	m_sky->SetScale({ 5000.0f,5000.0f,5000.0f });
	m_sky->SetEmissionColor({ 0.05f, 0.05f, 0.05f });
	shadow::OminiDirectionShadowMap().SetLightPosition(m_player->GetPosition());
	//�S���ʃV���h�E�̉e���͈͂�ݒ肷��B
	shadow::OminiDirectionShadowMap().SetDistanceAffectedByLight(1000);
	return true;
}


void Title::Update()
{
	CVector3 pos = m_player->GetPosition();
	//pos.y += 100;
	shadow::OminiDirectionShadowMap().SetLightPosition(pos);
	switch (m_state) {
	case enState_GameStart:
		GameStart();
		break;
	case enState_SelectMenu:
		SelectMenu();
		break;
	case enState_TransScene:
		TransScene();
		break;
	case enState_TransStageSelect:
		TransStageSelect();
		break;
	}
}

void Title::GameStart()
{
	//pressstart�̕\���ɂ���
	if (m_alphastart > 1.0f && m_isaddalphastart) {
		m_isaddalphastart = false;
	}
	else if (m_alphastart <= 0.2f && !m_isaddalphastart) {
		m_isaddalphastart = true;
	}
	if (m_ispressstartbutton) {
		if (m_isaddalphastart) {
			m_alphastart += 13.0f * GameTime().GetFrameDeltaTime();
		}
		else {
			m_alphastart -= 13.0f * GameTime().GetFrameDeltaTime();
		}
	}
	else {
		if (m_isaddalphastart) {
			m_alphastart += 1.5f * GameTime().GetFrameDeltaTime();
		}
		else {
			m_alphastart -= 1.5f * GameTime().GetFrameDeltaTime();
		}
	}
	//�X�^�[�g�{�^�������ꂽ��
	if (m_ispressstartbutton) {
		//���l��0�܂ŉ�����
		if (m_alphatitle > 0.0001f) {
			m_alphatitle -= GameTime().GetFrameDeltaTime();
		}
		//���l��0�܂ŉ�����(�^�C�g�����\������ĂȂ�)�ꍇ�A
		//���j���[��ʂɈڍs
		else{
			m_alphatitle = 0.0f;
			m_alphastart = 0.0f;
			m_state = enState_SelectMenu;
		}
	}
	else {
		if (m_alphatitle < 1.0f) {
			m_alphatitle += GameTime().GetFrameDeltaTime();
			if (m_alphatitle >= 1.0f) {
				m_alphatitle = 1.0f;
			}
		}
		else {
			if (Pad(0).IsPressAnyKey()) {
				prefab::CSoundSource* ss;
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/select.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);
				m_ispressstartbutton = true;
			}
		}

	}
	
	//m_spriteRender->SetMulColor({ 1.0f,1.0f,1.0f,m_alphatitle });
	//m_pressstart->SetMulColor({ 1.0f,1.0f,1.0f,m_alphastart });
}

void Title::SelectMenu()
{
	if (m_ispressAbutton) {
		if (m_alphamenu > 0.2f) {
			m_alphamenu -= GameTime().GetFrameDeltaTime() / 2;
			m_alphamenu2 -= GameTime().GetFrameDeltaTime();
		}
		else {
			m_alphamenu = 0.2f;
			m_alphamenu2;
			if (m_select == enState_StageSelect) {
				m_state = enState_TransStageSelect;
				m_istransstageselect = true;
			}
			else {
				m_state = enState_TransScene;
				m_isWaitFadeout = true;
				m_fade->StartFadeOut();
			}
		}
		
	}
	else {
		if (m_alphamenu < 0.5f) {
			m_alphamenu += GameTime().GetFrameDeltaTime() / 2;
			m_alphamenu2 += GameTime().GetFrameDeltaTime();
			if (m_alphamenu >= 0.5f) {
				m_alphamenu = 0.5f;
				m_alphamenu2 = 1.0f;

			}
		}
		else {
			Choice();
		}
	}
	/*for (int i = 0; i < m_menuList.size(); i++) {
		if (i == m_select) {
			m_menuList[i]->SetMulColor({ 1.0f,1.0f,1.0f,m_alphamenu });
		}
		else {
			m_menuList[i]->SetMulColor({ 1.0f,1.0f,1.0f,m_alphamenu / 2.0f });
		}
	}*/
}
void Title::Choice()
{
	prefab::CSoundSource* ss;
	const float arrow_move = -120.0f;//�|�̈ړ�����
	if (Pad(0).IsTrigger(enButtonDown)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		m_select = Select(m_select + 1);
		if (m_select > enState_Last) {
			m_select = enState_Last;
		}
		else {
			m_arrowPos.y += arrow_move;
		}
	}
	else if (Pad(0).IsTrigger(enButtonUp)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/select.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		m_select = Select(m_select - 1);
		if (m_select < enState_Fist) {
			m_select = enState_Fist;
		}
		else {
			m_arrowPos.y -= arrow_move;
		}
	}
	else if (Pad(0).IsTrigger(enButtonA)) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/decision1.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);
		m_ispressAbutton = true;
	}

	m_arrow->SetPosition(m_arrowPos);
}

void Title::TransScene()
{
	if (m_isWaitFadeout) {
	if (!m_fade->IsFade()) {
		if (m_select == enState_Manual) {
			NewGO<Help>(0, "Help");
			DeleteGO(this);
		}
		else if (m_select == enState_Credit) {
			NewGO<Credit>(0, "Credit");
			DeleteGO(this);
		}
	}
}
}

void Title::TransStageSelect()
{
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Stage_Select>(0, "Stage_Select");
			DeleteGO(this);
		}
	}
	else {
		m_timer += GameTime().GetFrameDeltaTime();
		if (m_timer >= m_time2) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
		else if (m_timer >= m_time) {
			m_isstop = true;
		}
		
	}
}

void Title::PostRender(CRenderContext& renderContext)
{
	if (m_state == enState_GameStart) {
		m_font.Begin(renderContext);
		wchar_t aaa2[20];
		swprintf(aaa2, L"INDUCTION");
		m_font.Draw(aaa2, { -300.0f,320.0f }, CVector4::White, 0.0f, 2.5f);
		wchar_t aaa[20];
		swprintf(aaa, L"PRESS ANYKEY");
		m_font.Draw(aaa, { 0.0f,-280.0f }, { m_alphastart,m_alphastart,m_alphastart,1.0f }, 0.0f,1.3f);
		m_font.End(renderContext);
	}
	else if (m_state == enState_SelectMenu) {
		std::vector<const wchar_t*> List;
		List.push_back(L"START");
		List.push_back(L"MANUAL");
		List.push_back(L"CREDIT");
		m_font.Begin(renderContext);
		CVector2 pos = { 300.0f,-50.0f };
		const float PLUS = -90.0f;
		for (int i = 0; i < enState_Last; i++) {
			if (i + 1 == m_select) {
				m_font.Draw(List[i], pos, { m_alphamenu2,m_alphamenu2,m_alphamenu2,1.0f }, 0.0f, 1.3f, { 0.0f,1.0f });
			}
			else {
				m_font.Draw(List[i], pos, { m_alphamenu,m_alphamenu,m_alphamenu,1.0f }, 0.0f, 1.3f, { 0.0f,1.0f });
			}
			pos.y += PLUS;
		}
		m_font.End(renderContext);
	}
}