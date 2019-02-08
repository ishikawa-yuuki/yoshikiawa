/*!
 * @brief	�T���v���X�e�[�g�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	�T���v���X�e�[�g�B
	 */
	class CSamplerState : Noncopyable{
	public:
		CSamplerState()
		{
		}
		~CSamplerState()
		{
			Release();
		}
		/*!
		 * @brief	�T���v���X�e�[�g���쐬�B
		 */
		bool Create(const D3D11_SAMPLER_DESC& desc);
		/*!
		 * @brief	�����I�ȊJ�������B
		 */
		void Release()
		{
			if(m_samplerState != nullptr){
				m_samplerState->Release();
				m_samplerState = nullptr;
			}
		}
		/*!
		 * @brief	�T���v���X�e�[�g���擾�B
		 */
		ID3D11SamplerState*& GetBody() 
		{
			return m_samplerState;
		}
	private:
		ID3D11SamplerState*		m_samplerState = nullptr;
	};
}