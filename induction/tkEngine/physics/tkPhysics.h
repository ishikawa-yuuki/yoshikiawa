#pragma once

#include "tkEngine/Physics/tkCollisionAttr.h"
#include "tkEngine/Physics/tkPhysicsDebugDraw.h"
#include "tkEngine/Physics/tkRigidBody.h"

namespace tkEngine{
	class CCharacterController;

	class CPhysicsWorld
	{
		std::unique_ptr<btDefaultCollisionConfiguration> 	 m_collisionConfig;
		std::unique_ptr<btCollisionDispatcher>				 m_collisionDispatcher;	//!<�Փˉ��������B
		std::unique_ptr<btBroadphaseInterface>				 m_overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		std::unique_ptr<btSequentialImpulseConstraintSolver> m_constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
		std::unique_ptr<btDiscreteDynamicsWorld>			 m_dynamicWorld;			//!<���[���h�B
#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
		CPhysicsDebugDraw									 m_debugDraw;
#endif
	public:
		~CPhysicsWorld();
		void Init();
		void Update();
		void DebubDrawWorld(CRenderContext& rc);
		void Release();
		/*!
		* @brief	�d�͂�ݒ�B�B
		*/
		void SetGravity(CVector3 g)
		{
			m_dynamicWorld->setGravity(btVector3(g.x, g.y, g.z));
		}
		/*!
		* @brief	�_�C�i�~�b�N���[���h���擾�B
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return m_dynamicWorld.get();
		}
		/*!
		* @brief	���̂�o�^�B
		*/
		void AddRigidBody(CRigidBody& rb)
		{
			if (rb.IsAddPhysicsWorld() == false) {
				m_dynamicWorld->addRigidBody(rb.GetBody());
				rb.SetMarkAddPhysicsWorld();
			}
		}
		/*!
		* @brief	�f�o�b�O�\���̃��[�h��ݒ肷��B
		*@param[in]	debugMode		enum btIDebugDraw::DebugDrawModes���Q�Ƃ��Ă��������B
		*/
		void SetDebugDrawMode(int debugMode)
		{
#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
			//���C���[�t���[���`��̂݁B
			m_debugDraw.setDebugMode(debugMode);
#endif
		}
		/*!
		* @brief	���̂�j���B
		*/
		void RemoveRigidBody(CRigidBody& rb)
		{
			if (rb.IsAddPhysicsWorld() == true) {
				m_dynamicWorld->removeRigidBody(rb.GetBody());
				rb.SetUnmarkAddPhysicsWorld();
			}
		}
		/*!
		* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		void AddCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->addCollisionObject(&colliObj);
		}
		/*!
		* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
		void RemoveCollisionObject(btCollisionObject& colliObj)
		{
			m_dynamicWorld->removeCollisionObject(&colliObj);
		}
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			m_dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}
		void ContactTest(
			btCollisionObject* colObj,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		void ContactTest(
			CRigidBody& rb,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		
		void ContactTest(
			CCharacterController& charaCon,
			std::function<void(const btCollisionObject& contactCollisionObject)> cb
		);
		
	};
	
}
