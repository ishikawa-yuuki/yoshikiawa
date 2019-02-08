/*!
 * @brief	�o�l�J����
 */

#pragma once

#include "tkEngine/graphics/tkCamera.h"
#include "tkEngine/camera/tkCameraCollisionSolver.h"

namespace tkEngine{
	/*!
	 * @brief	�o�l�J�����B
	 * @details
	 *  �o�l�Ɉ���������悤�ȃJ�����̋�������������N���X�ł��B\n
	 *  SetTarget�֐���SetPosition�֐����g�p���āA\n
	 *  �J�����̖ڕW�ƂȂ钍���_�Ǝ��_��ݒ肵�Ă��������B\n
	 *  Update�֐������s���邱�ƂŁA�J�������ݒ肳�ꂽ�ڕW���W�ɒǏ]���Ă����܂��B
	 *@code
		
	 *@endcode
	 */
	class CSpringCamera{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		CSpringCamera();
		/*!
		 * @brief	�f�X�g���N�^
		 */
		~CSpringCamera();
		/*!
		* @brief	�������B
		*@param[in]	camera			�J�����B
		*@param[in]	maxMoveSpeed	�J�����̍ő�ړ����x�B
		*@param[in] isEnableCollisionSolver	�R���W����������L���ɂ���H
		*@param[in]	sphereCollisionRadius	���̃R���W�����̔��a�BisEnableCollisionSolover��true�̎��ɗL���ɂȂ�܂��B
		*/
		void Init(
			CCamera& camera,
			float maxMoveSpeed,
			bool isEnableCollisionSolver,
			float sphereCollisionRadius
		);
		/*!
		 * @brief	�ڕW�ƂȂ钍���_��ݒ�B
		 */
		void SetTarget( const CVector3& target )
		{
			m_target = target;
		}
		/*!
		 * @brief	�ڕW�ƂȂ鎋�_��ݒ�B
		 */
		void SetPosition( const CVector3 position )
		{
			m_position = position ;
		}
		
		/*!
		* @brief	�����ʂ�ݒ�B
		*/
		void SetFar(float _far)
		{
			if (m_camera == nullptr) {
				return ;
			}
			m_camera->SetFar(_far);
		}
		/*!
		* @brief	�ߕ��ʂ�ݒ�B
		*/
		void SetNear(float _near)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetNear(_near);
		}
		/*!
		* @brief	�J�����̉�]�s����擾�B
		*/
		const CMatrix& GetCameraRotation() const
		{
			if (m_camera == nullptr) {
				return CMatrix::Identity;
			}
			return m_camera->GetCameraRotation();
		}
		/*!
		 *@brief	�ڕW�ƂȂ钍���_���擾�B
		 *@details
		 * ���̊֐����Ԃ��Ă��钍���_�́A���ۂ̒����_�ł͂Ȃ��̂Œ��ӂ��ĉ������B
		 * ���ۂ̒����_���ق����ꍇ��GetRealTarget���g�p���Ă��������B
		 */
		const CVector3& GetTarget() const
		{
			return m_target;
		}
		/*!
		 *@brief	�ڕW�ƂȂ鎋�_���擾�B
		 *@details
		 * ���̊֐����Ԃ��Ă��鎋�_�́A���ۂ̎��_�ł͂Ȃ��̂Œ��ӂ��Ă��������B
		 * ���ۂ̎n�_���ق����ꍇ��GetRealPosition���g�p���ĉ������B
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		* @brief	���ۂ̒����_���擾�B
		*/
		const CVector3& GetRealTarget() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetTarget();

		}
		/*!
		* @brief	���ۂ̎��_���擾�B
		*/
		const CVector3& GetRealPosition() const
		{
			if (m_camera == nullptr) {
				return CVector3::Zero;
			}
			return m_camera->GetPosition();
		}
		
		/*!
		 * @brief	�X�V�B
		 */
		void Update();
		/*!
		 * @brief	�J�������擾�B
		 */
		const CCamera* GetCamera() const
		{
			return m_camera;
		}
		/*!
		* @brief	�o�l�̌�������ݒ�B
		*@detail
		* �l���傫���قǃJ�������x��ĕt���Ă��܂��B
		*/
		void SetDampingRate(float dampingRate)
		{
			m_targetDampingRate = dampingRate;
		}
		/*!
		* @brief	�J�������擾�B
		*/
		CCamera* GetCamera() 
		{
			return m_camera;
		}
		void SetViewAngle(float angle)
		{
			if (m_camera == nullptr) {
				return;
			}
			m_camera->SetViewAngle(angle);
		}
		float GetViewAngle() const
		{
			if (m_camera == nullptr) {
				return 0.0f;
			}
			return m_camera->GetViewAngle();
		}

		/*!
		* @brief	���t���b�V��
		*@details
		* ���̊֐����Ăяo���ƁA�o�l�̈ړ������t���b�V������āAUpdate�֐����Ăяo���ƃJ�����̈ʒu��
		* �����ɖڕW���_�ƖڕW�����_�Ɉړ����܂��B�V�[�����؂�ւ���ăJ��������C�ɐ؂�ւ������Ƃ��Ȃǂ�
		* �g�p���Ă��������B
		*/
		void Refresh()
		{
			m_targetMoveSpeed = CVector3::Zero;
			m_positionMoveSpeed = CVector3::Zero;
			m_isRefresh = true;
		}
		/*!
		* @brief	�o�l�J�����̍X�V�����B
		* @details
		*  Update�֐�����Ă΂�Ă��܂��B</br>
		*  �o�l�J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
		*/
		void UpdateSpringCamera();
		/*!
		* @brief	�J�����̍X�V�B
		* @details
		*  Update�֐�����Ă΂�Ă��܂��B</br>
		*  �J�����̍X�V���������ʂŌĂт����Ȃǂ̓���ȃP�[�X�Ŏg�p���Ă��������B</br>
		*/
		void UpdateCamera()
		{
			if (m_camera) {
				m_camera->Update();
			}
		}
	private:
		CCamera*	m_camera = nullptr;				//!<�J�����B
		CVector3	m_target = CVector3::Zero;		//!<�ڕW�ƂȂ钍���_�B
		CVector3	m_position = CVector3::Zero;	//!<�ڕW�ƂȂ鎋�_�B
		CVector3	m_targetMoveSpeed = CVector3::Zero;		//!<�����_�̈ړ����x�B
		CVector3	m_positionMoveSpeed = CVector3::Zero;	//!<���_�̈ړ����x�B
		float		m_maxMoveSpeed = 0.0f;					//!<�ō��ړ����x�B
		float		m_targetDampingRate = 1.0f;				//!<�������B�l���傫���قǃJ�������x��t���Ă���B
		float		m_dampingRate = 1.0f;					//!<�������B
		float		m_dampingRateVel = 0.0f;
		bool		m_isEnableCollisionSolver = false;		//!<�R���W�����������L���H
		bool		m_isRefresh = true;						//!<���t���b�V�����K�v�H
		CCameraCollisionSolver m_cameraCollisionSolver;
	};
}