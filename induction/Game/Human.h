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
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;//スキンモデルレンダラー
	Player* m_player;
	CVector3 m_position;
	CVector3 m_movespeed;
};

