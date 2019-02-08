/*!
 * @brief	��ʊE�[�x�p�̃u���[�B
 */

#pragma once

#include "tkEngine/graphics/tkBlur.h"
#include "tkEngine/graphics/tkHexaBlur.h"

namespace tkEngine{
	/*!
	 * @brief	��ʊE�[�x�p�̃u���[�B
	 */
	class CDofBlur : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CDofBlur();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CDofBlur();
		/*!
		 * @brief	�������B
		 *@param[in]	srcTexture		���e�N�X�`���B
		 *@param[in]	blurIntensity	�u���[�̋����B�l���傫���قǃ{�P��B
		 */
		void Init( CShaderResourceView& srcTexture, float blurIntensity = 25.0f );
		
		/*!
		 * @brief	�u���[�����s�B
		 */
		void Execute(CRenderContext& rc);
		/// <summary>
		/// �Z�p�`�u���[�̌��ʂ��擾�B
		/// </summary>
		/// <returns></returns>
		CShaderResourceView& GetHexaBlurResultSRV()
		{
			return m_hexaBlur.GetResultSRV();
		}
		/// <summary>
		/// �Z�p�`�{�P�̔��a��ݒ肷��B
		/// </summary>
		/// <param name="r">���a�B�e�N�Z����ԁB�f�t�H���g��8�ł��B</param>
		void SetHexaBokeRadius(float r)
		{
			m_hexaBlur.SetRadius(r);
		}
		/// <summary>
		/// �Z�p�`�{�P�̔��a���擾�B
		/// </summary>
		float GetHexaBokeRadius() const
		{
			return m_hexaBlur.GetRadius();
		}
	private:
		bool m_isScaleupBlur = false;
		CShaderResourceView* m_srcTexture = nullptr;
		CRenderTarget m_downSamplingRT;
		CConstantBuffer m_cb;
		CShader m_vsMiniBlur;				//���K�̓u���[�̒��_�V�F�[�_�[�B
		CShader m_psMiniBlur;				//���K�̓u���[�̃s�N�Z���V�F�[�_�[�B
		CShader m_vsXBlurShader;			//!<X�u���[�p�̒��_�V�F�[�_�[�B
		CShader m_vsYBlurShader;			//!<Y�u���[�p�̒��_�V�F�[�_�[�B
		CShader m_psBlurShader;				//!<�u���[�p�̃s�N�Z���V�F�[�_�[�B
		CShader m_psVerticalDiagonalBlur;	//�����΂߃u���[�B
		CBlur m_blur;						//!<�K�E�V�A���u���[�B
		CHexaBlur m_hexaBlur;				//!<�Z�p�`�u���[�B
	};
}