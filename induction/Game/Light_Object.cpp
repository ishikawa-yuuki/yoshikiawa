#include "stdafx.h"
#include "Light_Object.h"
#include "Player.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "tkEngine/light/tkPointLight.h"

Light_Object::Light_Object()
{
}


Light_Object::~Light_Object()
{
	DeleteGO(m_skinModelRender);//Query�ɂȂ邩��
	DeleteGO(m_effect);
	DeleteGO(m_ptLight);
	if (m_directionLig != nullptr) {
		DeleteGO(m_directionLig);
	}
}

bool Light_Object::Start()
{
	m_player = FindGO<Player>("Player");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/lanthanum.cmo");
	m_skinModelRender->SetScale({ 2.0f,2.0f,2.0f });
	m_skinModelRender->SetPosition(m_position);

	//�@���}�b�v�����[�h�B
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"modelData/glass04.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"modelData/glass04.dds");
	//m_lnormalMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	//m_lspecularMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	return true;
}

void Light_Object::Update()
{
	CVector3 diff;

	diff = m_player->GetPosition() - m_position;
	if (!m_isLightOn) {
		if (diff.LengthSq() < 500.0f*500.0f) {
			m_isLightOn = true;
			housenlight();
			InitPointLight();
			//Dirlight();�g��Ȃ�
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Play(L"effect/spotlight.efk");//�X�|�b�g���C�g�̃G�t�F�N�g�B������ŋ����������Ƃ��Ɏg���B
			m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
			m_effect->SetPosition(m_position);
		}
	}
}

void Light_Object::InitPointLight()
{
	m_ptLight = NewGO<prefab::CPointLight>(0);
	//m_position.y = 100.0f;
	m_position.y += 70.0f;
	m_ptLight->SetPosition(m_position);//�ʒu����
	CVector3 color = { 10.0f,10.0f,0.0f,};
	m_ptLight->SetColor(color);//�F����
	CVector3 attn = CVector3::Zero;
	attn.x = 600.0f;//���̉e���͈͋���
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
	//�����悭�킩��񂯂ǉ摜��ǂݍ����
	//���̉摜�ɐF�𑫂��Ă��銴��������B
	//SRV�̓V�F�[�_�[���\�[�X�r���[�̗��@�X�y�L�����͋��ʔ��ˌ��̎�
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
	m_directionLig->SetColor({ 20.5f,20.5f,1.5f,1.0f });
	m_directionLig->SetLightingMaterialIDGroup(1 << materialID);
}