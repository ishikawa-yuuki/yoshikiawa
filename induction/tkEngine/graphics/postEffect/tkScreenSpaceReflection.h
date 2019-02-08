/*!
 *@brief	Screen Space Reflection
 */

#pragma once

#include <random>
#include "tkEngine/graphics/tkBlur.h"

namespace tkEngine{
	class CPostEffect;
	/*!
	*@brief	Screen Space Reflection
	*@details
	* �X�N���[����ԂŃ��C�}�[�`���O���s���^���I�ȉf�荞�݂�\�����܂��B
	*/
	class CScreenSpaceReflection{
	public:
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
		*@param[in]		rc		�����_�����O�R���e�L�Xt�B
		*/
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		/*!
		*@brief �萔�o�b�t�@�B
		*@todo �����͒萔�o�b�t�@����
		*/
		struct SConstantBuffer {
			CMatrix mViewProjInv;			//!<�r���[�v���W�F�N�V�����s��̋t�s��B
			CMatrix mViewProj;				//!<�r���[�v���W�F�N�V�����s��B
			CMatrix mViewProjInvLastFrame;	//!<1�t���[���O�̃r���[�v���W�F�N�V�����s��̋t�s��B
			CVector4 cameraPos;				//!<�J�����̎��_�B
			CVector4 renderTargteSize;		//!<�����_�����O�^�[�Q�b�g�̃T�C�Y�B
			float rayMarchStepRate;			//!<���C�}�[�`�̃X�e�b�v���[�g�B
		};
		bool m_isEnable = false;					//!<�L���B
		CShader m_vsShader;							//!<���_�V�F�[�_�[�B
		CShader m_psShader;							//!<�s�N�Z���V�F�[�_�[�B
		CShader m_psFinalShader;					//!<�ŏI�����V�F�[�_�[�B
		CConstantBuffer m_cb;						//!<�萔�o�b�t�@�B
		std::random_device m_rd;					//!<���ɉe����^���Ȃ��悤�ɁA�����������ŗ�����ێ�����B
		std::mt19937 m_mt;							//!<�����Z���k�c�C�X�^�[���g�p��������������B
		int m_currentRTNo = 0;						//!<
		static const int NUM_CALC_AVG_RT = 1;				//!<���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�̖����B
		CRenderTarget m_reflectionRT[NUM_CALC_AVG_RT];		//!<���t���N�V�������������ރ����_�����O�^�[�Q�b�g�B
		CBlur m_blur;
		CMatrix m_viewProjInvLastFrame = CMatrix::Identity;
	};
}