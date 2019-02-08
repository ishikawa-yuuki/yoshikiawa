/*!
 *@brief	�O�l�̎��_�̃Q�[���J�����̃R���W�����\���o�[
 */

#pragma once

#include "tkEngine/Physics/tkSphereCollider.h"

namespace tkEngine{
	/*!
	 *@brief	�J�����̃R���W�����\���o�[�B
	 *@details
	 * ��ʓI�ȎO�l�̎��_�̃Q�[���J�����̏Փˉ�����񋟂��܂��B\n
	 * �J������w�i�ɂ߂荞�܂������Ȃ��ꍇ�ȂǂɎg�p���Ă��������B
	 *@code
		//�T�^�I�Ȏg�p��B
		int main()
		{
				�E
				�E
				�ȗ�
				�Q�[���̏������Ȃǂ��s���B�B
				�E
				�E
			CCameraCollisionSolver cameraCollisionSolver;
			//�J�����̃R���W�����\���o�[������������B
			cameraCollisionSolver.Init( 50.0f );
			while(true){	//�Q�[�����[�v
				�E
				�E
				�ȗ�
				���̃t���[���̃J�����̎��_�⒍�ӓ_���v�Z�����肷��B
				�E
				�E
				CVector3 newCameraPosition;	//�V�����J�����̎��_�̊i�[��B
				cameraCollisionSolver.Execute( 
					newCameraPosition,		//�������͏Փˉ�����̎��_�̍��W�̊i�[��B
					cameraPosition,			//�������͏Փˉ����O�̎��_�̍��W�B
					cameraTarget,			//��O�����͒����_�̍��W�B
				//�Փˉ����������W���J�����̍��W�Ƃ��Đݒ肷��B
				MainCamera().SetPosition(newCameraPosition);
			}

			return 0;
		}
	 *@endcode
	 */
	class CCameraCollisionSolver{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CCameraCollisionSolver();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CCameraCollisionSolver();
		/*!
		 *@brief	�������B
		 *@param[in]	radius		�J�����̃o�E���f�B���O�X�t�B�A�̔��a�B
		 */
		void Init(float radius);
		/*!
		 *@brief	�R���W���������̎��s�B
		 *@param[out]	result		�R���W�����������s�����_�̍��W���i�[�����B
		 *@param[in]	position	�R���W�����������s���O�̎��_�̍��W�B
		 *@param[in]	target		�J�����̒����_�B
		 *@return	�R���W�����������s�����ꍇ��true���Ԃ��Ă���B
		 */
		bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
	private:
		CSphereCollider		m_collider;			 //�R���C�_�[�B
		float				m_radius = 0.0f;	//���a�B
		bool				m_isInited = false;	//�������ς݂̃t���O�Btrue�ɂȂ��Ă����珉�����ς݁B
	};
}