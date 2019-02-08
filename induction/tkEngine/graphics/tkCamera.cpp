/*!
 * @brief	�J����
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	CCamera::CCamera() :
		m_near(1.1f),
		m_far(5000.0f),
		m_viewAngle(CMath::DegToRad(60.0f)),
		m_aspect(1.0f),
		m_isNeedUpdateProjectionMatrix(true),
		m_position( CVector3::Zero),
		m_up( CVector3::Up),
		m_target( CVector3::Zero),
		m_viewMatrix( CMatrix::Identity ),
		m_projectionMatrix( CMatrix::Identity ),
		m_viewProjectionMatrix( CMatrix::Identity ),
		m_viewMatrixInv( CMatrix::Identity )
	{
	}
	CCamera::~CCamera()
	{
	}
	/*!
	 * @brief
	 */
	void CCamera::Update()
	{
#if BUILD_LEVEL != BUILD_LEVEL_MASTER

		if (m_isDebugCamera) {
			//�f�o�b�O���[�h�B�r���[�s��̂ݕύX����B
			//�r���[�s��̎Z�o
			m_viewMatrix.MakeLookAt(m_debugCameraPosition, m_debugCameraTarget, m_up);
			//�r���[�v���W�F�N�V�����s��̍쐬�B
			m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
			//�r���[�s��̋t�s����v�Z�B
			m_viewMatrixInv.Inverse(m_viewMatrix);
			return;
		}
#endif
		m_aspect = (float)GraphicsEngine().GetFrameBufferWidth() / (float)GraphicsEngine().GetFrameBufferHeight();
		if(m_isNeedUpdateProjectionMatrix){
			if (m_updateProjMatrixFunc == enUpdateProjMatrixFunc_Perspective) {
				//�����ϊ��s����v�Z�B
				m_projectionMatrix.MakeProjectionMatrix(
					m_viewAngle,
					m_aspect,
					m_near,
					m_far
				);
			}
			else {
				//���s���e�s����v�Z�B
				m_projectionMatrix.MakeOrthoProjectionMatrix(m_width, m_height, m_near, m_far);
			}
		}
		//�r���[�s��̎Z�o
		m_viewMatrix.MakeLookAt( m_position, m_target, m_up );
		//�r���[�v���W�F�N�V�����s��̍쐬�B
		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
		//�r���[�s��̋t�s����v�Z�B
		m_viewMatrixInv.Inverse( m_viewMatrix );

		m_forward.Set(m_viewMatrixInv.m[2][0], m_viewMatrixInv.m[2][1], m_viewMatrixInv.m[2][2]);
		m_right.Set(m_viewMatrixInv.m[0][0], m_viewMatrixInv.m[0][1], m_viewMatrixInv.m[0][2]);
		//�J�����̉�]�s����擾�B
		m_cameraRotation = m_viewMatrixInv;
		m_cameraRotation.m[3][0] = 0.0f;
		m_cameraRotation.m[3][1] = 0.0f;
		m_cameraRotation.m[3][2] = 0.0f;
		m_cameraRotation.m[3][3] = 1.0f;

		CVector3 toPos;
		toPos.Subtract(m_position, m_target);
		m_targetToPositionLen = toPos.Length();
	}
	void CCamera::CalcScreenPositionFromWorldPosition(CVector2& screenPos, const CVector3& worldPos) const
	{
		float half_w = (float)GraphicsEngine().GetFrameBufferWidth() * 0.5f;
		float half_h = (float)GraphicsEngine().GetFrameBufferHeight() * 0.5f;
		CVector4 _screenPos;
		_screenPos.Set(worldPos.x, worldPos.y, worldPos.z, 1.0f);
		m_viewProjectionMatrix.Apply(_screenPos);
		screenPos.x = (_screenPos.x / _screenPos.w)*half_w;
		screenPos.y = (_screenPos.y / _screenPos.w)*half_h;
	}
}

