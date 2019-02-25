#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
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
	void isDead();//��������I�𔻒肷��
	void Hanntei();
	/*void PostRender(CRenderContext& rc);*/
	CVector3 GetPosition() const
	{
		return m_position;
	}
	//���񂾂��ǂ�����Ԃ��֐�
	bool GetisDead()const 
	{
		return m_isDead;
	}
	//�Q�[���I�[�o�[���ǂ����Ԃ��֐�
	bool GetisGameOver()const {
		return m_isGameOver;
	}
	//human��|���Ƃ��̊֐��Aenemy�Ƃ����g���Ǝv���܂��B
	void isKill() 
	{
		if (!m_isDead) {
			m_isDead = true;
		}
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;//�X�L�����f�������_���[
	Player* m_player;
	Game* m_game;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_Bedspeed = CVector3::Zero;
	CQuaternion m_qrot = CQuaternion::Identity;
	CCharacterController m_charaCon;
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
	CAnimationClip m_animClip[enAnimationClip_num];//�A�j���[�V�����N���b�v�l�ߍ��킹
	CFont m_font;//���ׂ邽�߂̃t�H���g�A�����Ɏg������
	bool m_isDead = false;//���񂾂��ǂ���
	bool m_isGameOver = false;//�Q�[���I�[�o�[���ǂ���
	bool m_siboustop = false;//��񂵂��E�������Ȃ��̂ŃX�g�b�p�[�B
};

