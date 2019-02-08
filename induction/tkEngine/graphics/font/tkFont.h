/*!
 * @brief	�t�H���g
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�t�H���g�B
	 */
	class CFont final{
	public:
		CFont();
		~CFont();
		/*!
		* @brief	�t�H���g��ݒ�B
		* @details	�f�t�H���g�t�H���g����ύX�������ꍇ��
		*  DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ����s���Ă��������B
		*/
		void SetFont(DirectX::SpriteFont* font)
		{
			m_spriteFont = font;
		}
		/*!
		 * @brief	�`��J�n�B
		 */
		void Begin(CRenderContext& rc);
		/*!
		 * @brief	�`��I���B
		 */
		void End(CRenderContext& rc);
		/*!
		 * @brief	�`��B
		 *@param[in]	text		�\���������e�L�X�g�B
		 *@param[in]	trans		���s�ړ��B
		 *@param[in]	color		�J���[�B
		 *@param[in]	rot			��]�B
		 *@param[in]	scale		�g��B
		 *@param[in]	pivot		��_�B
		 *						0.5, 0.5�ŉ摜�̒��S����_�B
		 *						0.0, 0.0�ŉ摜�̍����B
		 *						1.0, 1.0�ŉ摜�̉E��B
		 *						Unity��uGUI�ɏ����B
		 */
		void Draw(
			wchar_t const* text, 
			const CVector2& position, 
			const CVector4& color = CVector4::White,
			float rotation = 0.0f, 
			float scale = 1.0f,
			CVector2 pivot = {0.5f, 0.5f}
		);
		/*!
		 *@brief	�e�̃p�����[�^��ݒ�B
		 *@param[in]	isDrawShadow		�e��`���H
		 *@param[in]	shadowOffset		�e��`���Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
		 *@param[in]	shadowColor			�e�̐F�B
		 */
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor)
		{
			m_isDrawShadow = isDrawShadow;
			m_shadowOffset = shadowOffset;
			m_shadowColor = shadowColor;
		}
	private:
		DirectX::SpriteBatch*	m_spriteBatch = nullptr;	//!<�X�v���C�g�o�b�`�B
		DirectX::SpriteFont*	m_spriteFont = nullptr;		//!<�X�v���C�g�t�H���g�B
		bool m_isDrawShadow = false;						//!<�e�������H
		float m_shadowOffset = 0.0f;						//!<�e�������Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
		CVector4 m_shadowColor = CVector4::Black;			//!<�e�̐F�B
		CMatrix m_scaleMat;
	};
}