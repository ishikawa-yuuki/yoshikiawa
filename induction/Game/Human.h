#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
class Fade;
class Light_Object;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//�Q�[���ŏ��ɍs���֐��B
	void GameStartMove();
	//�Q�[�����̕��ʂ̓���������Ƃ��̊֐�
	void Move();
	void Turn();
	//�v���C���[�̃A�j���̕ύX
	void AnimeControll();
	//��������I�𔻒肷��
	void isDead();
	//�������̔���
	void Hanntei();
	//�N���A���ǂ���
	void isClear();

	/*void PostRender(CRenderContext& rc);*/

	//���݂̃|�W�V�����̒l��Ԃ��֐��B
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	//�Q�[���������I��������̊֐��B
	bool GetStartMove()const
	{
		return m_StartMoveFin;
	}

	//���񂾂��ǂ�����Ԃ��֐�
	bool GetisDead()const 
	{
		return m_isDead;
	}
	//�N���A�������ǂ�����Ԃ��֐�
	bool GetisClear()const
	{
		return m_Clear_one;
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
	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player;
	Game* m_game;
	Fade* m_fade;
	Light_Object* m_lightObject;
	CVector3 m_position = { 0.0f,0.0f,700.0f };
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
	//�A�j���[�V�����N���b�v�l�ߍ��킹
	CAnimationClip m_animClip[enAnimationClip_num];
	//���ׂ邽�߂̃t�H���g�A�����Ɏg������
	CFont m_font;
	//�������I���������Ԃ��B
	bool m_StartMoveFin = false;
	//���񂾂��ǂ���
	bool m_isDead = false;
	//�Q�[���I�[�o�[���ǂ���
	bool m_isGameOver = false;
	//��񂵂��E�������Ȃ��̂ŃX�g�b�p�[�B
	bool m_siboustop = false;
	//�Q�[���I�[�o�[����񂾂��o�������
	bool m_gameover_one = false;
	//�Q�[���N���A����񂾂��B
	bool m_Clear_one = false;
	//�Q�[���N���A�̗]�C�p
	float m_timer = 0;
};

