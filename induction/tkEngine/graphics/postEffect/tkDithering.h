/*!
 * @brief	�f�B�U�����O�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�f�B�U�����O�B
	 * @details
	 *  �ŏI�I�ȉ摜�Ƀm�C�Y�������邱�Ƃɂ���āA�}�b�n�o���h�Ȃǂ�
	 *  �A�[�e�B�t�@�N�g���y������B
	 */
	class CDithering : Noncopyable{
	public:
		CDithering();
		~CDithering();
		/*!
		 *@brief	�J���B
		 */
		void Release();
		/*!
		 *@brief	�������B
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	�`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		bool m_isEnable = false;		//!<�L���H
		CShader m_vsShader;				//!<���_�V�F�[�_�[
		CShader m_psShader;				//!<�s�N�Z���V�F�[�_�[�B
		CSamplerState m_samplerState;	//!<�T���v���X�e�[�g�B
	};
}