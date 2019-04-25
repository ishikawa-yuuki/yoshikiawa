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

	if (m_isLightOn) {
		m_effect = NewGO<prefab::CEffect>(0);
		m_effect->Play(L"effect/spotlight.efk");
		m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
		m_effect->SetPosition(m_position);
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
	else {
		if (m_player->GetColor() == 1
			&& diff.LengthSq() < 100.0f*100.0f) {
			m_isLightOn = false;
			if (m_effect != nullptr) {
				DeleteGO(m_effect);
				m_effect = nullptr;
			}
			//attn�̓����o�ł���������
			CVector3 attn = CVector3::Zero;
			attn.x = 10.0f;//���̉e���͈͋���
			attn.y = 10.0f;//���̌���
			m_ptLight->SetAttn(attn);
		}
	}
}

void Light_Object::InitPointLight()
{
	m_ptLight = NewGO<prefab::CPointLight>(0);
	CVector3 pointlightpos = m_position;
	pointlightpos.y = 100.0f;
	m_ptLight->SetPosition(pointlightpos);//�ʒu����
	CVector3 color = { 2000.0f,2000.0f,2500.0f,};
	m_ptLight->SetColor(color);//�F����
	CVector3 attn = CVector3::Zero;
	attn.x = 2000.0f;//���̉e���͈͋���
	attn.y = 10.0f;//���̌���
	m_ptLight->SetAttn(attn);//�e���͈͂ƌ����̋���
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