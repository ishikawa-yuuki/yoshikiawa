/*!
 * @brief	�z�u�f�[�^�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�I�u�W�F�N�g�̔z�u�f�[�^�������N���X�B
	 * @details
	 *	�X�P���g���f�[�^���g���܂��BCSkeleton�N���X�̃C���^�[�t�F�[�X��
	 *	�z�u�f�[�^�Ƃ��Ĉ����₷���悤�ɕϊ�����A�_�v�^�N���X�ł��B
	 */
	class CLocData : Noncopyable{
	public:
		struct SObjectData {
			CVector3 position;
			CQuaternion rotation;
			CVector3 scale;
			const wchar_t* name;
		};
		CLocData()
		{
		}
		~CLocData()
		{
		}
		/*!
		*@brief	�z�u�f�[�^��ǂݍ��݁B
		*/
		bool Load(const wchar_t* filePath)
		{
			if(m_locData.Load(filePath) == false){
				//�ǂݍ��݂Ɏ��s�B
				TK_WARNING_MESSAGE_BOX("�z�u�f�[�^�̓ǂݍ��݂Ɏ��s���܂����B%ls", filePath);
				return false;
			}
			for (int i = 1; i < m_locData.GetNumBones(); i++) {
				SObjectData objData;
				auto bone = m_locData.GetBone(i);

				CVector3 scale;
				bone->CalcWorldTRS(objData.position, objData.rotation, scale);

				//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
				auto t = objData.position.y;
				objData.position.y = objData.position.z;
				objData.position.z = -t;

				t = objData.rotation.y;
				objData.rotation.y = objData.rotation.z;
				objData.rotation.z = -t;

				objData.name = bone->GetName();
				//�g��͖��Ή����Ȃ��B
				objData.scale = scale;
				std::swap(objData.scale.y, objData.scale.z);

				m_objectData.push_back(objData);
			}
			return true;
		}
		/*!
		*@brief	�z�u����Ă���I�u�W�F�N�g�̐����擾�B
		*/
		int GetNumObject() const
		{
			return static_cast<int>(m_objectData.size());
		}
		/*!
		 *@brief	�z�u����Ă���I�u�W�F�N�g�̍��W���擾�B
		 */
		const CVector3& GetObjectPosition(int objNo) const
		{
			return m_objectData.at(objNo).position;
		}
		/*!
		 *@brief	�z�u����Ă���I�u�W�F�N�g�̉�]���擾�B
		 */
		const CQuaternion& GetObjectRotation(int objNo) const
		{
			return m_objectData.at(objNo).rotation;
		}
		/*!
		*@brief	�z�u����Ă���I�u�W�F�N�g�̖��O���擾�B
		*/
		const wchar_t* GetObjectName(int objNo) const
		{
			return m_objectData.at(objNo).name;
		}
		const SObjectData& GetObjectData(int objNo) const
		{
			return m_objectData[objNo];
		}
	private:
		CSkeleton	m_locData;	//!<�X�P���g���f�[�^�B
		std::vector<SObjectData>	m_objectData;
	};
}