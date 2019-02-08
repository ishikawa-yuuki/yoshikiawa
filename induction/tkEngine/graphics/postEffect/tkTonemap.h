/*!
 *@brief	�g�[���}�b�v�B
 */
#pragma once

namespace tkEngine{
	/*!
	 *@brief	�g�[���}�b�v�B
	 */
	class CTonemap{
	public:
		CTonemap();
		~CTonemap();
		/*!
		*@brief	�쐬�B
		*@param[in]		config		�O���t�B�b�N�ݒ�B
		*/
		void Init(const SGraphicsConfig& config);
		void Release();
		/*!
		 *@brief	���ϋP�x�̌v�Z�B
		 *@param[in]	renderContext		�����_�����O�R���e�L�X�g
		 */
		void CalcLuminanceAvarage(CRenderContext& renderContext, CPostEffect* postEffect);
		/*!
		 *@brief	�g�[���}�b�v�̎��s�B
		 *@details
		 * ���̊֐����ĂԑO��CalcLuminanceAvarage���R�[�����ĕ��ϋP�x�̌v�Z���s���Ă��������B
		 * ���ϋP�x�̌v�Z�̓|�X�g�G�t�F�N�g�̐퓬�ōs���Ă��������B
		 *@param[in]	renderContext		�����_�����O�R���e�L�X�g
		 */
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);
		/*!
		*@brief	�g�[���}�b�v�̏��������Z�b�g�B
		*@details
		*�@�P�x���傫���ς��V�[���؂�ւ��Ȃǂ���������ꍇ�Ȃǂɖ��Ï�������������������ꍇ������܂��B
		* ���̂悤�ȏꍇ�̓V�[���؂�ւ��̃^�C�~���O�Ń��Z�b�g���s���Ă݂Ă��������B
		*/
		void Reset()
		{
			m_isFirstWhenChangeScene = true;
		}
		/*!
		*@brief	 ���邳��ݒ�B
		*@@param[in]	lum		���邳�B���̒l��傫������Ɩ��邭�Ȃ�B
		*/
		void SetLuminance(float lum)
		{
			m_tonemapParam.midddleGray = lum;
		}
		/*!
		*@brief	 �g�[���}�b�v�̗L��������ݒ�B
		*/
		void SetEnable(bool flag)
		{
			m_isEnable = flag;
		}
	public:
		static const int MAX_SAMPLES = 16;
	private:
		struct STonemapParam {
			float deltaTime;
			float midddleGray;
		};
		static const int NUM_CALC_AVG_RT = 5;				//!<���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�̖����B
//		CEffect*		m_effect = nullptr;					//!<�G�t�F�N�g�B
		bool			m_isEnable = false;					//!<�g�[���}�b�v�L���H
		CRenderTarget	m_calcAvgRT[NUM_CALC_AVG_RT];		//!<���ϋP�x�v�Z�p�̃����_�����O�^�[�Q�b�g�B
		CRenderTarget   m_avgRT[2];							//!<���ϋP�x���i�[����郌���_�����O�^�[�Q�b�g�B
		int				m_currentAvgRT = 0;					//!<
		CShader			m_vsShader;							//!<���_�V�F�[�_�[�B
		CShader			m_psCalcLuminanceLogAvarageShader;	//!<�P�x�̑ΐ����ς����߂�s�N�Z���V�F�[�_�[�B
		CShader			m_psCalcLuminanceAvarageShader;		//!<�P�x�̕��ς����߂�s�N�Z���V�F�[�_�[�B
		CShader			m_psCalcLuminanceExpAvarageShader;	//!<�P�x�̎w�����ς����߂�s�N�Z���V�F�[�_�[�B
		CShader			m_psCalcAdaptedLuminanceShader;		//!<���Ï����̃s�N�Z���V�F�[�_�[�B
		CShader			m_psCalcAdaptedLuminanceFirstShader;	//!<���Ï����̃s�N�Z���V�F�[�_�[�B(�V�[�����؂�ւ�����Ƃ��Ɏg�p�����B)
		CShader			m_psFinal;							//!<�ŏI�����V�F�[�_�[�B
		bool			m_isFirstWhenChangeScene = true;	//!<�V�[�����؂�ւ���ď���̕`�悩�ǂ����̃t���O�B
		CVector4		m_avSampleOffsets[MAX_SAMPLES];
		CConstantBuffer	m_cbCalcLuminanceLog;
		CConstantBuffer m_cbTonemapCommon;
		STonemapParam	m_tonemapParam;
	};
}