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
	//�Y���̔ԍ��̃X�e�[�W�|�C���g�̃|�C���^���擾
	SSPoint* GetStagePoint(const GameData::StageNumber& number)
	{
		return m_sspointList[number];
	}
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	CQuaternion m_humanrot = CQuaternion::Identity;
	//true�Ȃ��ʂ�؂�ւ���B
	bool m_isWaitFadeout = false;
	//�^�C�g���؂�ւ�true�Ȃ�؂�ւ���
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
	std::unordered_map<int, CVector3> m_playerpositionList;   //�v���C���[�̍��W�̃��X�g
	std::unordered_map<int, CVector3> m_humanpositionList;    //Human�̍��W�̃��X�g
	std::unordered_map<int, SSPoint*> m_sspointList;		  //�X�e�[�W�̖�����̃��X�g
	CVector3 m_pos;
	CPhysicsStaticObject m_physicsStaticObject;
	
};

