/// <summary>
/// �V���h�E�}�b�v�̊��N���X�B
/// </summary>

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/shadow/tkIShadowMap.h"
#include "tkEngine/graphics/preRender/shadow/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"


namespace tkEngine {
	void IShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		if (IsEnable() == false) {
			return;
		}
		//�V���h�E�}�b�v�ւ̏������ݏ������Ăяo���B
		RenderToShadowMapImp(rc);
		//�V���h�E�L���X�^�[���N���A�B
		m_shadowCaster.clear();
	}
}
