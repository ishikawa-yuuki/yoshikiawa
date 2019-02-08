/*!
 * @brief	�t�H���g
 */

#pragma once

#include "tkEngine/graphics/font/tkFont.h"

namespace tkEngine{
namespace prefab {
	/*!
	 * @brief	�t�H���g�����_�[�B
	 */
	class CFontRender final : public IGameObject{
	public:
		/*!
		* @brief	�t�H���g��ݒ�B
		* @details	�f�t�H���g�t�H���g����ύX�������ꍇ��
		*  DirectX::SpriteFont���g�p���āA�t�H���g�����[�h���č����ւ����s���Ă��������B
		*/
		void SetFont(DirectX::SpriteFont* font)
		{
			m_font.SetFont(font);
		}
		
		/*!
		 *@brief	�e�̃p�����[�^��ݒ�B
		 *@param[in]	isDrawShadow		�e��`���H
		 *@param[in]	shadowOffset		�e��`���Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB
		 *@param[in]	shadowColor			�e�̐F�B
		 */
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}
		/*!
		 * @brief	�e�L�X�g��ݒ�B
		 *@details
		 * ���t���[���ĂԂƏd�����I�I�I\n
		 * �d���̂����ɂȂ����瑊�k���Ă�\n
		 * Unsafe�ł�����܂��B
		 *@param[in]	text		�e�L�X�g
		 */
		void SetText(const wchar_t* text)
		{
			if (wcscmp(m_text.c_str(), text) != 0) {
				//�����񂪕ς�����B
				m_text = text;
			}
			
		}
		/*!
		 * @brief	�e�L�X�g��ݒ�BUnsafe�ŁB
		 *@details
		 *�@�댯����I�I�I\n
		 *  �f�l�͎g������_���I\n
		 *  �g�������l�͂����Ƃ��̐��ǂ�łˁI�I�I\n
		 * 
		 *
		 *
		 *
		 *
		 *  SetText�͌Ăяo�����тɕ�����̃R�s�[���������邽�߁A\n
		 *  ���񃁃����A���P�[�g������܂��B\n
		 *  �������A�����Ń������m�ۂ��s���Ă��邽�߁A\n
		 *  �����Ŏw�肳�ꂽ�e�L�X�g�������ɂȂ��Ă����Ȃ����삵�܂��B\n
		 *  �������ASetTextUnsafe�ł͈����œn���ꂽ�A�h���X�����̂܂܎g�p���邽�߁A\n
		 *  �t�H���g�̕`�悪��������܂ŁA���̃A�h���X�͗L���ł���K�v������܂��B\n
		 *  �悤�́A���[�J���ϐ��Ɋi�[���Ă���e�L�X�g�Ƃ��n�����玀�ʂ�( �L䇁M)�I���Ă��Ƃł��B\n
		 *  ���̐�����ǂ�ŁA�Ӗ���������Ȃ��l�́ASetTextUnsafe�͎g��Ȃ����ƁI�I�I�I
		 * 
		 @param[in]	text		�e�L�X�g
		 */
		void SetTextUnsafe(const wchar_t* text)
		{
			m_textUnsafe = text;
		}
		/*!
		* @brief	�t�H���g��\��������W��ݒ�B
		*@details
		* �t�H���g�̍��W�n��2�����ƂȂ��Ă���A��ʂ̒�����0, 0�Ƃ��܂��B\n
		* �E������X+�A�������Y+�̍��W�n�ł��B
		*@param[in]	pos		���W�B
		*/
		void SetPosition(const CVector2& pos)
		{
			m_position = pos;
		}
		/*!
		* @brief	�t�H���g�̃J���[��ݒ�B
		*@details
		* �t�H���g�̃J���[�͌��̎O���F�Ŏw�肵�܂��B\n
		* ������color.x���ԁAcolor.y���΁Acolor.z���ƂȂ�܂��B\n
		* �e�����ɐݒ�ł���l��0.0�`1.0�ł��B\n
		* �Ⴆ�΁A�^���Ԃ��w�肵�����ꍇ�́A\n
		* color.x = 1.0f�Acolor.y = 0.0f�Acolor.z = 0.0f�ƂȂ�܂��B
		* 
		*@param[in]	color	�F�B
		*/
		void SetColor(const CVector3& color)
		{
			m_color = color;
		}
		/*!
		 *@brief	��]��ݒ�B
		 *@param[in]	rotation	��]�p�x�B�P�ʂ̓��W�A���B
		 */
		void SetRotation(float rotation)
		{
			m_rotation = rotation;
		}
		/*!
		 *@brief	�g�嗦��ݒ�B
		 *@param[in]	scale	�g�嗦�B
		 */
		void SetScale(float scale)
		{
			m_scale = scale;
		}
		/*!
		 *@brief	�s�{�b�g��ݒ�B
		 *@details
		 *�@�t�H���g��\������ۂ̊�_���w�肵�܂��B\n
		 *�@0.5, 0.5�ŉ摜�̒��S����_�B
		 *	0.0, 0.0�ŉ摜�̍����B
		 *	1.0, 1.0�ŉ摜�̉E��B
		 *  Unity��uGUI�ɏ����B
		 *@param[in]	pivot	��_�B
		 */
		void SetPivot(const CVector2& pivot)
		{
			m_pivot = pivot;
		}
	private:
		void PostRender(CRenderContext& rc);
	private:
		CFont m_font;
		std::wstring m_text;					//!<�e�L�X�g�B
		const wchar_t* m_textUnsafe = nullptr;	//!<�A���Z�[�t�ł̃e�L�X�g�B
		CVector2 m_position = CVector2::Zero;	//!<���W�Bx = 0.0f, y = 0.0f�ŉ�ʂ̒��S�B
		CVector4 m_color = CVector4::White;		//!<�J���[�B
		float m_rotation = 0.0f;				//!<��]�B
		float m_scale = 1.0f;					//!<�g�嗦�B
		CVector2 m_pivot;						//!<�s�{�b�g�B
	};
}
}