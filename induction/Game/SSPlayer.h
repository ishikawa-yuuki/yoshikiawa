#pragma once
class SSPlayer : public IGameObject//�X�e�[�W�I���p
{
public:
	SSPlayer();
	~SSPlayer();
	bool Start();
	void Update();
	void Move(); // �v���C���[�̊�{�I�ȓ���
	CVector3 GetPosition() const { // �v���C���[�̏ꏊ��Ԃ��֐��B
		return m_position;
	}
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
};

