/*!
 *@brief	�}�b�v�`�b�v
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/level/tkMapChip.h"
#include "tkEngine/level/tkLevel.h"

namespace tkEngine{
	CMapChip::CMapChip(LevelObjectData& objData)
	{
		char objName[256];
		wcstombs(objName, objData.name, 256);
		//�����_���[���쐬�B
		m_modelRender = NewGO<prefab::CSkinModelRender>(0, objName);
		//�t�@�C���p�X���쐬�B
		wchar_t filePath[256];
		swprintf_s(filePath, L"modelData/%s.cmo", objData.name);
		m_modelRender->Init(filePath);
		m_modelRender->SetPosition(objData.position);
		m_modelRender->SetRotation(objData.rotation);
		m_modelRender->SetScale(objData.scale);
		//MapChip�p�̃��f�B�t�@�C�A�����Ȃ�����Ȃ��E�E�E
		m_modelRender->SetShadowReceiverFlag(true);
		
		m_physicsStaticObject.CreateMesh( 
			objData.position, 
			objData.rotation,
			objData.scale,
			m_modelRender
		);
	}
}
