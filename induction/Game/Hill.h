#pragma once
//蛭って英語ではLeechって言うらしいのですが
//Hillって名前で作ってしまいました…
class Human;
class Hill : public IGameObject
{
public:
	Hill();
	~Hill();
	bool Start();
	void Update();
	void Move();
	void Stop();
	void Turn();
	void Kill();
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
	void SetKill(const int& num)
	{
		m_num = num;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_parallel = CVector3::Zero;
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rotation = CQuaternion::Identity;
	enum HillAnimationClip {
		enAnimationClip_move,
		enAnimationClip_num
	};
	enum State {
		enState_Move,
		enState_Stop
	};
	State m_state = enState_Stop;
	CAnimationClip m_animeClip[enAnimationClip_num];
	float m_timer = 0.0f;
	int m_num = 0;
	bool kill = false;
	Human* m_human = nullptr;
};

