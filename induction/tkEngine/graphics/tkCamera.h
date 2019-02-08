/*!
 * @brief	�J����
 */

#ifndef _TKCAMERA_H_
#define _TKCAMERA_H_

namespace tkEngine{
	class CCamera : Noncopyable{
	public:
		/*!
		* @brief	�ˉe�s��̍X�V���@�B
		*/
		enum EnUpdateProjMatrixFunc {
			enUpdateProjMatrixFunc_Perspective,		//!<�����ˉe�s��B���ߖ@���������G����肽���Ȃ炱�����B
			enUpdateProjMatrixFunc_Ortho,			//!<���s���e�B�Q�c�I�ȕ\�����������Ȃ炱�����B
		};
		CCamera();
		~CCamera();
		/*!
		 * @brief	�r���[�s��A�v���W�F�N�V�����s��A�r���[�v���W�F�N�V�����s����X�V�B
		 */
		virtual void Update();
		/*!
		 * @brief	�J�����̍��W��ݒ�B
		 *@param[in]	pos		�J�����̍��W�B
		 */
		void SetPosition( const CVector3& pos ) 
		{
			m_position = pos;
		}
		/*!
		 * @brief	�J�����̍��W���擾
		 *@return	�J�����̍��W�B
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		 * @brief	�����_��ݒ�B
		 *@param[in]	target		�����_�B
		 */
		void SetTarget( const CVector3& target )
		{
			m_target = target;
		}
		/*!
		 * @brief	�����_���擾�B
		 *@return	�����_�B
		 */
		const CVector3& GetTarget() const
		{
			return m_target;
		}
		/*!
		 * @brief	�J�����̏������ݒ�B
		 */
		void SetUp( const CVector3& up )
		{
			m_up = up;
		}
		/*!
		 * @brief	�J�����̏�������擾
		 */
		const CVector3& GetUp() const
		{
			return m_up;
		}
		/*!
		* @brief	�r���[�s��̋t�s����擾�B
		*/
		const CMatrix& GetViewMatrixInv() const
		{
			return m_viewMatrixInv;
		}
		/*!
		 * @brief	�r���[�s����擾�B
		 */
		const CMatrix& GetViewMatrix() const
		{
			return m_viewMatrix;
		}
		
		/*!
		 * @brief	�v���W�F�N�V�����s����擾�B
		 */
		const CMatrix& GetProjectionMatrix() const
		{
			return m_projectionMatrix;
		}
		/*!
		 * @brief	�r���[�v���W�F�N�V�����s����擾�B
		 */
		const CMatrix& GetViewProjectionMatrix() const
		{
			return m_viewProjectionMatrix;
		}
		/*!
		* @brief	�J�����̉�]�s����擾�B
		*/
		const CMatrix& GetCameraRotation() const
		{
			return m_cameraRotation;
		}
		/*!
		 * @brief	�����ʂ�ݒ�B
		 */
		void SetFar( float fFar )
		{
			m_far = fFar;
		}
		/*!
		 * @brief	�ߕ��ʂ�ݒ�B
		 */
		void SetNear( float fNear )
		{
			m_near = fNear;
		}
		/*!
		 * @brief	�����ʂ��擾�B
		 */
		float GetFar() const
		{
			return m_far;
		}
		/*!
		 * @brief	�ߕ��ʂ��擾�B
		 */
		float GetNear() const
		{
			return m_near;
		}
		/*!
		* @brief	���s���e�̕���ݒ�B
		*@details
		* m_updateProjMatrixFunc��enUpdateProjMatrixFunc_Ortho�̎��Ɏg�p�����B
		*/
		void SetWidth(float w)
		{
			m_width = w;
		}
		/*!
		* @brief	���s���e�̍�����ݒ�B
		*@details
		* m_updateProjMatrixFunc��enUpdateProjMatrixFunc_Ortho�̎��Ɏg�p�����B
		*/
		void SetHeight(float h)
		{
			m_height = h;
		}
		/*!
		* @brief	���s���e�̕����擾
		*/
		float GetWidth() const
		{
			return m_width;
		}
		/*!
		* @brief	���s���e�̍������擾
		*/
		float GetHeight() const
		{
			return m_height;
		}
		/*!
		* @brief	���s���e�̍�����ݒ�B
		*@details
		* m_updateProjMatrixFunc��enUpdateProjMatrixFunc_Ortho�̎��Ɏg�p�����B
		*/
		void SetUpdateProjMatrixFunc(EnUpdateProjMatrixFunc func)
		{
			m_updateProjMatrixFunc = func;
		}
		/*!
		* @brief	��p��ݒ�B
		* @details
		*  m_updateProjMatrixFunc��enUpdateProjMatrixFunc_Perspective�̎��Ɏg�p�����B
		*/
		void SetViewAngle(float viewAngle)
		{
			m_viewAngle = viewAngle;
		}
		/*!
		* @brief	��p���擾�B
		*/
		float GetViewAngle() const
		{
			return m_viewAngle;
		}
		/*!
		* @brief	�����_�Ǝ��_�̋������擾�B
		*/
		float GetTargetToPositionLength() const
		{
			return m_targetToPositionLen;
		}
		/*!
		* @brief	�J�����̑O���������擾�B
		*/
		const CVector3& GetForward() const
		{
			return m_forward;
		}
		/*!
		* @brief	�J�����̉E�������擾�B
		*/
		const CVector3& GetRight() const
		{
			return m_right;
		}
		/*!
		 *@brief	�A�X�y�N�g����擾�B
		 */
		float GetAspect() const
		{
			return m_aspect;
		}
		/*!
		*@brief�@�J�����̃R�s�[���쐬�B�B
		*/
		void CopyTo(CCamera& dst) 
		{
			memcpy(&dst, this, sizeof(dst));
		}
		/*!
		* @brief	���[���h���W����X�N���[�����W���v�Z����B
		*@details
		* �v�Z�����X�N���[�����W�͉�ʂ̒��S��{0,0}�A�����{��ʂ̕�*-0.5,��ʂ̍���*-0.5}</br>
		* �E����{��ʂ̕�*0.5,��ʂ̍���*0.5}�Ƃ�����W�ł��B
		*@param[out]	screenPos		�X�N���[�����W�̊i�[��B
		*@param[in]		worldPos		���[���h���W�B
		*/
		void CalcScreenPositionFromWorldPosition(CVector2& screenPos, const CVector3& worldPos) const;

#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		CVector3    m_debugCameraPosition = CVector3::Zero; //!<�f�o�b�O�J�����̍��W�B
		CVector3	m_debugCameraTarget = CVector3::Zero;	//!<�f�o�b�O�J�����̒����_�B
		bool		m_isDebugCamera = false;
#endif

	protected:
		float		m_targetToPositionLen = 1.0f;		//!<�����_�Ǝ��_�܂ŋ����B
		CVector3	m_position;							//!<�J�����ʒu�B
		CVector3	m_up;								//!<�J�����̏�����B
		CVector3	m_target;							//!<�J�����̒��~�_�B
		CMatrix		m_viewMatrix;						//!<�r���[�s��B
		CMatrix		m_projectionMatrix;					//!<�v���W�F�N�V�����s��B
		CMatrix		m_viewProjectionMatrix;				//!<�r���[�v���W�F�N�V�����s��B
		CMatrix		m_viewMatrixInv;					//!<�r���[�s��̋t�s��B
		CMatrix		m_cameraRotation;					//!<�J�����̉�]�s��B
		CVector3	m_forward = CVector3::Front;		//!<�J�����̑O���B
		CVector3	m_right = CVector3::Right;			//!<�J�����̉E�B
		float		m_near;								//!<�ߕ��ʁB
		float		m_far;								//!<�����ʁB
		float		m_viewAngle;						//!<��p(���W�A��)�B
		float		m_aspect;							//!<�A�X�y�N�g��B
		float		m_width = 1280.0f;
		float		m_height = 720.0f;
		EnUpdateProjMatrixFunc m_updateProjMatrixFunc = enUpdateProjMatrixFunc_Perspective;	//!<�v���W�F�N�V�����s��̍X�V�̎d���B
		bool		m_isNeedUpdateProjectionMatrix;

	};
}
#endif //_TKCAMERA_H_