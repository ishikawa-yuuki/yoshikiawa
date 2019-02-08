/*!
 * @brief	���C�g�̊Ǘ��ҁB
 */

#pragma once
#include "tkEngine/graphics/tkLight.h"

namespace tkEngine{
	namespace prefab {
		class CDirectionLight;
		class CPointLight;
		class CLightBase;
	}
	/*!
	 * @brief	���C�g�̊Ǘ���
	 * @details
	 *  �C���X�^���X�����ꂽCLightBase�̃C���X�^���X�͂��ׂ�CLightManager�ɓo�^����܂��B
	 *  ���̃N���X�̃C���X�^���X��CGraphicsEngine�N���X�݂̂��ێ����Ă���A���̑��̃N���X�ŃC���X�^���X�𐶐����邱�Ƃ͂ł��܂���B
	 */
	class CLightManager{
	friend class CGraphicsEngine;
	private:
		CLightManager();
		~CLightManager();
	public:
		void Init();
		/*!
		*@brief�@���C�g��ǉ��B
		*/
		void AddLight(prefab::CLightBase* light);
		/*!
		*@brief�@���C�g���폜�B
		*/
		void RemoveLight(prefab::CLightBase* light);
		/*!
		*@brief�@�X�V�B
		*/
		void Update();
		/*!
		*@brief�@�`��V�[�P���X����Ă΂�鏈���B
		* �X�g���N�`���[�o�b�t�@�̍X�V��A���I���C�g�̃V�F�[�_�[���\�[�X��ݒ肷��B
		*/
		void Render(CRenderContext& renderContext);
		/*!
		*@brief�@�P�t���[���̕`��I�����ɌĂ΂�鏈���B
		*/
		void EndRender(CRenderContext& renderContext);
		/*!
		*@brief�@�|�C���g���C�g��SRV���擾�B
		*/
		CShaderResourceView& GetPointLightsSRV()
		{
			return m_pointLightsSB.GetSRV();
		}
		/*!
		*@brief�@�e�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�̃X�g���N�`���[�o�b�t�@��UAV���擾�B
		*/
		CUnorderedAccessView& GetPointLightsInTileUAV()
		{
			return m_pointLightsInTileSB.GetUAV();
		}
		/*!
		*@brief�@�|�C���g���C�g�̐����擾�B
		*/
		int GetNumPointLight() const
		{
			return static_cast<int>(m_pointLights.size());
		}

		/*!
		 *@brief	�A���r�G���g���C�g���擾�B
		 */
		const CVector3& GetAmbientLight() const
		{
			return m_lightParam.ambientLight;
		}
		/*!
		 *@brief	�A���r�G���g���C�g��ݒ�B
		 */
		void SetAmbientLight(const CVector3& ambient)
		{
			m_lightParam.ambientLight = ambient;
		}
	private:
		void InitDirectionLightStructuredBuffer();
		void InitPointLightStructuredBuffer();
		void InitPointLightInTileStructuredBuffer();
	private:
		static const int MAX_DIRECTION_LIGHT = 8;						//!<�f�B���N�V�������C�g�̍ő吔�B
		static const int MAX_POINT_LIGHT = 1024;						//!<�|�C���g���C�g�̍ő吔�B
		/*!
		 *@brief	GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�B
		 *@details
		 * �����o�ϐ���ǉ�������A���т�ς����肵����
		 * Assets/shader/modelCB.h��lightCb���ς���K�v����B
		 */
		struct SLightParam {
			CVector3 eyePos;			//�����̈ʒu�B
			int numDirectionLight;		//�f�B���N�V�������C�g�̐��B
			CVector3 ambientLight;		//�A���r�G���g���C�g�B
			int numPointLight;			//�|�C���g���C�g�̐��B
			CVector4 screenParam;		//�X�N���[���p�����[�^�B
		};
		SLightParam							m_lightParam;
		CConstantBuffer						m_lightParamCB;			//!<GPU�Ŏg�p���郉�C�g�p�̃p�����[�^�̒萔�o�b�t�@�B
		SDirectionLight						m_rawDirectionLights[MAX_DIRECTION_LIGHT];
		SPointLight							m_rawPointLights[MAX_POINT_LIGHT];
		std::list<prefab::CDirectionLight*>	m_directionLights;		//!<���s�����̃��X�g�B
		CStructuredBuffer					m_directionLightSB;		//!<���s�����̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		std::list<prefab::CPointLight*>		m_pointLights;			//!<�|�C���g���C�g�̃��X�g�B
		CStructuredBuffer					m_pointLightsSB;		//!<�|�C���g���C�g�̃��X�g�̃X�g���N�`���[�o�b�t�@�B
		CStructuredBuffer					m_pointLightsInTileSB;	//!<�e�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�̃X�g���N�`���[�o�b�t�@�B

	};
}