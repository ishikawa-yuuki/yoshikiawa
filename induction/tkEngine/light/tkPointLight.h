/*!
 *@brief	�|�C���g���C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	�|�C���g���C�g�B
		 */
		class CPointLight : public CLightBase {
		public:
			CPointLight();
			~CPointLight();
			bool StartSub() override final;
			void Update() override final;
			const CVector3& GetPosition()
			{
				return light.position;
			}
			void SetPosition(const CVector3& pos);
			
			void SetColor(const CVector3& color);
			/*!
			*@brief	�����p�����[�^��ݒ�B
			*@param[in] attn	�����萔�Bx�̓|�C���g���C�g�̉e�����͂��͈́By�̓|�C���g���C�g�̌������ɉe����^���܂��B</br>
			*					y���傫���Ȃ�ƁA�����������Ȃ�܂��B1.0�Ő��`�̌������ɂȂ�܂��Bz�͖��g�p�B
			*/
			void SetAttn(const CVector3& attn);
			
			/*!
			*@brief ���f�[�^�̎擾�B
			*/
			SPointLight& GetRawData()
			{
				return light;
			}
		private:
			SPointLight	light;
		};
	}
}