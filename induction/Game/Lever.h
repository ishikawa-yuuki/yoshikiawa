#pragma once
class Player;
class Lever: public IGameObject
{
private:
	//ONかOFFかtrueはONの状態
	bool m_State = true;
public:
	Lever();
	~Lever();
	bool Start();
	void Update();
	void SetPosition( const CVector3& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//Leverの状態trueならONの状態
	bool IsStateLever()const
	{
		return m_State;
	}
private:
	//
	int n = 0;
	prefab::CSkinModelRender* m_skin = nullptr;
	Player*m_player;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	enum LeverAnimationClip {
		enAnimationClip_OFF,
		enAnimationClip_ON,
		enAnimationClip_num
	};
	//アニメーションクリップ詰め合わせ
	CAnimationClip m_animClip[enAnimationClip_num];
	float m_timer = 0.0f;
};

