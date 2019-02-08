/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
#include "tkEngine/physics/tkPhysicsObjectBase.h"


namespace tkEngine{
	/*!
	 * @brief	�ÓI�����I�u�W�F�N�g
	 */
	class CPhysicsStaticObject : public CPhysicsObjectBase{
	public:
		~CPhysicsStaticObject()
		{
			Release();
		}
		/*!
		* @brief	����B
		*/
		void Release() override final;
		/*!
		* @brief	���W�Ɖ�]��ݒ�B
		*/
		void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
		{
			m_rigidBody.SetPositionAndRotation(pos, rot);
		}
		CRigidBody& GetRigidBody()
		{
			return m_rigidBody;
		}
	private:
		
		/*!
		* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		*/
		void CreateCommon(CVector3 pos, CQuaternion rot) override final;
	private:
		CRigidBody m_rigidBody;				//!<���́B
	};
}