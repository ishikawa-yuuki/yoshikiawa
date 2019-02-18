#pragma once
class Fade;
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Choice(); //�^�C�g���V�[���̑I��
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	CVector3 m_arrowPos{ 250.0f,-80.0f,0.0f }; // �|�̏����ʒu�Aselect1�̉��ɂ���B
	enum Select {
		select1,//stage�I�����
		select2,//������@���
		select3//�N���W�b�g
	};
	Select m_select = select1;
	bool m_isWaitFadeout = false;//true�Ȃ��ʂ�؂�ւ���B
	Fade* m_fade = nullptr;
};

