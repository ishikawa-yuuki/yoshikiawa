/*!
 * @brief	�S���ʃV���h�E�}�b�v
 */

#pragma once

#include "tkEngine/graphics/preRender/shadow/tkIShadowMap.h"
#include <array>

namespace tkEngine{
	class IShadowCaster;
	/*!
	 * @brief	�S���ʃV���h�E�}�b�v�B
	 */
	class COminiDirectionShadowMap : public IShadowMap{
	public:
		
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		COminiDirectionShadowMap();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~COminiDirectionShadowMap();
		/*!
		 * @brief	�V���h�E�}�b�v�̍쐬�B
		 *@param[in]	config		�R���t�B�O�B
		 *@return	true���Ԃ��Ă�����V���h�E�}�b�v�̍쐬�����B
		 */
		bool Init( const SOminiShadowRenderConfig& config );
		/*!
		* @brief	�X�V�B
		*/
		void Update();
		/*!
		 *@brief	�e�𗎂Ƃ����߂̃p�����[�^��GPU�ɓ]������B
		 */
		void SendShadowReceiveParamToGPU(CRenderContext& rc);
		
		/// <summary>
		/// ���C�g�̍��W��ݒ肷��B
		/// </summary>
		/// <param name="pos">���C�g�̍��W</param>
		void SetLightPosition(CVector3 pos)
		{
			m_ominiDirectionShadowCbCPU.lightPosition = pos;
		}
		/// <summary>
		/// ���C�g�̉e�����󂯂鋗����ݒ肷��B
		/// </summary>
		/// <param name="distance">����</param>
		void SetDistanceAffectedByLight(float distance)
		{
			m_ominiDirectionShadowCbCPU.distanceAffectedByLight = distance;
		}
		/// <summary>
		/// �ߕ��ʂ܂ł̃N���b�v������ݒ�B
		/// </summary>
		/// <param name="n">�ߕ��ʂ܂ł̋���</param>
		void SetNearClip(float n)
		{
			m_near = n;
		}
		/// <summary>
		/// �V���h�E�o�C�A�X��ݒ�B
		/// </summary>
		/// <remarks>
		/// �Z���t�V���h�E�Ŕ�������V���h�E�A�N�l��������邽�߂�
		/// �p�����[�^�ł��B�傫�Ȓl������Ɖe�������ɂ����Ȃ�܂��B
		/// </remarks>
		/// <param name="bias"></param>
		void SetShadowBias(float bias)
		{
			m_ominiDirectionShadowCbCPU.shadowBias = bias;
		}
	private:
		/// <summary>
		/// �V���h�E�}�b�v�p�̃e�N�X�`�����쐬�B
		/// </summary>
		bool InitShadowMapTextures(ID3D11Device* pD3DDevice);
		/// <summary>
		/// �����_�����O�^�[�Q�b�g�r���[���쐬�B
		/// </summary>
		/// <returns></returns>
		bool InitRenderTargetViews(ID3D11Device* pD3DDevice);
		/// <summary>
		/// �f�v�X�X�e���V���e�N�X�`�����쐬�B
		/// </summary>
		/// <returns></returns>
		bool InitDepthStencilTextures(ID3D11Device* pD3DDevice);
		/// <summary>
		/// �f�v�X�X�e���V���r���[���������B
		/// </summary>
		/// <param name="pD3DDevice"></param>
		/// <returns></returns>
		bool InitDepthStencilViews(ID3D11Device* pD3DDevice);
		/*!
		 *@brief	�V���h�E�}�b�v�֏������݁B
		 */
		void RenderToShadowMapImp(CRenderContext& rc) override;
	private:
		enum { NUM_TEXTURE = 6 }; //�e�N�X�`���̐��B
		/// <summary>
		/// �萔�o�b�t�@�\����
		/// </summary>
		/// <remarks>
		/// GPU�ɑ��肽���p�����[�^�͂��̍\���̂ɓ����B
		/// ���̍\���̂̃����o��ύX������Ashader/modelCB.h��
		/// OminiDirectionShadowCb���ύX����悤�ɁB
		/// </remarks>
		struct SOminiDirectionShadowCb {
			CMatrix lightViewProjMatrix[NUM_TEXTURE] = {CMatrix::Identity};	//���C�g�r���[�v���W�F�N�V�����s��B
			CVector3 lightPosition = CVector3::Zero;	//�����̍��W�B
			float distanceAffectedByLight = 100;		//���C�g�̉e�����󂯂鋗���B
			float shadowBias = 0.001f;					//�V���h�E�o�C�A�X�B
		};
		
		ID3D11Texture2D* m_shadowMap = nullptr;	//�V���h�E�}�b�v�B���I�L���[�u�}�b�v�B6�ʃ����_�����O���s�����ƂŁA�S���ʃV���h�E����������B
		std::array< ID3D11RenderTargetView*, NUM_TEXTURE> m_renderTargets;	//�����_�����O�^�[�Q�b�g�B
		ID3D11Texture2D* m_depthStencilTexture = nullptr;					//�f�v�X�X�e���V���e�N�X�`���B
		ID3D11DepthStencilView* m_depthStencilView = nullptr;				//�f�v�X�X�e���V���r���[�B	
		D3D11_TEXTURE2D_DESC m_texDesc = { 0 };								//�e�N�X�`����`�B
		D3D11_TEXTURE2D_DESC m_depthTexDesc = { 0 };						//�f�v�X�X�e���V���e�N�X�`���̒�`�B
		CShaderResourceView m_shadowMapSRV;									//�V���h�E�}�b�v��SRV�B
		SOminiDirectionShadowCb m_ominiDirectionShadowCbCPU;				//CPU���̒萔�o�b�t�@
		CConstantBuffer m_ominiDirectionShadowCbGPU;						//GPU���̒萔�o�b�t�@�B
		float m_near = 1.0f;
	};
}