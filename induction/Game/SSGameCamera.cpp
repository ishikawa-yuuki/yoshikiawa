#include "stdafx.h"
#include "SSPlayer.h"
#include "SSGameCamera.h"


SSGameCamera::SSGameCamera()
{
}


SSGameCamera::~SSGameCamera()
{
}
bool SSGameCamera::Start()
{
	
	m_ssplayer = FindGO<SSPlayer>("SSPlayer");
	//�J������ݒ�B
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetUpdateProjMatrixFunc(CCamera::enUpdateProjMatrixFunc_Ortho);
	return true;
}
void SSGameCamera::Update()
{
	// target(�����_)�ł��B
	 CVector3 SSPlayerPos = m_ssplayer->GetPosition();
	SSPlayerPos.y = 0;
	SSPlayerPos.y += 235.0f;	//�����_�̓v���C���[�̂�����Ə�ɂ���B

						//�����Ď��_���v�Z����B
	CVector3 position = SSPlayerPos;
	//���_�͒����_����y������+100�AZ������-500�ɂ���B
	//position.y += 300.0f;
	position.z -= 200.0f;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肵�čX�V����B
	MainCamera().SetTarget(SSPlayerPos);
	MainCamera().SetPosition(position);
	MainCamera().Update();
}