#pragma once
class SSPlayer;
//�X�e�[�W�I���p
class SSHuman : public IGameObject
{
public:
	SSHuman();
	~SSHuman();
	bool Start();
	void Update();
	void Move();
	void Turn();
	//�v���C���[�̃A�j���̕ύX
	void AnimeControll();
	//void PostRender(CRenderContext& rc);
	// �v���C���[�̏ꏊ��Ԃ��֐��B
	CVector3 GetPosition() const { 
		return m_position;
	}
private:
	//�X�L�����f�������_���[
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

