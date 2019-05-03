#pragma once
//•g‚Á‚Ä‰pŒê‚Å‚ÍLeech‚Á‚ÄŒ¾‚¤‚ç‚µ‚¢‚Ì‚Å‚·‚ª
//Hill‚Á‚Ä–¼‘O‚Åì‚Á‚Ä‚µ‚Ü‚¢‚Ü‚µ‚½c
class Human;
class Hill : public IGameObject
{
public:
	Hill();
	~Hill();
	bool Start();
	void Update();
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	void SetRotation(const CQuaternion& qrot)
	{
		m_rotation = qrot;
	}
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation = CQuaternion::Identity;
	enum HillAnimationClip {
		enAnimationClip_move,
		enAnimationClip_num
	};
	CAnimationClip m_animeClip[enAnimationClip_num];
	int m_timer = 0;
	Human* m_human;
};

