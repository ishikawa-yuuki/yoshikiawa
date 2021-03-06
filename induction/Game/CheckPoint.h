#pragma once
class CheckPoint:public IGameObject
{
public:
	CheckPoint();
	~CheckPoint();
	bool Start();
	void Update();
	//座標を設定
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//座標を取得
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//通過済みかどうかを取得
	bool GetisPass() const
	{
		return m_pass;
	}
	//通過したかどうかを設定
	void SetPass(bool pass) 
	{
		m_pass = pass;
	}

private:
	bool m_pass = false;
	CVector3 m_position = CVector3::Zero;
};

