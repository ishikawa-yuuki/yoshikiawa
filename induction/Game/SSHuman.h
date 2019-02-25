#pragma once
class SSPlayer;
class SSHuman : public IGameObject//�X�e�[�W�I���p
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Move();
	void Turn();
	void AnimeControll();//�v���C���[�̃A�j���̕ύX
	void PostRender(CRenderContext& rc);
	CVector3 GetPosition() const { // �v���C���[�̏ꏊ��Ԃ��֐��B
		return m_position;
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;//�X�L�����f�������_���[
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

