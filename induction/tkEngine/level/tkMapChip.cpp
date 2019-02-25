/*!
 *@brief	�}�b�v�`�b�v
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/level/tkMapChip.h"
#include "tkEngine/level/tkLevel.h"

namespace tkEngine{
	CMapChip::CMapChip(const LevelObjectData& objData, CMapChipRender* mapChipRender)
	{
		char objName[256];
		wcstombs(objName, objData.name, 256);
		
		//�t�@�C���p�X���쐬�B
		wchar_t filePath[256];
		swprintf_s(filePath, L"modelData/%s.cmo", objData.name);
		m_mapChipRender = mapChipRender;
		m_physicsStaticObject.CreateMesh( 
			objData.position, 
			objData.rotation,
			objData.scale,
			mapChipRender->GetSkinModelRender()
		);
	}
}
