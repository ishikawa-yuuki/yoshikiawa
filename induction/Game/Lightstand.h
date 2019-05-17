#pragma once
#include "tkEngine/physics/tkPhysicsStaticObject.h"
#include "tkEngine/light/tkPointLight.h"
class Player;
class Game;
class GameData;
class Lightstand : public IGameObject
{
public:
	Lightstand();
	~Lightstand();
	void Range();
	bool Start();
	void Update();
	void SetPosition(CVector3 const& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	void SetNum(const int& n) {
		num = n;
	}
	void SetLeverNum(const int& n) {
		Levernum = n;
	}
	void LightLever() {
		m_State = true;
	}
private:
	//Leverの番号を教える。
	int Levernum = 0;
	int num = 0;
	prefab::CSkinModelRender* m_skin = nullptr;
	prefab::CSoundSource* m_sound = nullptr;
	prefab::CPointLight* m_pointLight = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_scale = CVector3::Zero;
	CPhysicsStaticObject m_StaticObject;
	float m_timer = 0.0f;
	float m_volume = 0.0f;
	//Leverのオンオフで判断
	bool m_State = false;
	Player* m_player;
	Game* m_game;
	GameData* m_gamedata;
};

