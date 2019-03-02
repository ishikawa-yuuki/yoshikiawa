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
		enState_FindNearEdge,		//近いエッジを検索。
		enState_MoveNearEdge,		//近いエッジに移動。
		enState_MovePath,			//パスを移動。
		enState_MovePath_Reverse,	//パスを逆方向に移動中。。
		enState_Turn,		//次のエッジに向けて旋回。
	};
	void ChangeState(enState nextState)
	{
		m_state = nextState;
	}
	/*!
	*@brief	ターン状態に切り替えるときはこっちを使う。
	*@param[in]	stateWhenTurnEnd	ターン終了時の次のステート。
	*@param[in]	turnDir				目的進行方向。
	*/
	void ChangeTurnState(enState stateWhenTurnEnd, const CVector3& targetDir);

	const PathEdge* m_currentEdge = nullptr;
	Enemy*	m_enemy = nullptr;
	Path* m_path = nullptr;
	enState m_state = enState_FindNearEdge;
	enState m_stateWhenTurnEnd;				//!<ターン終了時の次のステート。	
	float m_angleWhenStartTurn;				//!<ターン開始時のアングル。単位：ラジアン。
	float m_angleWhenEndTurn;				//!<ターン終了時のアングル。単位：ラジアン。
	float m_angle = 0.0f;					//!<ターン中の角度。
};
