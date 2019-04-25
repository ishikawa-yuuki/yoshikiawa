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
	Player* m_player;
	Human* m_human;
	//���C�g���I���Ȃ̂��ǂ���
	bool m_isLightOn = false;
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
};

