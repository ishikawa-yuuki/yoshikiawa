/*!
 * @brief	���I�����I�u�W�F�N�g�B
 */

#pragma once

#include "tkEngine/physics/tkMeshCollider.h"
#include "tkEngine/physics/tkRigidBody.h"
#include "tkEngine/physics/tkPhysicsObjectBase.h"

namespace tkEngine{
	/*!
	 * @brief	���I�����I�u�W�F�N�g
	 *@details
	 * CPhysicsObjectBase��public�p�u���b�N�����o�֐���
	 * �����̂��߂Ɏg���Ă���A�O���Ɍ��J�������Ȃ���������
	 * private�p�����s���Ă���B
	 */
	class CPhysicsDynamicObject : private CPhysicsObjectBase{
	public:
		/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃI�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release() override final;
	private:
		/*!
		* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		*/
		void CreateCommon(CVector3 pos, CQuaternion rot) override final;
	public:
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		~CPhysicsDynamicObject()
		{
			Release();
		}
		/*!
		* @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	size		�T�C�Y�B
		*@param[in] mass		���ʁB
		*/
		void CreateBox(CVector3 pos, CQuaternion rot, CVector3 size, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateBox(pos, rot, size);
		}
		/*!
		* @brief	�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	radius		�J�v�Z���̔��a�B
		*@param[in]	height		�J�v�Z���̍����B
		*@param[in]	mass		���ʁB
		*/
		void CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateCapsule(pos, rot, radius, height);
		}
		/*!
		* @brief	���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	radius		���̂̔��a�B
		*@param[in]	mass		���ʁB
		*/
		void CreateSphere(CVector3 pos, CQuaternion rot, float radius, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateSphere(pos, rot, radius);
		}
		/*!
		* @brief	���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos					���W�B
		*@param[in]	rot					��]�B
		*@param[in]	skinModelData		�X�L�����f���f�[�^�B
		*@param[in] mass				���ʁB
		*/
		void CreateMesh(CVector3 pos, CQuaternion rot, const CSkinModelData& skinModelData, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateMesh(pos, rot, skinModelData);
		}
		void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const CSkinModel& skinModel, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateMesh(pos, rot, scale, skinModel);
		}
		void CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, prefab::CSkinModelRender* skinModelRender, float mass, CVector3 localInteria)
		{
			m_mass = mass;
			m_localInterial = localInteria;
			CPhysicsObjectBase::CreateMesh(pos, rot, scale, skinModelRender);
		}
		/*!
		* @brief	�����I�u�W�F�N�g�̍��W�Ɖ�]���擾
		*@param[out]	pos			���W�B
		*@param[out]	rot			��]�B
		*/
		void GetPositionAndRotation(CVector3& pos, CQuaternion& rot) const
		{
			m_rigidBody.GetPositionAndRotation(pos, rot);
		}
		/*!
		* @brief	�͂�������B
		*@param[out]	force		�́B
		*@param[out]	relPos		�͂���������W�B
		*/
		void AddForce(const CVector3& force, const CVector3& relPos = CVector3::Zero)
		{
			m_rigidBody.AddForce(force, relPos);
		}
		CRigidBody& GetRigidBody()
		{
			return m_rigidBody;
		}
	private:
		CVector3 m_localInterial = CVector3::Zero;	//!<�����e���\�B��
		float m_mass = 1.0f;				//!<���ʁB
		CRigidBody m_rigidBody;				//!<���́B
	};
}