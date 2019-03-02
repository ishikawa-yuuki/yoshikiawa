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
	void SetPosition(const CVector3& pos) 
	{
		m_position = pos;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	//レベルデザインで設計するのでとりあえず仮
	CVector3 m_position = { 0.0f,-70.0f,-3000.0f };
	Player* m_player;
	bool m_isLightOn = false;
	//ライト。
	prefab::CDirectionLight* m_lig;			
	//ライトの方向。
	CVector3 m_lightDir;					
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

