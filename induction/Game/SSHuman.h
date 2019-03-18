#pragma once
class SSPlayer;
//ステージ選択専用
class SSHuman : public IGameObject
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Move();
	void Turn();
	//プレイヤーのアニメの変更
	void AnimeControll();
	//void PostRender(CRenderContext& rc);
	// プレイヤーの場所を返す関数。
	CVector3 GetPosition() const { 
		return m_position;
	}
private:
	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_skin = nullptr;
	SSPlayer* m_ssplayer;
	CVector3 m_position;
	CVector3 m_movespeed;
	CQuaternion m_qrot = CQuaternion::Identity;
	enum HumanAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_num
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	CFont m_font;
};

