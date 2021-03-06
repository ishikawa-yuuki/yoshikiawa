#pragma once
class Title;
class TitleGround :public IGameObject
{
public:
	TitleGround();
	~TitleGround();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(CVector3 const& pos)
	{
		m_position = pos;
	}
	//回転速度(一秒間の)を取得
	float GetSpeed()
	{
		return m_adddegree;
	}
	//回転速度(一秒間の)を取得
	float GetCutSpeed()
	{
		return m_cutdegree;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_skinModelRender2 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One * 1.0f;
	CQuaternion m_rotation = CQuaternion::Identity, m_rotation2 = CQuaternion::Identity;
	const float m_adddegree = -0.20f * 40.0f;
	const float m_cutdegree = -0.5f * 40.0f;
	float m_degree = 0.0f, m_degree2 = 0.0f;
	Title* m_title;
	prefab::CPointLight* m_ptLight = nullptr;
	const CVector3 m_pointLigDefaultAttn = { 10000.0f, 10.0f, 0.0f };
	CVector3 m_lightposBase = { 15.288 , 2772.341 , 2458.6 };
};

