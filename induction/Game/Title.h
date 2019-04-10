#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	//�^�C�g���V�[���̑I��
	void Choice(); 
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	prefab::CSoundSource* m_bgm = nullptr;
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
	//true�Ȃ��ʂ�؂�ւ���B
	bool m_isWaitFadeout = false;
	Fade* m_fade = nullptr;
};

