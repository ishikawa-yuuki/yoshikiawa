/*!
 *@brief	���Ȕ������C�g
 */

#pragma once

#include "tkEngine/graphics/tkLight.h"
#include "tkEngine/light/tkLightBase.h"

namespace tkEngine{
	namespace prefab {
		/*!
		 *@brief	���Ȕ������C�g�B
		 */
		class CEmissionLight : public CLightBase {
		public:
			CEmissionLight();
			~CEmissionLight();
			/*!
			 *@brief	���Ȕ����F��ݒ肷��B
			 *@param[in]	color		���Ȕ����F�B
			 */
			void SetColor( const CVector4& color )
			{
			}
		private:
		};
	}
}