/*!
 *@brief	�}�b�v�`�b�v�̃����_���[�B
 */

#pragma once

#include "tkEngine/physics/tkPhysicsStaticObject.h"

namespace tkEngine{
	struct LevelObjectData;
	/*!
	 *@brief	�}�b�v�`�b�v�����_���[�B
	 */
	class CMapChipRender : public IGameObject{
	public:
		CMapChipRender();
		~CMapChipRender();
		/// <summary>
		/// IGameObject�̃C���X�^���X��DeleteGO�����Ƃ��ɌĂяo�����֐��B
		/// </summary>
		void OnDestroy() override;
		/// <summary>
		/// ���t���[���Ăяo�����X�V�����B
		/// </summary>
		void Update() override;
		/// <summary>
		/// �`�悷��I�u�W�F�N�g�̐���ǉ��B
		/// </summary>
		void AddRenderObject( const LevelObjectData& objData )
		{
			m_renderObjDatas.push_back(objData);
		}
		/// <summary>
		/// �S�Ă̕`��I�u�W�F�N�g�̒ǉ����I�������ŌĂяo���K�v�����鏉���������B
		/// </summary>
		void InitAfterAddAllRenderObjects();
		/// <summary>
		/// �X�L�����f�������_���[���擾�B
		/// </summary>
		/// <returns></returns>
		prefab::CSkinModelRender* GetSkinModelRender()
		{
			return m_modelRender;
		}
		/// <summary>
		/// �`��I�u�W�F�N�g�f�[�^�ɃN�G�����s���B
		/// </summary>
		/// <param name="queryFunc">�N�G���֐�</param>
		void QueryRenderObjDatas(std::function<void(const LevelObjectData& objData)> queryFunc) 
		{
			for (const auto& renderObjData : m_renderObjDatas) {
				queryFunc(renderObjData);
			}
		}
	private:
		int m_numRenderObject = 0;
		std::vector<LevelObjectData> m_renderObjDatas;	//�`�悷��I�u�W�F�N�g�̃f�[�^�̔z��B
		prefab::CSkinModelRender* m_modelRender = nullptr;	//!<���f�������_���[�B
	};
}
