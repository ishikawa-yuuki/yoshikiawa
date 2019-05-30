#include "stdafx.h"
#include "Light_Object.h"
#include "Player.h"
#include "Human.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

Light_Object::Light_Object()
{
}


Light_Object::~Light_Object()
{
	DeleteGO(m_skinModelRender);//Query�ɂȂ邩��
	if (m_effect != nullptr) {
		DeleteGO(m_effect);
	}

	if (m_ptLight != nullptr) {
		DeleteGO(m_ptLight);
	}

	if (m_directionLig != nullptr) {
		DeleteGO(m_directionLig);
	}
	if (m_lig != nullptr) {
		DeleteGO(m_lig);
	}
}

bool Light_Object::Start()
{
	m_player = FindGO<Player>("Player");
	m_human = FindGO<Human>("Human");
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/LightObject/lanthanum.cmo");
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelRender->SetScale({ 2.0f,2.0f,2.0f });
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rot);

	if (m_isLightOn) {
		m_effect = NewGO<prefab::CEffect>(0);
		m_effect->Play(L"effect/spotlight.efk");
		m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
		CVector3 m_effectPos = m_position;
		m_effectPos.y = m_position.y - 150.0f;
		m_effect->SetPosition(m_effectPos);
		
		//m_human->isLantanon();
	//	housenlight();
		InitPointLight();
		//Dirlight();�g��Ȃ�
	}
	//�@���}�b�v�����[�h�B
	//���͎g���Ȃ������B�����Ă����ł͂Ȃ�
	//m_normalMapSRV.CreateFromDDSTextureFromFile(L"modelData/LightObject/glass05_N.dds");
	//m_specularMapSRV.CreateFromDDSTextureFromFile(L"modelData/LightObject/glass05_S.dds");
	//m_lnormalMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	//m_lspecularMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	return true;
}

void Light_Object::Update()
{
	CVector3 diff;

	diff = m_player->GetPosition() - m_position;
	diff.y = 0.0f;
	if (!m_isLightOn) {
		if (m_player->GetColor() == 0
			&&diff.LengthSq() < 100.0f*100.0f
			||m_isLightOn) {
			m_isLightOn = true;
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Play(L"effect/spotlight.efk");
			m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
			m_effect->SetPosition(m_position);
			//m_human->isLantanon();
		//	housenlight();
			InitPointLight();
			//Dirlight();�g��Ȃ�
		}
	}
	else{
		if (m_player->GetColor() == 1
			&& diff.LengthSq() < 450.0f * 450.0f) {
			//attn�̓����o�ł���������
			attn.x = attn.x - 30.0f;
			if (attn.x < 300.0f) {
				if (m_effect != nullptr) {
					DeleteGO(m_effect);
					m_effect = nullptr;
				}
				attn.x = 0.0f;//���̉e���͈͋���
				attn.y = 10.0f;//���̌���
				m_isLightOn = false;
			}
			m_ptLight->SetAttn(attn);
		}
	}
	//��������Lastlight�̃R�[�h������
	if (m_lastlight) {
		if (m_human->GetisLastStageClear()
			&&!m_isLightOn) {
			static float timer = 0.0f;
			timer += 1 * GameTime().GetFrameDeltaTime();
			if (m_lastlightnum == flont) {
				m_isLightOn = true;
				m_effect = NewGO<prefab::CEffect>(0);
				m_effect->Play(L"effect/spotlight.efk");
				m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
				InitPointLight();
				m_effect->SetPosition(m_position);
			}
			else if (m_lastlightnum == center) {
				if (timer > 0.8f) {
					m_isLightOn = true;
					m_effect = NewGO<prefab::CEffect>(0);
					m_effect->Play(L"effect/spotlight.efk");
					m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
					InitPointLight();
					m_effect->SetPosition(m_position);
				}
			}
			else if (m_lastlightnum == back) {
				if (timer > 1.6f) {
					m_isLightOn = true;
					m_effect = NewGO<prefab::CEffect>(0);
					m_effect->Play(L"effect/spotlight.efk");
					m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
					InitPointLight();
					m_effect->SetPosition(m_position);
				}
			}
		}
	}
}

void Light_Object::InitPointLight()
{
	m_ptLight = NewGO<prefab::CPointLight>(0);
	CVector3 pointlightpos = m_position;
	pointlightpos.y = 100.0f;
	m_ptLight->SetPosition(pointlightpos);//�ʒu����
	
	if (m_lastlight) {
		CVector3 color = { 5000.0f,5000.0f,5000.0f, };
		m_ptLight->SetColor(color);//�F����
		attn.x = 1000.0f;//���̉e���͈͋���
		attn.y = 5.0f;//���̌���
		m_ptLight->SetAttn(attn);//�e���͈͂ƌ����̋���
	}
	else if (m_biglight) {
		CVector3 color = { 20000.0f,20000.0f,25000.0f, };
		m_ptLight->SetColor(color);
		attn.x = 1200.0f;
		attn.y = 2.0f;
		m_ptLight->SetAttn(attn);
	}
	else {
		CVector3 color = { 2000.0f,2000.0f,2500.0f, };
		m_ptLight->SetColor(color);
		attn.x = 1000.0f;
		attn.y = 10.0f;
		m_ptLight->SetAttn(attn);
	}
}

void Light_Object::Dirlight()

{
	//�f�B���N�V�������C�g
	//���z���̂悤�ȃ��C�g�ŃQ�[���S�̂��ނ悤�Ȍ������
	//���̂Ƃ���g��Ȃ�
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection(m_lightDir);
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });

}

void Light_Object::housenlight()
{
	//�킩��񂯂ǉ摜��ǂݍ����
	//���̉摜�ɐF�𑫂��Ă��銴��������B
	//SRV�̓V�F�[�_�[���\�[�X�r���[�̗��@�X�y�L�����͋��ʔ��ˌ��̎�

	//�����o�O�̌�
	int materialID = 1;
	//�}�e���A��ID��ݒ�
	m_skinModelRender->FindMaterial([&](auto material) {
		material->SetMaterialID(materialID);
		if (material->EqualMaterialName(L"glass05")) {
			material->SetNormalMap(m_normalMapSRV.GetBody());
			material->SetSpecularMap(m_specularMapSRV.GetBody());
		}
	});
	m_directionLig = NewGO<prefab::CDirectionLight>(0);
	m_directionLig->SetColor({ 15.5f,15.5f,1.5f,1.0f });
	m_directionLig->SetLightingMaterialIDGroup(1 << materialID);
}