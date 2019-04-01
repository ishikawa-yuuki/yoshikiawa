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
	DeleteGO(m_skinModelRender);//Queryになるかも
	if (m_effect != nullptr) {
		DeleteGO(m_effect);
	}

	if (m_ptLight != nullptr) {
		DeleteGO(m_ptLight);
	}

	if (m_directionLig != nullptr) {
		DeleteGO(m_directionLig);
	}
}

bool Light_Object::Start()
{
	m_player = FindGO<Player>("Player");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/LightObject/lanthanum.cmo");
	m_skinModelRender->SetScale({ 2.0f,2.0f,2.0f });
	m_skinModelRender->SetPosition(m_position);

	//法線マップをロード。
	//今は使えなさそう。消しても問題ではない
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
	if (!m_isLightOn) {
		if (m_player->GetColor() == 0
			&&diff.LengthSq() < 100.0f*100.0f) {
			m_isLightOn = true;
			housenlight();
			//InitPointLight();
			//Dirlight();使わない
			m_effect = NewGO<prefab::CEffect>(0);
			m_effect->Play(L"effect/spotlight.efk");
			m_effect->SetScale({ 4.0f, 4.0f, 4.0f });
			m_effect->SetPosition(m_position);
		}
	}
	else {
		if (m_player->GetColor() == 1
			&& diff.LengthSq() < 100.0f*100.0f) {
			m_isLightOn = false;
			DeleteGO(m_effect);
		}
	}
}

void Light_Object::InitPointLight()
{
	m_ptLight = NewGO<prefab::CPointLight>(0);
	//m_position.y = 100.0f;
	m_position.y += 1.0f;
	m_ptLight->SetPosition(m_position);//位置決め
	CVector3 color = { 10.0f,10.0f,0.0f,};
	m_ptLight->SetColor(color);//色決め
	CVector3 attn = CVector3::Zero;
	attn.x = 60.0f;//光の影響範囲距離
	attn.y = 10.0f;//光の減衰
	m_ptLight->SetAttn(attn);//影響範囲と減衰の強さ
}

void Light_Object::Dirlight()

{
	//ディレクションライト
	//太陽光のようなライトでゲーム全体を包むような光を放つ
	//今のところ使わない
	m_lightDir.Set(0.707f, -0.707f, 0.0f);
	m_lig = NewGO<prefab::CDirectionLight>(0);
	//ライトの方向を設定。
	m_lig->SetDirection(m_lightDir);
	//ライトの色を設定。
	m_lig->SetColor({ 300.5f, 300.5f, 300.5f, 1.0f });

}

void Light_Object::housenlight()
{
	//わからんけど画像を読み込んで
	//その画像に色を足している感じがする。
	//SRVはシェーダーリソースビューの略　スペキュラは鏡面反射光の事

	int materialID = 1;
	//マテリアルIDを設定
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