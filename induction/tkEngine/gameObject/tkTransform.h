/*!
 *@brief	Transform
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	Transform
	 *@details
	 * Unity��Transform�Ɠ��l�̎g�������ł���B
	 */
	class CTransform{
	public:
		CTransform()
		{
		}
		~CTransform()
		{
		}
		/*!
		 *@brief	���[���h���W���擾�B
		 */
		const CVector3& GetPosition() const
		{
			return m_position;
		}
		/*!
		 *@brief	���[���h��]���擾�B
		 */
		const CQuaternion& GetRotation() const
		{
			return m_rotation;
		}
		/*!
		 *@brief	���[���h�g�嗦���擾�B
		 */
		const CVector3& GetScale() const
		{
			return m_scale;
		}
		/*!
		 *@brief	���[�J�����W���擾�B
		 */
		const CVector3& GetLocalPosition() const
		{
			return m_localPosition;
		}
		/*!
		 *@brief	���[�J����]���擾�B
		 */
		const CQuaternion& GetLocalRotation() const
		{
			return m_localRotation;
		}
		/*!
		 *@brief	���[�J���g����擾�B
		 */
		const CVector3& GetLocalScale() const
		{
			return m_localScale;
		}
		/*!
		 *@brief	���[�J�����W��ݒ�B
		 */
		void SetLocalPosition(const CVector3& pos)
		{
			m_localPosition = pos;
		}
		/*!
		 *@brief	���[�J����]��ݒ�B
		 */
		void SetLocalRotation(const CQuaternion& rot)
		{
			m_localRotation = rot;
		}
		/*!
		 *@brief	���[�J���g�嗦��ݒ�B
		 */
		void SetLocalScale(const CVector3& scale)
		{
			m_localScale = scale;
		}
		/*!
		 *@brief	���̃C���X�^���X�Ǝq�����ׂẴ��[���h�s����X�V����B
		 */
		void UpdateWorldMatrixAll();
	private:
		CTransform* m_parent = nullptr;							//!<�e�B
		std::list<CTransform*> m_children;						//!<�q���B
		CVector3	m_position = CVector3::Zero;				//!<���[���h���W�B
		CQuaternion m_rotation = CQuaternion::Identity;			//!<���[���h��]�B
		CVector3	m_scale = CVector3::Zero;					//!<���[���h�g�嗦�B
		CVector3	m_localPosition = CVector3::Zero;			//!<���[�J�����W�B
		CQuaternion	m_localRotation = CQuaternion::Identity;	//!<���[�J����]�B
		CVector3	m_localScale = CVector3::One;				//!<���[�J���X�P�[���B
		CMatrix		m_worldMatrix;								//!<���[���h�s��B
	};
}