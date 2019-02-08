/*!
 * @brief	G-Buffer��`��B
 */

#pragma once

#include "tkEngine/graphics/tkShadowBlur.h"

namespace tkEngine{
	//!<G-Buffer�̒�`�B
	enum EnGBuffer{
		enGBufferAlbedo,		//!<�A���x�h�B
		enGBufferNormal,		//!<�@���B
		enGBufferSpecular,		//!<�X�y�L�����B
		enGBufferShadow,		//!<�e�}�b�v�B
		enGBufferDepth,			//!<�[�x�Bx�ɂ͎ˉe��Ԃł̐[�x�l�Ay�ɂ̓J������Ԃł̐[�x�l���L�^����Ă���B
		enGBufferTangent,		//!<�ږ@���B
		enGBufferMateriaID,		//!<�}�e���A��ID�B
		enGBufferEmission,		//!<���Ȕ����F�B
		enGBufferNum,			//!<G-Buffer�̐��B
	};
	/*!
	 * @brief	G-Buffer�B
	 */
	class CGBufferRender : Noncopyable{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CGBufferRender();
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CGBufferRender();
		/*!
		 *@brief	�������B
		 */
		void Init(const SGraphicsConfig& config);
		/*!
		*@brief	�X�L�����f����ǉ��B
		*/
		void AddSkinModel(CSkinModel* skinModel)
		{
			m_skinModels.push_back(skinModel);
		}
		/*!
		*@brief	�X�L�����f���������B
		*/
		void RemoveSkinModel(CSkinModel* skinModel)
		{
			auto it = std::find(m_skinModels.begin(), m_skinModels.end(), skinModel);
			if (it != m_skinModels.end() ){
				m_skinModels.erase(it);
			}
		}
		/*!
		 * @brief	�`��B
		 */
		void Render(CRenderContext& rc);
		/*!
		*@brief	GBuffer�̃p�����[�^�����W�X�^�ɐݒ�B
		*/
		void SetGBufferParamToReg(CRenderContext& rc);
		/*!
		*@brief	GBuffer�����W�X�^����O���B
		*/
		void UnsetGBufferParamFromReg(CRenderContext& rc);
		/*!
		*@brief	GBuffer���擾�B
		*@param[in]	enGBuffer	�擾������G-Buffer
		*/
		CRenderTarget& GetRenderTarget(EnGBuffer enGBuffer) 
		{
			return m_GBuffer[enGBuffer];
		}
		CShaderResourceView& GetDepthTextureLastFrameSRV()
		{
			return m_depthTextureLastFrameSRV;
		}
	private:
		
		//�萔�p�����[�^�B
		struct SCBParam {
			bool isPCFShadowMap;		//�e�}�b�v�����Ƃ���PCF���s���B
		};
		std::vector<CSkinModel*>	m_skinModels;	//!<�X�L�����f���̃��X�g�B
		CRenderTarget m_GBuffer[enGBufferNum];		//!<G-Buffer
		ID3D11Texture2D* m_depthTextureLastFrame;		//!<1�t���[���O�̐[�x�e�N�X�`���B
		CShaderResourceView m_depthTextureLastFrameSRV;	//!<1�t���[���O�̐[�x�e�N�X�`����SRV�B
		CShadowBlur m_shadowBlur;					//!<�e�}�b�v�ւ̃u���[�����B
		SCBParam m_cbEntity;
		CConstantBuffer m_cb;
	};
}
