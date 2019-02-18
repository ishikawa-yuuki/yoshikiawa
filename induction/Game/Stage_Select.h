#pragma once
class Fade;
class SSPlayer;
class SSHuman;
class SSGameCamera;
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
	void Choice(); //�X�e�[�W�I�����邽�߂̊֐�
private:
	prefab::CSkinModelRender* m_skin = nullptr;
	enum Stage {
		stage1,
		stage2,
		stage3
	};
	bool m_isWaitFadeout = false;//true�Ȃ��ʂ�؂�ւ���B
	bool m_Tile = false;
	Fade* m_fade = nullptr;
	Stage m_stage = stage1;
	SSPlayer* m_ssPlayer = nullptr;
	SSHuman* m_ssHuman = nullptr;
	SSGameCamera* m_ssGC = nullptr;
};

