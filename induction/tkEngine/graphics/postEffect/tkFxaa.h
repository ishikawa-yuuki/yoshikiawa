/*!
 *@brief	FXAA
 */

#pragma once

namespace tkEngine{
	class CPostEffect;
	/*!
	 *@brief	FXAA
	 *@details
	 * �|�X�g�G�t�F�N�g�ɂ��A���`�G�C���A�X�B
	 */
	class CFxaa : Noncopyable{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CFxaa();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CFxaa();
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
		bool m_isEnable = false;	//!<�L���H
		CShader m_vsShader;			//!<���_�V�F�[�_�[
		CShader m_psShader;			//!<FXAA�p�̃s�N�Z���V�F�[�_�[�B
		CSamplerState m_samplerState;	//!<FXAA�p�̃T���v���X�e�[�g�B
	};
}