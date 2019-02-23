#pragma once
class SSPlayer;
class SSHuman : public IGameObject//ステージ選択専用
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Move();
	void Turn();
	void AnimeControll();//プレイヤーのアニメの変更
	void PostRender(CRenderContext& rc);
	CVector3 GetPosition() const { // プレイヤーの場所を返す関数。
		return m_position;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;//スキンモデルレンダラー
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

