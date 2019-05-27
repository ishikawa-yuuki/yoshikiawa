#pragma once
#include "tkEngine/character/tkCharacterController.h"
class Player;
class Game;
class GameOver;
class Fade;
class MistEnemy;
class Light_Object;
class Light_Object2;
class Exit;
class Title;
class TitleGround;
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	//�Q�[���ŏ��ɍs���֐��B
	void GameStartMove();
	//�L�����̉�]
	void Turn();
	//Mistenemy�ɘA��Ă�����Ă���Ƃ��̏���
	void TakingMove();
	//LightObject���������Ƃ��̏���
	void Light_Move();
	//���̉��̑傫��
	void Range();
	//�v���C���[�̃A�j���̕ύX
	void AnimeControll();
	//��������I�𔻒肷��
	void isDead();
	//�������̔���
	void Hanntei();
	//�N���A���ǂ���
	void isClear();
	//�����^���Ƃ̋�����c��������
	void lanpos(CVector3 pos);
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
	//mistenemy���s����ς��邽�߂̃X�C�b�`�֐�
	bool GetismistEnemy()const {
		return mistflag;
	}
	//human��|���Ƃ��̊֐��Aenemy�Ƃ����g���Ǝv���܂��B
	void isKill() 
	{
		if (!m_isDead) {
			m_isDead = true;
		}
	}
	prefab::CPointLight* GetNearPointLight() const
	{
		return m_nearPointLight;
	}
	//���W��ݒ�
	void SetPosition(const CVector3& pos)
	{
		m_position = pos;
	}
	//��]��ݒ�
	void SetRotation(const CQuaternion rot)
	{
		m_qrot = rot;
	}
	const float m_speed = 0.3f;					//�^�C�g����ʂł̈ړ����x
private:
	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	Player* m_player;
	MistEnemy* m_mistenemy;
	Game* m_game;
	Fade* m_fade;
	Exit* m_exit;
	//Light_Object2* m_lightObject2;
	CVector3 m_position = { 0.0f,0.0f,700.0f };
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_Bedspeed = CVector3::Zero;
	CQuaternion m_qrot = CQuaternion::Identity;
	CCharacterController m_charaCon;
	enum HumanAnimationClip {
		enAnimationClip_idle,
	//	enAnimationClip_walk,
		enAnimationClip_run,
		enAnimationClip_clear,
		enAnimationClip_KneelDown,
		enAnimationClip_num
	};
	//�A�j���[�V�����N���b�v�l�ߍ��킹
	CAnimationClip m_animClip[enAnimationClip_num];
	enum HumanAnimationClip2 {
		enAnimationClip_run2,
		enAnimationClip_num2
	};
	CAnimationClip m_animClip2[enAnimationClip_num2];
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
	//��������
	float m_nearLen = 10000.0f;
	//��ԋ߂����C�g����
	prefab::CPointLight* m_nearPointLight = nullptr;
	//mistenemy���ߊ��t���O
	bool mistflag = false;
	//��ŏ���
	float m_kari = 0.0;
	//���̉�
	float m_volume = 0;
	Title* m_title = nullptr;
	//m_enemy�p�^�C�}�[
	int m_enemytimer = 200;
	TitleGround* m_titleground = nullptr;
	float m_degree = 0.0f;
};

