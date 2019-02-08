/*!
 *@brief	�t�H���g�m�[�h�B
 */

#pragma once

#include "tkEngine/HUD/tkIHUDNode.h"

namespace tkEngine{
	class CHUDNode_Font : public IHUDNode{
	public:
		CHUDNode_Font(CBone* bone);
		void Update() override;
		void PostRender( CRenderContext& rc ) override;
		/*!
		*@brief	�e�L�X�g��ݒ�B
		*/
		void SetText(const wchar_t* text)
		{
			m_text = text;
		}
		/*!
		* @brief	�t�H���g��ݒ�B
		* @details	�g�p����t�H���g��ݒ�ł��܂��B
		*  �f�t�H���g�̃t�H���g���g�p����ꍇ�́A���̊֐����g�p����K�v�͂���܂���B
		*  �t�H���g��ύX�������ꍇ�Ɏg�p���Ă��������B
		*@param[in]	font	�t�H���g�B
		*/
		void SetFont(DirectX::SpriteFont* font)
		{
			m_font->SetFont(font);
		}
	private:
		std::unique_ptr<CFont>	m_font;
		std::wstring m_text;
		CVector2 m_position = CVector2::Zero;
	};
}