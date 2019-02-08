/*!
 *@brief	���C�g�J�����O
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	���C�g�J�����O�B
	 *@details
	 * TBFR�̓��I�����̃^�C���x�[�X�̃J�����O�̏����B
	 */
	class CLightCulling{
	public:
		static const int TILE_WIDTH = 16;
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CLightCulling();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CLightCulling();
		/*!
		*@brief	�������B
		*/
		void Init();
		/*!
		 *@brief	���C�g�J�����O�̎��s�B
		 */
		void Render(CRenderContext& rc);
	private:
		//�J�����p�����[�^�B
		struct SCameraParam {
			CMatrix mProj;			//�v���W�F�N�V�����s��B
			CMatrix mProjInv;		//�v���W�F�N�V�����s��̋t�s��B
			CMatrix mViewRot;		//�J�����̉�]�s��̋t�s��B
			CVector4 screenParam;	//�X�N���[���p�����[�^�B
			int numPointLight;		//�|�C���g���C�g�̐��B
		};
		
		SCameraParam	m_cameraParam;			//�J�����p�����[�^�B
		CConstantBuffer m_cameraParamCB;	//�J�����p�̒萔�o�b�t�@�B
		CShader			m_csLightCulling;		//!<���C�g�J�����O�p�̃R���s���[�g�V�F�[�_�[�B
	};
}