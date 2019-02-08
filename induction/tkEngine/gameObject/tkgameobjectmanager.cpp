/*!
 *@brief	CGameObject�̃}�l�[�W��
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/gameObject/tkgameobjectmanager.h"
#include <future>
#include "tkEngine/graphics/preRender/tkPreRender.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"

namespace tkEngine{
	void CGameObjectManager::Start()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
	}
	void CGameObjectManager::PreUpdate()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreUpdateWrapper();
			}
		}
	}
	void CGameObjectManager::Update()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
	}
	void CGameObjectManager::PostUpdate()
	{
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostUpdateWrapper();
			}
		}
	}
	void CGameObjectManager::BeginRender(CRenderContext& rc)
	{
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha
		CRenderTarget* renderTargets[] = {
			&GraphicsEngine().GetMainRenderTarget()
		};
	//	rc.BeginRender();
		rc.OMSetRenderTargets(1, renderTargets);
		rc.ClearRenderTargetView(0, ClearColor);
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
		rc.RSSetState(RasterizerState::sceneRender);
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender);
		rc.PSSetSampler(0, *CPresetSamplerState::clamp_clamp_clamp_linear);
	}
	void CGameObjectManager::ForwardPreRender(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_ForwardPreRender");
		//�����_�����O�X�e�b�v���t�H���[�h�����_�����O�ɁB
		rc.SetRenderStep(enRenderStep_ForwardPreRender);
		
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PreForwardRenderWrapper(rc);
			}
		}
		EndGPUEvent();
	}
	void CGameObjectManager::ForwardRender(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_ForwardRender");
		rc.SetRenderStep(enRenderStep_ForwardRender);
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->ForwardRenderWrapper(rc);
			}
		}
		//�������[���h�̃f�o�b�O�`��B
		PhysicsWorld().DebubDrawWorld(rc);
		EndGPUEvent();
	}
	void CGameObjectManager::PostRender(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_Render2DToScene");

		rc.OMSetBlendState(AlphaBlendState::trans);
		rc.RSSetState(RasterizerState::spriteRender);
		rc.OMSetDepthStencilState(DepthStencilState::spriteRender);
		rc.SetRenderStep(enRenderStep_Render2DToScene);
		for (GameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->PostRenderWrapper(rc);
			}
		}
		EndGPUEvent();
	}
	void CGameObjectManager::ExecuteFromMainThread()
	{
		//Start
		Start();
	}
	void CGameObjectManager::ExecuteFromGameThread()
	{
		
		//�X�V�n�̏����B
		{
			
			//���O�A�b�v�f�[�g�B
			PreUpdate();
			//�v�������_�����O�̍X�V�����B
			GraphicsEngine().GetPreRender().Update();
			//�A�b�v�f�[�g�B
			Update();
			//�x���A�b�v�f�[�g�B
			PostUpdate();
			//�V�[���O���t���X�V�B
			UpdateSceneGraph();
			//���C�g���X�V�B
			LightManager().Update();
			//�G�t�F�N�g���X�V�B
			GraphicsEngine().GetEffectEngine().Update();
		}
		//�`��n�̏����B
		{
			CRenderContext& renderContext = GraphicsEngine().GetRenderContext();
			//��ʂ��N���A
			BeginRender(renderContext);
			//�v�������_�����O�B
			GraphicsEngine().GetPreRender().Render(renderContext);
			//�f�B�t�@�[�h�V�F�[�f�B���O�B
			GraphicsEngine().DefferdShading(renderContext);
			//���O�t�H���[�h�����_�����O�B
			ForwardPreRender(renderContext);
			//�t�H���[�h�����_�����O�B
			ForwardRender(renderContext);
			//�|�X�g�G�t�F�N�g�B
			GraphicsEngine().GetPostEffect().Render(renderContext);
			//2D�I�Ȃ��̂̕`��B
			PostRender(renderContext);
		}
		ExecuteDeleteGameObjects();
	}
	void CGameObjectManager::UpdateSceneGraph()
	{
		//���[���h�s����X�V�B
		for (auto transform : m_childrenOfRootTransformList) {
			transform->UpdateWorldMatrixAll();
		}
	}
	void CGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//�o�b�t�@��؂�ւ��B
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for(GameObjectList& goList : m_deleteObjectArray[preBufferNo]){
			for(IGameObject* go : goList){
				GameObjectPrio prio = go->GetPriority();
				GameObjectList& goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find( goExecList.begin(),goExecList.end(),go );
				if (it != goExecList.end()) {
					//�폜���X�g���珜�O���ꂽ�B
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManager()) {
						delete (*it);
					}
				}
				goExecList.erase(it);
			}
			goList.clear();
		}
	}
	void CGameObjectManager::Init( int gameObjectPrioMax )
	{
		TK_ASSERT( gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}
}