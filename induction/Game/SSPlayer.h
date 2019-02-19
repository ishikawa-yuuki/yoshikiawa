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
	int GetStagenum() {//�I�������X�e�[�W�̔ԍ�
		return m_stage;
	}
	enum Stage {
		stage1 = 1,
		stage2,
		stage3
	};
	Stage m_stage = stage1;
private:
	CVector3 m_position = CVector3::Zero;
	prefab::CEffect* m_effect;
};

