#pragma once
class Stage_Select : public IGameObject
{
public:
	Stage_Select();
	~Stage_Select();
	bool Start();
	void Update();
	void Choice(); //�X�e�[�W�I�����邽�߂̊֐�
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSpriteRender* m_arrow = nullptr;
	CVector3 m_arrowPos{ -450.0f,67.0f,0.0f }; // �|�̏����ʒu�Astage1�̉��ɂ���B
	enum Stage {
		stage1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
};

