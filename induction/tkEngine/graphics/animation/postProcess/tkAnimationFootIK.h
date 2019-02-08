/*!
 *@brief	FootIK
 */

#pragma once

#include "tkEngine/physics/tkCapsuleCollider.h"


namespace tkEngine{
	class CSkeleton;
	class CBone;

	/*!
	 *@brief	FootIK
	 *@details
	 * �����n�ʂɂ߂荞�܂Ȃ��悤�ɂ��邷�鏈���B
	 * CCD-IK�@���g�p���Ă��܂��B
	 */
	class CAnimationFootIK{
	private:
		/*!
		*@brief	���B
		*/
		struct SFoot {
			CBone*			m_bone;			//���̃{�[���B
			CCapsuleCollider m_collider;	//�G���h�G�t�F�N�^�ɐݒ肳��Ă���{�[���B
		};
	public:
		/*!
		*@brief	FootIK�̃p�����[�^�B
		*/
		struct SFootIKParam {
			const wchar_t* footBoneName_0 = nullptr;	//!<���̃{�[���̖��O0�B
			const wchar_t* footBoneName_1 = nullptr;	//!<���̃{�[���̖��O1�B
			const wchar_t* rootBoneName = nullptr;		//!<����IK�̃��[�g�ƂȂ鍜�̖��O�B�X�P���g���̃��[�g�ł͂Ȃ��AIK�̌v�Z���I��点�����{�[���̖��O���w��B���ՂƂ����K�̃{�[���ɂȂ�Ǝv����B
			float footCapsuleColliderHeight_0 = 0.0f;	//!<�J�v�Z���R���C�_�[�̍���0�B
			float footCapsuleColliderHeight_1 = 0.0f;	//!<�J�v�Z���R���C�_�[�̍���1�B
			float footCapsuleColliderRadius_0 = 0.0f;	//!<�J�v�Z���R���C�_�[�̔��a0�B
			float footCapsuleColliderRadius_1 = 0.0f;	//!<�J�v�Z���R���C�_�[�̔��a1�B
		};
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CAnimationFootIK();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CAnimationFootIK();
		/*!
		*@brief	�������B
		*/
		void Init(CSkeleton* skeleton);
		/*!
		 *@brief	�X�V�B
		 */
		void Update();
		/*!
		*@brief	FootIK��L���ɂ���B
		*/
		void Enable(const SFootIKParam& param);
		
		/*!
		*@brief	FootIK�𖳌��ɂ���B
		*/
		void Disable()
		{
			m_isEnable = false;
		}
	private:
		/*!
		 *@brief	CCD-IK�@���g����FootIK�����s�B
		 */
		void SolverCCD_IK(const SFoot& foot, CVector3 targetPosition);
		/*!
		 *@brief	PIK�@���g����FootIK�����s�B
		 */
		void SolverPIK(const SFoot& foot, CVector3 targetPosition);
		bool CalcIKTargetPosition(const SFoot& foot, CVector3& targetPosition);
	private:
		int				m_rootBoneId = -1;	//!<���[�g�̃{�[��ID
		CSkeleton*		m_skeleton;		//!<�X�P���g���B
		SFoot			m_foots[2];		//!<���B
		bool			m_isEnable = false;	//!<FootIK���L���H
		
	};
}