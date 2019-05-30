#pragma once
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/light/tkPointLight.h"

class Player;
class Human;
class Light_Object : public IGameObject
{
public:
	Light_Object();
	~Light_Object();
	bool Start();
	void Update();
	void InitPointLight();
	void Dirlight();
	void housenlight();
	//�|�W�V���������x���œ����B
	void SetPosition(const CVector3& pos) 
	{
		m_position = pos;
	}
	//�X�P�[�������x���œ����B
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}
	//���[�e�[�V���������x���ɓ����B
	void SetRotation(const CQuaternion& rot) {
		m_rot = rot;
	}
	//���O�̒ʂ胉�C�g���傫���Ȃ�
	bool Biglight()
	{
		m_biglight = true;
		return  m_biglight;
	}
	//���ꂪ�Ă΂ꂽ�班�������d�l���Ⴄ���C�g�ɂȂ�
	bool Lastlight()
	{
		m_lastlight = true;
		return m_lastlight;
	}
	//���ꂪ�Ă΂ꂽ�珉����Ԃ̃��C�g��on�ɂȂ�
	bool SetLight()
	{
		m_isLightOn = true;
		return m_isLightOn;
	}
	//���̃|�W�V�����̒l��Ԃ��B
	CVector3 GetPosition()const
	{
		return m_position;
	}
	bool GetLightOn()const
	{
		return m_isLightOn;
	}
	CVector4 GetPointLightAttn() const
	{
		return m_ptLight->GetAttn();
	}
	prefab::CPointLight* GetPointLight() const
	{
		return m_ptLight;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	//���x���f�U�C���Ő݌v����̂łƂ肠������
	CVector3 m_position = { 0.0f,-70.0f,-3000.0f };
	CVector3 m_scale = CVector3::One;
	CQuaternion m_rot = CQuaternion::Identity;
	Player* m_player;
	Human* m_human;
	//���C�g���I���Ȃ̂��ǂ���
	bool m_isLightOn = false;
	//���C�g���傫�����ǂ���
	bool m_biglight = false;
	//�Ō�̃X�e�[�W�Ŕz�u����郉���^�����ǂ���
	bool m_lastlight = false;
	//���C�g�B
	prefab::CDirectionLight* m_lig = nullptr;
	//���C�g�̕����B
	CVector3 m_lightDir;					
	prefab::CDirectionLight* m_directionLig = nullptr;
	//housenlight()�Ŏg���B
	CShaderResourceView m_normalMapSRV;
	CShaderResourceView m_specularMapSRV;
	CShaderResourceView m_lnormalMapSRV;
	CShaderResourceView m_lspecularMapSRV;
	//�X�|�b�g���C�g�p��effect
	prefab::CEffect* m_effect = nullptr;
	//�|�C���g���C�g�𐶐�
	prefab::CPointLight* m_ptLight = nullptr;
	//���C�g�̌��̑����A�������𑀍�B
	CVector3 attn = CVector3::Zero;
};

