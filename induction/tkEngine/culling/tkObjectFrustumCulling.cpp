/*!
 *@brief	�t���X�^���J�����O�����B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CObjectFrustumCulling::CObjectFrustumCulling()
	{
	}
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	CObjectFrustumCulling::~CObjectFrustumCulling()
	{
	}
	/*!
	 *@brief	�J�����O�A���S���Y���̎��s�B
	 */
	void CObjectFrustumCulling::Execute(const CBox& box)
	{
		if (m_camera != nullptr) {
			const CMatrix& viewProjMatrix = m_camera->GetViewProjectionMatrix();
			SetCullingFlag(false);
			//CBox�̂W���_���X�N���[����Ԃ̐��K�����W�n�ɕϊ�����B
			//x�Ay��1.0�`-1.0�Az��0.0�`1.0�͈͓̔��ɂ������ʓ��ɂ���Ƃ������ƂɂȂ�B
			//8���_���ׂĂ���ʂ̊O�Ȃ�J�����O����B
			auto vMax = CVector3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
			auto vMin = CVector3(FLT_MAX, FLT_MAX, FLT_MAX);
			for (int i = 0; i < 8; i++) {
				CVector4 vertPos(box.GetVertexPosition(i));
				viewProjMatrix.Apply(vertPos);
				vertPos.x /= vertPos.w;
				vertPos.y /= vertPos.w;
				vertPos.z /= vertPos.w;
				vMax.Max({ vertPos.x, vertPos.y, vertPos.z });
				vMin.Min({ vertPos.x, vertPos.y, vertPos.z });
			}
			//�I�u�W�F�N�g�̉�����
			if (vMax.x < -1.0f
				|| vMin.x > 1.0f
				|| vMax.y < -1.0f
				|| vMin.y > 1.0f
				) {
				SetCullingFlag(true);
			}
		}
	}
}
