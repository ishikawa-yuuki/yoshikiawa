/*!
 *@brief	�|�C���g���C�g
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/light/tkPointLight.h"

namespace tkEngine{
	namespace prefab {
		CPointLight::CPointLight()
		{
			light.color = CVector3::One;
			light.position = CVector3::Zero;
			light.positionInView = CVector3::Zero;
			light.attn.Set(10.0f, 1.0f, 0.0f, 0.0f);
		}
		CPointLight::~CPointLight()
		{

		}
		void CPointLight::SetPosition(const CVector3& pos)
		{
			light.position = pos;
		}
		void CPointLight::SetColor(const CVector3& color)
		{
			light.color = color;
		}
		void CPointLight::SetAttn(const CVector3& attn)
		{
			light.attn = attn;
			if (light.attn.y <= 0.0f) {
				TK_WARNING("attn.y�̒l���s���ł��B���̒l�͕K��0���傫�Ȓl��ݒ肷��悤�ɂ��Ă��������B");
				light.attn.y = max(0.001f, light.attn.y);
			}
		}
		bool CPointLight::StartSub()
		{
			return true;
		}
		void CPointLight::Update()
		{
			//�J������Ԃł̈ʒu���v�Z����B
			const CMatrix& mView = MainCamera().GetViewMatrix();
			light.positionInView = light.position;
			mView.Apply(light.positionInView);
			light.lightingMaterialIDGroup = GetLightingMaterialIDGroup();
		}
	}
}