/*!
 *@brief	�|�X�g�G�t�F�N�g�B
 */

#pragma once

#include "tkEngine/graphics/postEffect/tkFxaa.h"
#include "tkEngine/graphics/postEffect/tkBloom.h"
#include "tkEngine/graphics/postEffect/tkTonemap.h"
#include "tkEngine/graphics/postEffect/tkDithering.h"
#include "tkEngine/graphics/postEffect/tkScreenSpaceReflection.h"
#include "tkEngine/graphics/postEffect/tkDof.h"
#include "tkEngine/graphics/tkPrimitive.h"


namespace tkEngine{
	/*!
	 *@brief	�|�X�g�G�t�F�N�g�B
	 */
	class CPostEffect : Noncopyable {
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CPostEffect();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CPostEffect();
		/*!
		 *@brief	�J���B
		 */
		void Release();
		/*!
		 *@brief	�쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 */
		void Create(const SGraphicsConfig& config);
		/*!
		*@brief	�`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void Render(CRenderContext& rc);
		/*!
		*@brief	�t���X�N���[���`��B
		*@param[in]		rc		�����_�����O�R���e�L�X�g�B
		*/
		void DrawFullScreenQuad(CRenderContext& rc);
		/*!
		*@brief	�g�[���}�b�v�̎擾�B�B
		*/
		CTonemap& GetTonemap()
		{
			return m_tonemap;
		}
		/// <summary>
		/// DofDofDof
		/// </summary>
		/// <returns></returns>
		CDof& GetDof()
		{
			return m_dof;
		}
		/*!
		* @brief	�ŏI�������݂̃����_�����O�^�[�Q�b�g��؂�ւ��B
		*/
		void ToggleFinalRenderTarget()
		{
			m_currentFinalRenderTarget ^= 1;
		}
		/*!
		* @brief	�ŏI�������݂̃����_�����O�^�[�Q�b�g�̎擾�B
		*/
		CRenderTarget& GetFinalRenderTarget()
		{
			return m_finalRenderTarget[m_currentFinalRenderTarget];
		}
	private:
		/*!
		*@brief	�t���X�N���[���`��p�̋�`�v���~�e�B�u�̏������B�B
		*/
		void InitFullScreenQuadPrimitive();
		/*!
		 *@brief	�|�X�g�G�t�F�N�g�̍ŏI�������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		 */
		void InitFinalRenderTarget();
	private:
		CScreenSpaceReflection	m_ssr;				//!<SSR;
		CFxaa					m_fxaa;				//!<FXAA�B
		CBloom					m_bloom;			//!<BLOOM�B
		CTonemap				m_tonemap;			//!<�g�[���}�b�v�B
		CDithering				m_dithering;		//!<�f�B�U�����O�B
		CDof					m_dof;				//Dof
		CPrimitive				m_fullscreenQuad;	//!<�t���X�N���[���`��p�̋�`�v���~�e�B�u�B
		int	m_currentFinalRenderTarget = 0;			//!<���݂̃��C�������_�����O�^�[�Q�b�g�B
		CRenderTarget m_finalRenderTarget[2];		//!<�|�X�g�G�t�F�N�g�̍ŏI�������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
	};
}