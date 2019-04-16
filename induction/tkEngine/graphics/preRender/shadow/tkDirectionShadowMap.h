/*!
 * @brief	�w�����V���h�E�}�b�v
 */

#pragma once

#include "tkEngine/graphics/preRender/shadow/tkIShadowMap.h"

namespace tkEngine{
	class IShadowCaster;
	/*!
	 * @brief	�w�����V���h�E�}�b�v�B
	 */
	class CDirectionShadowMap : public IShadowMap{
	public:
		
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CDirectionShadowMap();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CDirectionShadowMap();
		/*!
		 * @brief	�V���h�E�}�b�v�̍쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 *@return	true���Ԃ��Ă�����V���h�E�}�b�v�̍쐬�����B
		 */
		bool Init( const SShadowRenderConfig& config );
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/*!
		 *@brief	�e�𗎂Ƃ����߂̃p�����[�^��GPU�ɓ]������B
		 */
		void SendShadowReceiveParamToGPU(CRenderContext& rc);
		
		/*!
		* @brief	�J���B
		*/
		void Release();
		/*!
		 *@brief	���C�g�̕�����ݒ�B
		 */
		void SetLightDirection(const CVector3 lightDir)
		{
			m_lightDirection = lightDir;
			m_lightDirection.Normalize();
		}
		/*!
		 *@brief	���C�g�̍�����ݒ�B
		 */
		void SetLightHeight(float h)
		{
			m_lightHeight = h;
		}
		/*!
		 *@brief	�\�t�g�V���h�E���L���H
		 */
		EnSoftShadowQualityLevel GetSoftShadowLevel() const
		{
			return m_softShadowLevel;
		}
	private:
		/// <summary>
		/// ���C�g�̍��W���v�Z����B
		/// </summary>
		/// <remarks>
		/// �������ꂽ��������ʂ����C�g�̍��W���v�Z���܂��B
		/// ���C�g�̍��W�̌v�Z�̓��C�g�̍����A���C�g�̕����A�����āA
		/// ������̒��S���W(�ߕ��ʂ̒��S���W�Ɖ����ʂ̒��S���W�����񂾐����̒��_���W)
		/// ����v�Z����܂��B
		/// �����̃p�����[�^�����ƂɃ��C�g�̍��W�͉��L�̌v�Z�ŋ��߂��܂��B
		/// 
		/// �@�@���m�����ɂ��Ă̈ꎟ�������������܂��B
		/// ���C�g�̍��� = ������̒��S���W.y + ���C�g�̕���.y * ��
		/// �� = ( ���C�g�̍��� - ������̒��S���W.y ) / ���C�g�̕���.y
		/// �A�@�����g���āA���C�g�̍��W�����߂�B
		/// ���C�g�̍��W = ������̒��S���W + ���C�g�̕��� * ��
		/// </remarks>
		/// <param name="lightHeight">
		/// ���C�g�̍����B
		/// </param>
		/// <param name="viewFrustomCenterPosition">
		/// �������ꂽ������̒��S���W�B
		/// </param>
		/// <returns>�v�Z���ꂽ���C�g�̍��W</returns>
		CVector3 CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition);
		/*!
		 *@brief	�V���h�E�}�b�v�֏������݁B
		 */
		void RenderToShadowMapImp(CRenderContext& rc) override;
	private:
		/*!
		 *@brief	���̒��g��ύX������AmodelCB.h��ShadowCb���ύX����悤�ɁB
		 */
		struct SShadowCb {
			CMatrix mLVP[NUM_SHADOW_MAP];
			CVector4 texOffset[NUM_SHADOW_MAP];
			float depthOffset[NUM_SHADOW_MAP];
			float pading;
			float shadowAreaDepthInViewSpace[NUM_SHADOW_MAP];	//�J������Ԃł̉e�𗎂Ƃ��G���A�̐[�x�e�[�u���B
		};
		CVector3 m_lightDirection = CVector3::Down;			//!<���C�g�̕����B
		float m_lightHeight = UnitM(20.0f);				//!<���C�g�̍����B
		float m_accpect = 1.0f;								//!<�A�X�y�N�g�B�s�v�H
		float m_shadowAreaW[NUM_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̕��B
		float m_shadowAreaH[NUM_SHADOW_MAP] = {0};			//!<�e�𗎂Ƃ��͈͂̍����B
		CRenderTarget	m_shadowMapRT[NUM_SHADOW_MAP];		//!<�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
		CMatrix	m_LVPMatrix[NUM_SHADOW_MAP] = { CMatrix::Identity };				//!<���C�g�r���[�v���W�F�N�V�����s��B
		SShadowCb m_shadowCbEntity;
		CConstantBuffer m_shadowCb;							//!<�e�𗎂Ƃ����Ɏg�p����萔�o�b�t�@�B
		EnSoftShadowQualityLevel m_softShadowLevel = EnSoftShadowQualityLevel::enNone;							//!<�\�t�g�V���h�E�̃��x���B
		CSamplerState m_fetchShadowMapSampler;	//�V���h�E�}�b�v���t�F�b�`����Ƃ��Ɏg�p����T���v���B
	};
}