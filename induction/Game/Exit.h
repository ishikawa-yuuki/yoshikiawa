#pragma once
class Human;
class Exit : public IGameObject
{
public:
	Exit();
	~Exit();
	bool Start();
	void Update();
	CVector3 SetPosition(const CVector3& pos)
	{
		m_position = pos;
		return m_position;
	}
	CQuaternion SetQrot(const CQuaternion& qrot)
	{

		m_qrot = qrot;
		return m_qrot;
	}
	CVector3 SetScale(const CVector3& scale)
	{
		m_scale = scale;
		return m_scale;
	}
	CVector3 GetPosition()const{
		return m_position;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_qrot = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One;

	Human* m_human;
};

