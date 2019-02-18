#pragma once
class Player;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	void Move();
	void Turn();
	void AnimeControll();//�v���C���[�̃A�j���̕ύX
	void isDead();
	/*void PostRender(CRenderContext& rc);*/
	CVector3 GetPosition() const{
		return m_position;
	}
	//���񂾂��ǂ�����Ԃ��֐�
	bool GetisDead()const {
		return m_isDead;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;//�X�L�����f�������_���[
	Player* m_player;
	CVector3 m_position;
	CVector3 m_movespeed;
	CQuaternion m_qrot = CQuaternion::Identity;
	enum HumanAnimationClip {
		enAnimationClip_idle,
		enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_jump,
		enAnimationClip_damage,
		enAnimationClip_clear,
		enAnimationClip_KneelDown,
		enAnimationClip_num
	};
	CAnimationClip m_animClip[enAnimationClip_num];
	CFont m_font;
	bool m_isDead = false;
};

