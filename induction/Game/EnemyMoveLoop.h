#pragma once
class Enemy;
class PathEdge;
class Path;
class EnemyMoveLoop
{
public:
	EnemyMoveLoop(Enemy* en, Path& path);
	~EnemyMoveLoop();
	void Update();
private:
	enum enState {
		enState_FindNearEdge,		//�߂��G�b�W�������B
		enState_MoveNearEdge,		//�߂��G�b�W�Ɉړ��B
		enState_MovePath,			//�p�X���ړ��B
		enState_MovePath_Reverse,	//�p�X���t�����Ɉړ����B�B
		enState_Turn,		//���̃G�b�W�Ɍ����Đ���B
	};
	void ChangeState(enState nextState)
	{
		m_state = nextState;
	}
	/*!
	*@brief	�^�[����Ԃɐ؂�ւ���Ƃ��͂��������g���B
	*@param[in]	stateWhenTurnEnd	�^�[���I�����̎��̃X�e�[�g�B
	*@param[in]	turnDir				�ړI�i�s�����B
	*/
	void ChangeTurnState(enState stateWhenTurnEnd, const CVector3& targetDir);

	const PathEdge* m_currentEdge = nullptr;
	Enemy*	m_enemy = nullptr;
	Path* m_path = nullptr;
	enState m_state = enState_FindNearEdge;
	enState m_stateWhenTurnEnd;				//!<�^�[���I�����̎��̃X�e�[�g�B	
	float m_angleWhenStartTurn;				//!<�^�[���J�n���̃A���O���B�P�ʁF���W�A���B
	float m_angleWhenEndTurn;				//!<�^�[���I�����̃A���O���B�P�ʁF���W�A���B
	float m_angle = 0.0f;					//!<�^�[�����̊p�x�B
};
