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
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
	prefab::CSpriteRender* m_menu1;
	prefab::CSpriteRender* m_menu2;
	prefab::CSpriteRender* m_menu3;
	// �|�̏����ʒu�Aselect1�̉��ɂ���B
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f };
	enum Select {
		//stage�I�����
		select1,
		//������@���
		select2,
		//�N���W�b�g
		select3
	};
	Select m_select = select1;
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
};

