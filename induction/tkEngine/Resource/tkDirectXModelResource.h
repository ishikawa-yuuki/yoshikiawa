/*!
 *@brief	DirectX::Model���\�[�X�Ǘ��N���X�B
 */
#pragma once

namespace tkEngine {
	class CDirectXModelResource : Noncopyable{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CDirectXModelResource();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CDirectXModelResource();
		/*!
		 *@brief	DirectX::Model���\�[�X�̃��[�h�B
		 */
		DirectX::Model* Load(const wchar_t* filePath, CSkeleton& skeleton);
		/*!
		*@brief	���\�[�X�����ׂĉ���B
		*/
		void Release()
		{
			m_resourceMap.clear();
		}
	private:
		static bool m_isInstanced;		//���̂���������Ă��邩�ǂ����̃t���O�B
		using DirectXModelPtr = std::unique_ptr<DirectX::Model>;
		std::map<int, DirectXModelPtr> m_resourceMap;
	};
}