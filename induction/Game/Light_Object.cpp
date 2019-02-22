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
}

bool Light_Object::Start()
{
	m_player = FindGO<Player>("Player");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/lanthanum.cmo");
	m_skinModelRender->SetScale({ 2.0f,2.0f,2.0f });
	m_skinModelRender->SetPosition(m_position);

	//�@���}�b�v�����[�h�B
	m_normalMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	m_specularMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	m_lnormalMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	m_lspecularMapSRV.CreateFromDDSTextureFromFile(L"modelData/.dds");
	return true;
}

void Light_Object::Update()
{
	CVector3 diff;
	diff = m_player->GetPosition() - m_position;
	if (!m_isLightOn) {
		if (diff.LengthSq() < 500.0f*500.0f) {
			m_isLightOn = true;
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
			m_directionLig->SetColor({ 10.5f,10.5f,1.5f,1.0f });
			m_directionLig->SetLightingMaterialIDGroup(1 << materialID);
		//	InitPointLight();
		//	Dirlight();
			
		}
	}
}

void Light_Object::InitPointLight()
{
	//�|�C���g���C�g�𐶐�
	prefab::CPointLight* ptLight = NewGO<prefab::CPointLight>(0);
	m_position.y = 100.0f;

	ptLight->SetPosition(m_position);//�ʒu����
	CVector3 color = { 255.0f,255.0f,0.0f,};
	ptLight->SetColor(color);//�F����
	CVector3 attn = CVector3::Zero;
	attn.x = 60.0f;//���̉e���͈͋���
	attn.y = 1.0f;//���̌���
	ptLight->SetAttn(attn);//�e���͈͂ƌ����̋���
}

void Light_Object::Dirlight()
{
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	m_lig->SetDirection(m_lightDir);
	//���C�g�̐F��ݒ�B
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });

}

void Light_Object::housenlight()
{
	
}