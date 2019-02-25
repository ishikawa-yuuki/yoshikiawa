/*!
 *@brief	�}�b�v�`�b�v�����_���[
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/level/tkMapChipRender.h"
#include "tkEngine/level/tkLevel.h"

namespace tkEngine {
	CMapChipRender::CMapChipRender()
	{
	}
	CMapChipRender::~CMapChipRender()
	{
	}
	
	void CMapChipRender::OnDestroy()
	{
		DeleteGO(m_modelRender);
	}
	
	void CMapChipRender::Update()
	{
		if (m_renderObjDatas.size() > 1) {
			for (auto& objData : m_renderObjDatas) {
				m_modelRender->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
			}
		}
	}

	void CMapChipRender::InitAfterAddAllRenderObjects()
	{
		//�X�L�����f�������_���[������������B
		m_modelRender = NewGO<prefab::CSkinModelRender>(0);
		//�t�@�C���p�X���쐬�B
		wchar_t filePath[256];
		swprintf_s(filePath, L"modelData/%s.cmo", m_renderObjDatas[0].name);
		if (m_renderObjDatas.size() > 1) {
			//�C���X�^���V���O
			m_modelRender->Init(filePath, nullptr, 0, enFbxUpAxisZ, m_renderObjDatas.size());
		}
		else {
			//�̂��ƃC���X�^���V���O
			m_modelRender->Init(filePath);
			m_modelRender->SetPosition(m_renderObjDatas[0].position);
			m_modelRender->SetRotation(m_renderObjDatas[0].rotation);
			m_modelRender->SetScale(m_renderObjDatas[0].scale);
		}
		//�e
		m_modelRender->SetShadowReceiverFlag(true);
		m_modelRender->SetShadowCasterFlag(true);
	}
}
