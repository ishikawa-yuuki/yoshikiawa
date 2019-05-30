#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/light/tkPointLight.h"

class Player;
class Human;
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
	//ポジションをレベルで入れる。
	void SetPosition(const CVector3& pos) 
	{
		m_position = pos;
	}
	//スケールをレベルで入れる。
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//ローテーションをレベルに入れる。
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//名前の通りライトが大きくなる
	bool Biglight()
	{
		m_biglight = true;
		return  m_biglight;
	}
	//これが呼ばれたら少しだけ仕様が違うライトになる
	bool Lastlight()
	{
		m_lastlight = true;
		return m_lastlight;
	}
	//これが呼ばれたら初期状態のライトはonになる
	bool SetLight()
	{
		m_isLightOn = true;
		return m_isLightOn;
	}
	//今のポジションの値を返す。
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool GetLightOn()const
	{
		return m_isLightOn;
	}
	CVector4 GetPointLightAttn() const
	{
		return m_ptLight->GetAttn();
	}
	prefab::CPointLight* GetPointLight() const
	{
		return m_ptLight;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	//レベルデザインで設計するのでとりあえず仮
	CVector3 m_position = { 0.0f,-70.0f,-3000.0f };
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rot = CQuaternion::Identity;
	Player* m_player;
	Human* m_human;
	//ライトがオンなのかどうか
	bool m_isLightOn = false;
	//ライトが大きいかどうか
	bool m_biglight = false;
	//最後のステージで配置されるランタンかどうか
	bool m_lastlight = false;
	//ライト。
	prefab::CDirectionLight* m_lig = nullptr;
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
	//ライトの光の増減、減衰率を操作。
	CVector3 attn = CVector3::Zero;
};

