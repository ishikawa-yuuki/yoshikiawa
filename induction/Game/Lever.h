#pragma once
class Player;
class Lever: public IGameObject
{
private:
	//ON��OFF��true��ON�̏��
	bool m_State = true;
public:
	Lever();
	~Lever();
	bool Start();
	void Update();
	void Range();
	void SetPosition( const CVector3& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	//Lever�̏��true�Ȃ�ON�̏��
	bool IsStateLever()const
	{
		return m_State;
	}
	void SetLeverTime(const int& num) {
		m_num = num;
	};
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	Player*m_player;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_scale = CVector3::Zero;
	enum LeverAnimationClip {
		enAnimationClip_OFF,
		enAnimationClip_ON,
		enAnimationClip_num
	};
	//�A�j���[�V�����N���b�v�l�ߍ��킹
	CAnimationClip m_animClip[enAnimationClip_num];
	float m_timer = 0.0f;
   //����
	int m_num = 0;
	float m_time = 0.0f;
	float m_volume = 0;
};

