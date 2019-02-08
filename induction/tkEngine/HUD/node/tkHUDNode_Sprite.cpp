/*!
 *@brief	�X�v���C�g�m�[�h�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/HUD/tkHUD.h"
#include "tkEngine/HUD/node/tkHUDNode_Sprite.h"

namespace tkEngine{
	CHUDNode_Sprite::CHUDNode_Sprite(CBone* bone) :
		IHUDNode(bone)
	{
		//�e�N�X�`�������I�u�W�F�N�g�����璊�o����B
		//�v���t�B�b�N�X�̌�낪�e�N�X�`�����ɂȂ��Ă���B
		const auto boneName = bone->GetName();
		wchar_t filePath[256];
		swprintf_s(filePath, L"sprite/%s.dds", &boneName[HUD_SPRITE_NODE_NAME_PREFIX_LENGTH]);
		CVector3 pos;
		CVector3 scale;
		CQuaternion rot;
		bone->CalcWorldTRS(pos, rot, scale);
		auto t = pos.y;
		pos.y = pos.z;
		pos.z = -t;

		m_spriteRender.Init(filePath, scale.x, scale.y);
		m_spriteRender.SetPosition(pos);
	}
	void CHUDNode_Sprite::Update()
	{
		m_spriteRender.Update();
	}
	void CHUDNode_Sprite::PostRender( CRenderContext& rc )
	{
		m_spriteRender.PostRender(rc);
	}
}
