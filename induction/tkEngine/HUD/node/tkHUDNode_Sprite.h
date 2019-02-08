/*!
 *@brief	�X�v���C�g�m�[�h�B
 */

#pragma once

#include "tkEngine/HUD/tkIHUDNode.h"

namespace tkEngine{
	/*!
	 *@brief	�X�v���C�g�m�[�h�B
	 */
	class CHUDNode_Sprite : public IHUDNode{
	public:
		CHUDNode_Sprite(CBone* bone);
		void Update() override;
		void PostRender( CRenderContext& rc ) override;
	private:
		prefab::CSpriteRender m_spriteRender;		//�X�v���C�g�����_���[�B
	};
}
