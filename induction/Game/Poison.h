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
		n = num;
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
	int n = 0;
	int num = 0;
	//�K�X�̏��true�Ȃ�o�Ă�
	bool m_State = true;
	
};

