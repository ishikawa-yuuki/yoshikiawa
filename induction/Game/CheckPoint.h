#pragma once
class CheckPoint:public IGameObject
{
public:
	CheckPoint();
	~CheckPoint();
	bool Start();
	void Update();
	//À•W‚ğİ’è
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//À•W‚ğæ“¾
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//’Ê‰ßÏ‚İ‚©‚Ç‚¤‚©‚ğæ“¾
	bool GetisPass() const
	{
		return m_pass;
	}
	//’Ê‰ß‚µ‚½‚©‚Ç‚¤‚©‚ğİ’è
	void SetPass(bool pass) 
	{
		m_pass = pass;
	}

private:
	bool m_pass = false;
	CVector3 m_position = CVector3::Zero;
};

