/*!
 * @brief	�u���[��
 */
#pragma once

namespace tkEngine{
	class CPostEffect;
	/*!
	 * @brief	�u���[��
	 */
	class CBloom : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CBloom();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CBloom();
		/*!
		 * @brief	�J��
		 */
		void Release();
		/*!
		 * @brief	�������B
		 */
		void Init( const SGraphicsConfig& config );
		/*!
		 * @brief	�`��
		 */
		void Render(CRenderContext& rc, CPostEffect* postEffect);
	private:
		/*!
		* @brief	�K�E�X�t�B���^�̏d�݂��X�V�B
		*/
		void UpdateWeight(float dispersion);
	private:
		
		static const int NUM_WEIGHTS = 8;
		static const int NUM_DOWN_SAMPLING_RT = 10;
		/*!
		* @brief	�u���[�p�̃p�����[�^�o�b�t�@�B
		*@details
		* �����ύX������AAssets/shader/bloom.fx��CBBlur�̒��g���ύX����悤�ɁB
		*/
		struct SBlurParam {
			CVector4 offset;
			float weights[NUM_WEIGHTS];
		};
		bool m_isEnable = false;		//!<�L���B
		CRenderTarget m_luminanceRT;	//!<�P�x�𒊏o���郌���_�����O�^�[�Q�b�g�B
		CRenderTarget m_combineRT;		//!<�ڂ��������p�̃����_�����O�^�[�Q�b�g�B
		CRenderTarget m_downSamplingRT[NUM_DOWN_SAMPLING_RT];	//!<�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
		CShader m_vsShader;	
		CShader m_psLuminance;			//!<�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
		CShader m_vsXBlur;				//!<XBlur�p�̒��_�V�F�[�_�[�B
		CShader m_vsYBlur;				//!<YBlur�p�̒��_�V�F�[�_�[�B
		CShader m_psBlur;				//!<XBlur�p�̃s�N�Z���V�F�[�_�[�B
		CShader m_psCombine;			//!<�����p�̃s�N�Z���V�F�[�_�[�B
		CShader	m_copyVS;				//!<�R�s�[�p�̒��_�V�F�[�_�[�B
		CShader	m_copyPS;				//!<�R�s�[�p�̃s�N�Z���V�F�[�_�[�B
		SBlurParam m_blurParam;			//!<�u���[�p�̃p�����[�^�B
		CConstantBuffer m_cbBlur;
		CConstantBuffer m_cb;
	};
}