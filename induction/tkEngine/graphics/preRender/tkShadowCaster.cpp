/*!
 * @brief	�V���h�E�L���X�^�[�B
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"

namespace tkEngine{

////////////////////////////////////////////////////////////////
// �V���h�E�L���X�^�[(�X�L�����f����)
////////////////////////////////////////////////////////////////
	CShadowCaster_SkinModel::CShadowCaster_SkinModel() :
		m_skinModel(nullptr)
	{
	}
	CShadowCaster_SkinModel::~CShadowCaster_SkinModel()
	{
		//�V���h�E�}�b�v�ɓo�^����Ă��邩������Ȃ��̂ŁA�폜����B
		GraphicsEngine().GetShadowMap().Remove(this);
	}
	void CShadowCaster_SkinModel::Create(CSkinModel* model)
	{
		m_skinModel = model;
	}
	void CShadowCaster_SkinModel::Render(CRenderContext& renderContext, const CMatrix& mLVP)
	{
		if (!m_skinModel) {
			return;
		}
		m_skinModel->Draw(renderContext, mLVP, CMatrix::Identity);
	}
}