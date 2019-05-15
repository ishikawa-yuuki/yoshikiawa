#pragma once
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Player;
class Game;
class GameData;
class Poison : public IGameObject
{
public:
	Poison();
	~Poison();
	bool Start();
	void Update();
	void Range();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	//�S�[�X�g�I�u�W�F�N�g�̏���Ԃ��֐��B
	CPhysicsGhostObject* GetGhost()
	{
		return &m_GhostObject;
	}

	void SetPoisonNumber(const int& num) {
		m_n = num;
	};
	//������ς���
	void SetPoisonMoveNumber(const int& number) {
		m_num = number;
	};
private:
	
	prefab::CSkinModelRender* m_skin = nullptr;
	Lever* m_lever ;
	Player* m_player;
	Game* m_game;
	GameData* m_gamedata = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsGhostObject m_GhostObject;
	float m_timer = 0.0f;
	//�K�X���o���^�C�~���O�����炷�^�C��
	float m_time = 0.0f;
	float m_volume = 0;
    //���Ԃ�
	int m_n = 0;
	//�ǂ̓��������邩
	//1�Ȃ烌�o�[�œ���
	//2�Ȃ珇�Ԃɓ���
	//3�Ȃ烌�o�[�̋t�ɓ���(1�̔��]�j
	int m_num = 0;
	//�K�X�̏��true�Ȃ�o�Ă�
	bool m_State = true;
	
};

