/*!
 * @brief	���C�g�̊��N���X�B
 */

#pragma once

namespace tkEngine{
	namespace prefab {
		/*!
		 * @brief	���C�g�̊��N���X�B
		 */
		class CLightBase : public IGameObject {
		public:
			bool Start() override final;
			void OnDestroy() override final;
			/*!
			*@brief ���C�g�̉e����^����}�e���A��ID�O���[�v��ݒ肷��B
			*/
			void SetLightingMaterialIDGroup(unsigned int group)
			{
				m_lightingMaterialIDGroup = group;
			}
			/*!
			*@brief ���C�g�̉e����^����}�e���A��ID�O���[�v���擾�B
			*/
			unsigned int GetLightingMaterialIDGroup() const
			{
				return m_lightingMaterialIDGroup;
			}
		private:
			virtual bool StartSub() = 0;
			virtual void OnDestorySub() {}
		private:
			unsigned int m_lightingMaterialIDGroup = 0xFFFFFFFF;	//!<���C�g�̉e����^���鑊������ʂ���}�e���A��ID�O���[�v�B0xFFFFFFFF�ł��ׂẴI�u�W�F�N�g�Ƀ��C�g�𓖂Ă�B
		};
	}
}