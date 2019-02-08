/*!
 * @brief	�G�t�F�N�g
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	�G�t�F�N�g�B
		 */
		class CEffect : public IGameObject{
		public:
			CEffect();
			~CEffect();
			/*!
			 *@brief	����B
			 */
			void Release();
			/*!
			 *@brief	�G�t�F�N�g���Đ��B
			 *@param[in]	filePath		�Đ�����G�t�F�N�g�̃t�@�C���p�X�B
			 */
			void Play(const wchar_t* filePath);
			/*!
			 *@brief	���W��ݒ�B
			 */
			void SetPosition(const CVector3& pos)
			{
				m_position = pos;
			}
			/*!
			 *@brief	��]�̐ݒ�B
			 */
			void SetRotation(const CQuaternion& rot)
			{
				m_rotation = rot;
			}
			/*!
			 *@brief	�g�嗦��ݒ�B
			 */
			void SetScale(const CVector3& scale)
			{
				m_scale = scale;
			}
			/*!
			 *@brief	�G�t�F�N�g���Đ���������B
			 */
			bool IsPlay() const
			{
				return GraphicsEngine().GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
			}
			/*!
			 *@brief	�X�V�B
			 */
			void Update() override;
		private:
			Effekseer::Effect*	m_effect = nullptr;
			Effekseer::Handle	m_handle = -1;
			CVector3 m_position = CVector3::Zero;			//!<���W�B
			CQuaternion m_rotation = CQuaternion::Identity;	//!<��]�B
			CVector3 m_scale = CVector3::One;				//!<�g�嗦�B
		};
	}
}