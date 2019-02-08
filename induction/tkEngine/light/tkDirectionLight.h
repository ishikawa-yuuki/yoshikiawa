/*!
 *@brief	�f�B���N�V�������C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	�f�B���N�V�������C�g�B
		 */
		class CDirectionLight : public CLightBase {
		public:
			CDirectionLight();
			~CDirectionLight();
			bool StartSub() override final;
			void Update() override final;
			/*!
			*@brief ���C�g�̕�����ݒ�B
			*@param[in]	direction	���C�g�̕����B
			*/
			void SetDirection(const CVector3& direction);
			/*!
			 *@brief	�f�B���N�V�������C�g���擾�B
			 */
			const CVector3& GetDirection() const
			{
				return m_light.direction;
			}
			/*!
			*@brief ���C�g�̃J���[��ݒ�B
			*@param[in]	color	���C�g�̃J���[�B
			*/
			void SetColor(const CVector4& color);
			/*!
			*@brief ���f�[�^�̎擾�B
			*/
			SDirectionLight& GetRawData()
			{
				return m_light;
			}
			
		private:
			SDirectionLight		m_light;		//!<���C�g�B
			
		};
	}
}