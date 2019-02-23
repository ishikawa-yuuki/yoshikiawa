#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"

class Player;
class Light_Object : public IGameObject
{
public:
	Light_Object();
	~Light_Object();
	bool Start();
	void Update();
	void InitPointLight();
	void Dirlight();
	void housenlight();
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = { 0.0f,-70.0f,-3000.0f };//レベルデザインで設計するのでとりあえず仮
	Player* m_player;
	bool m_isLightOn = false;
	prefab::CDirectionLight* m_lig;			//ライト。
	CVector3 m_lightDir;					//ライトの方向。
	prefab::CDirectionLight* m_directionLig = nullptr;
	//housenlight()で使う。
	CShaderResourceView m_normalMapSRV;
	CShaderResourceView m_specularMapSRV;
	CShaderResourceView m_lnormalMapSRV;
	CShaderResourceView m_lspecularMapSRV;
	//スポットライト用のeffect
	prefab::CEffect* m_effect = nullptr;
	//ポイントライトを生成
	prefab::CPointLight* m_ptLight = nullptr;
};

