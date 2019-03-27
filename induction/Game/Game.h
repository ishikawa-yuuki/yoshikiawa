#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Fade;
class Human;
class Player;
class Enemy;
class MoveBed;
class MoveBed_zengo;
class Light_Object;
class GameCamera;
class BackGround;
class Exit;
class Poison;
class Lever;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Pose();
	//�������牺�̊֐��͂��艟���ł��E�E�E�Ȃ񂩂���������������C������E�E�E

	//�Q�[���N���X�����������Ƃ��Ɏg���֐��A��{GameOver�N���X����Ă΂��
	bool GameOwari()
	{
		m_Gamesyuuryou = true;
		return m_Gamesyuuryou;
	}
	//�|�[�Y���ł��邩�ǂ����̊֐��A�G��M�~�b�N������Ŏ~�܂邩��
	bool GetifPose() const
	{
		return m_isPose;
	}
	//�_���[�W���ł��邩�ǂ����̊֐��AHuman��Enemy�N���X�Ɏg���邩��
	bool GetDamage()
	{
		m_damege = true;
		return m_damege;
	}
private:
	/*�|�C���^�Q*/
	Fade * m_fade = nullptr;
	Human * m_human;
	Player* m_player;
	Enemy* m_enemy;
	BackGround* m_background;
	GameCamera * m_gamecamera;
	Light_Object* m_lightobject;
	Exit* m_exit;
	///////////////////
	Poison* m_poison;
	Lever* m_lever;

	prefab::CSkinModelRender* m_goal = nullptr;
	prefab::CSpriteRender* m_sprite_Retire = nullptr;
	prefab::CSpriteRender* m_sprite_toGame = nullptr;
	prefab::CSpriteRender* m_sprite_arrow = nullptr;
	//true�Ȃ��ʂ�؂�ւ���B
	bool m_isWaitFadeout = false;
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

	//level
	CLevel m_level;
	//�ϒ��z��
	std::vector<MoveBed*> m_moveBedList;
	std::vector<MoveBed_zengo*> m_moveBed_zengoList;
	std::vector<MoveBed_zengo*> m_moveBed_zengo2List;
};

