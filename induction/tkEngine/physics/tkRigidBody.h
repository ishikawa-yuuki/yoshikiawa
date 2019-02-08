#pragma once

namespace tkEngine{

	class ICollider;

	//���̏��B
	struct RigidBodyInfo {
		RigidBodyInfo() :
			collider(NULL),
			mass(0.0f)
		{
			pos = CVector3::Zero;
			rot = CQuaternion::Identity;
			localInteria = CVector3::Zero;
		}
		CVector3 pos;				//���W�B
		CQuaternion rot;			//��]�B
		CVector3 localInteria;		//�����e���\���B
		ICollider* collider;		//�R���C�_�[�B
		float mass;					//���ʁB

	};
	//���̃N���X�B
	class CRigidBody
	{
		std::unique_ptr<btRigidBody>			m_rigidBody;		//���́B
		std::unique_ptr<btDefaultMotionState>	m_myMotionState;	//���[�V�����X�e�[�g�B
		bool m_isAddPhysicsWorld = false;			//�������[���h�ɒǉ�����Ă���H
	public:
		~CRigidBody();
		void Release();
		void Create(RigidBodyInfo& rbInfo);
		btRigidBody* GetBody()
		{
			return m_rigidBody.get();
		}
		//�������[���h�ɓo�^���̈������B
		void SetMarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = true;
		}
		//�������[���h�ɓo�^���̈���O���B
		void SetUnmarkAddPhysicsWorld()
		{
			m_isAddPhysicsWorld = false;
		}
		//�������[���h�ɒǉ�����Ă���H
		bool IsAddPhysicsWorld() const
		{
			return m_isAddPhysicsWorld;
		}
		/*!
		* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]���擾
		*@param[out]	pos			���W�B
		*@param[out]	rot			��]�B
		*/
		void GetPositionAndRotation(CVector3& pos, CQuaternion& rot) const
		{
			btTransform trans;
			m_myMotionState->getWorldTransform(trans);
			pos.Set(trans.getOrigin());
			rot.Set(trans.getRotation());
		}
		/*!
		* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]��ݒ�
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*/
		void SetPositionAndRotation(const CVector3& pos, const CQuaternion& rot)
		{
			btTransform trans;
			btVector3 btPos;
			pos.CopyTo(btPos);
			trans.setOrigin(btPos);
			btQuaternion btRot;
			rot.CopyTo(btRot);
			trans.setRotation(btRot);
			m_rigidBody->setWorldTransform(trans);
		}
		/*!
		* @brief	�͂�������B
		*@param[out]	force		�́B
		*@param[out]	relPos		�͂���������W�B
		*/
		void AddForce(const CVector3& force, const CVector3& relPos)
		{
			btVector3 btForce;
			btVector3 btRelPos;
			force.CopyTo(btForce);
			relPos.CopyTo(btRelPos);
			m_rigidBody->applyForce(btForce, btRelPos);
		}
	};
}
