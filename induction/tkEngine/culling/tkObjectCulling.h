/*!
 *@brief	�I�u�W�F�N�g�̃J�����O�����̃C���^�[�t�F�[�X�N���X�B
 */

#pragma once

#include "tkEngine/math/tkAabb.h"

namespace tkEngine{
	/*!
	 *@brief	CPU�ł̑����J�����O�����̃C���^�[�t�F�[�X�N���X�B
	 *@details
	 * Strategy�p�^�[�����g�p���Đ݌v����Ă��܂��B
	 */
	class IObjectCulling{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		IObjectCulling() {}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		virtual ~IObjectCulling() {}
		/*!
		 *@brief	�J�����O�A���S���Y�������s�B
		 */
		virtual void Execute(const CBox& aabb) = 0;
		/*!
		 *@brief	�J�����O����Ă��邩����B
		 */
		bool IsCulling() const
		{
			return m_isCulling;
		}
	protected:
		/*!
		 *@brief	�J�����O�t���O��ݒ�B
		 */
		void SetCullingFlag( bool flag )
		{
			m_isCulling = flag;
		}
	private:
		bool	m_isCulling = false;
	};
}