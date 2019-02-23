#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
class Fade;
class Human;
class Player;
class MoveBed;
class GameCamera;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Pose();
	//�������牺�̊֐��͂��艟���ł��E�E�E�Ȃ񂩂���������������C������E�E�E

	bool GameOwari() {//�Q�[���N���X�����������Ƃ��Ɏg���֐��A��{GameOver�N���X����Ă΂��
		m_Gamesyuuryou = true;
		return m_Gamesyuuryou;
	}
	bool GetifPose() const{//�|�[�Y���ł��邩�ǂ����̊֐��A�G��M�~�b�N������Ŏ~�܂邩��
		return m_isPose;
	}
	bool GetDamage(){//�_���[�W���ł��邩�ǂ����̊֐��AHuman��Enemy�N���X�Ɏg���邩��
		m_damege = true;
		return m_damege;
	}
private:
	Fade * m_fade = nullptr;
	Human * m_human;
	Player* m_player;
	MoveBed* m_movebed;
	GameCamera * m_gamecamera;

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSpriteRender* m_sprite_Retire = nullptr;
	prefab::CSpriteRender* m_sprite_toGame = nullptr;
	prefab::CSpriteRender* m_sprite_arrow = nullptr;
	bool m_isWaitFadeout = false; //true�Ȃ��ʂ�؂�ւ���B
	bool m_isPose = false;
	CVector3 m_Retirepos = { -200.0f,-100.0f,0.0f };
	CVector3 m_toGamepos = { 200.0f,-100.0f,0.0f };
	CVector3 m_arrowpos = { -400.0f,-100.0f,0.0f };
	enum pose{
		retire,
		togame,
		posenum
	};
	pose m_state = retire;
	bool m_Gamesyuuryou = false;
	bool m_damege = false;
};

