/*!
 * @brief	�x�N�g�������_���[
 */

#pragma once

namespace tkEngine{
	namespace prefab{
		/*!
		 * @brief	�x�N�g�������_���[�B
		 */
		class CVectorRender : public IGameObject{
		public:

			/*!
			* @brief	�`��f�[�^�B
			*/
			struct SRenderData {
				std::string name;						//���O
				CVector3 vector = CVector3::One;		//�x�N�g���B
				CVector3 origin = CVector3::Zero;		//��_�B
			};
			/*!
			* @brief	�`�悷��x�N�g����ǉ��B
			*/
			void AddVector(SRenderData& renderData)
			{
				m_renderData.push_back(std::move(renderData));
			}
			/*!
			* @brief	�`��t���O��ݒ�B
			*/
			void SetRenderFlag(bool flag)
			{
				m_isRender = flag;
			}
			/*!
			* @brief	�`�悷��x�N�g���̖��O���X�g���w��B
			*/
			void SetRenderVectorNameList(const std::vector<std::string>& list)
			{
				m_renderVectorNameList = list;
			}
		private:
			bool IsRenderVector( const SRenderData& renderData ) const;
			bool Start() override;
			void ForwardRender( CRenderContext& rc ) override;
			void PostRender(CRenderContext& rc) override;
		private:
			bool m_isRender = false;					//!<�`��t���O�B
			std::vector<SRenderData>	m_renderData;	//!<�`��f�[�^�B
			CSkinModel m_model;							//!<���f���B
			CSkinModelData m_modelData;					//!<���f���f�[�^�B
			CFont m_font;								//!<�t�H���g�B
			std::uint32_t m_renderTagMask;				//!<�`�悷��^�O�̃}�X�N
			std::vector<std::string>	m_renderVectorNameList;
		};
	}

}
