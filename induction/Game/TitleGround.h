#pragma once
class Title;
class TitleGround :public IGameObject
{
public:
	TitleGround();
	~TitleGround();
	bool Start();
	void Update();
	//À•W‚ğİ’è
	void SetPosition(CVector3 const& pos)
	{
		m_position = pos;
	}
	//‰ñ“]‘¬“x(ˆê•bŠÔ‚Ì)‚ğæ“¾
	float GetSpeed()
	{
		return m_adddegree;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_skinModelRender2 = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One * 1.0f;
	CQuaternion m_rotation = CQuaternion::Identity, m_rotation2 = CQuaternion::Identity;
	const float m_adddegree = -0.20f * 40.0f;
	float m_degree = 0.0f, m_degree2 = 0.0f;
	Title* m_title;
};

