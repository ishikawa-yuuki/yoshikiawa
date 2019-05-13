#pragma once
#include "tkEngine/light/tkPointLight.h"
class Fade;
class TitleGround;
class Player;
class Human;
class GameCamera;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	//�^�C�g���V�[���̑I��
	void Choice(); 
	//�X�e�[�W�Z���N�g��ʂɑJ�ڂ��邩�ǂ���
	bool isTransStageSelect()
	{
		return m_istransstageselect;
	}
	//�F�X�X�g�b�v
	bool isStop()
	{
		return m_isstop;
	}
	//�J�����̒����_���擾
	CVector3 GetCameraTarget()
	{
		return m_camerataragetpos;
	}
private:
	void GameStart();
	void SelectMenu();
	void TransScene();
	void TransStageSelect();
private:
	enum State {
		enState_GameStart,					//�X�^�[�g�{�^�������܂�
		enState_SelectMenu,					//���j���[�\��
		enState_TransScene,					//�N���W�b�g�⑀������Ɉڍs���鎞		
		enState_TransStageSelect,			//�X�e�[�W�Z���N�g��ʂɈڍs���鎞
	};
	State m_state = enState_GameStart;
	const CVector4 m_transparent = CVector4(1.0f, 1.0f, 1.0f, 0.0f);		//�摜�𓧖�(�\�������Ȃ���)�ɂ�����J���[��Z������
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSpriteRender* m_pressstart = nullptr;
	std::vector <prefab::CSpriteRender*> m_menuList;
	// �|�̏����ʒu�Aselect1�̉��ɂ���B
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f };
	TitleGround* m_titleground = nullptr;
	Player* m_player = nullptr;
	Human* m_human = nullptr;
	GameCamera* m_gamecamera = nullptr;
	//�|�C���g���C�g�𐶐�
	prefab::CPointLight* m_ptLight = nullptr;
	//���C�g�̌��̑����A�������𑀍�B
	CVector3 attn = CVector3::Zero;
	//true�Ȃ��ʂ�؂�ւ���B
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
	//level
	CLevel m_level;
	bool m_istransstageselect = false;
	//���j���[�Ɉڍs����܂�
 	float m_alphatitle = 0.0f, m_alphastart = 0.0f;
	float m_starttime = 1.0f;
	bool m_isaddalphastart = true;
	bool m_ispressstartbutton = false;
	//���j���[�I������V�[���ڍs�܂�
	float m_alphamenu = 0.0f;							//���l
	const float m_translucentalphamenu = 0.5f;			//�I������ĂȂ���͔������ɂ���
	bool m_ispressAbutton = false;						//A�{�^���������ꂽ���ǂ���
	enum Select {
		//stage�I�����
		enState_StageSelect,
		//������@���
		enState_Manual,
		//�N���W�b�g
		enState_Credit,
		//�ŏ��l
		enState_Fist = enState_StageSelect,
		//�ő�l
		enState_Last = enState_Credit
	};
	Select m_select = enState_StageSelect;				//�ŏ��̓J�[�\���͈�ԏ�
	//�X�e�[�W�Z���N�g��ʂɈڍs
	CVector3 m_point = CVector3::Zero;
	bool m_isstop = false;
	float m_timer = 0.0f, m_time = 4.6f,m_time2 = 5.2;
	prefab::CSky* m_sky = nullptr;
	CVector3 m_camerataragetpos = CVector3::Zero;
};

