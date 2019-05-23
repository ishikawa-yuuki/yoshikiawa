#include <unordered_map>
#include "GameData.h"
#include "tkEngine/Physics/tkPhysicsStaticObject.h"
#pragma once
class Fade;
class SSPlayer;
class SSHuman;
class SSPoint;
class SSGameCamera;
class GameCamera;
class GameData;
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
	//該当の番号のステージポイントのポインタを取得
	SSPoint* GetStagePoint(const GameData::StageNumber& number)
	{
		return m_sspointList[number];
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CQuaternion m_humanrot = CQuaternion::Identity;
	//trueなら画面を切り替える。
	bool m_isWaitFadeout = false;
	//タイトル切り替えtrueなら切り替える
	bool m_Tile = false;
	Fade* m_fade = nullptr;
	SSPlayer* m_ssPlayer = nullptr;
	SSHuman* m_ssHuman = nullptr;
	SSGameCamera* m_ssGC = nullptr;
	//level
	CLevel m_level;
	prefab::CSky* m_sky = nullptr;
	GameCamera* m_gamecamera = nullptr;
	GameData* m_gamedata = nullptr;
	std::unordered_map<int, CVector3> m_playerpositionList;   //プレイヤーの座標のリスト
	std::unordered_map<int, CVector3> m_humanpositionList;    //Humanの座標のリスト
	std::unordered_map<int, SSPoint*> m_sspointList;		  //ステージの明かりのリスト
	CVector3 m_pos;
	CPhysicsStaticObject m_physicsStaticObject;
	
};

