/*!
 * @brief	StructuredBuffer
 */

#pragma once

#include "tkEngine/graphics/GPUView/tkShaderResourceView.h"
#include "tkEngine/graphics/GPUView/tkUnorderedAccessView.h"
namespace tkEngine{
	/*!
	 * @brief	StructuredBuffer
	 */
	class CStructuredBuffer : Noncopyable{
	public:
		CStructuredBuffer();
		~CStructuredBuffer();
		/*!
		* @brief	StructuredBuffer���쐬�B
		*@param[in]	pInitData		�����f�[�^�B
		*@param[in]	bufferDesc		�o�b�t�@��`�B
		*/
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/*!
		 * @brief	ID3D11Buffer*���擾�B
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_structuredBuffer;
		}
		/*!
		*@brief	�J���B
		*@details
		* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
		/*!
		* @brief	SRV���擾�B
		*/
		CShaderResourceView& GetSRV()
		{
			return m_srv;
		}
		/*!
		* @brief	UAV���擾�B
		*/
		CUnorderedAccessView& GetUAV()
		{
			return m_uav;
		}
	private:
		ID3D11Buffer*			m_structuredBuffer = nullptr;	//!<StructuredBuffer
		CShaderResourceView		m_srv;							//!<SRV
		CUnorderedAccessView	m_uav;							//!<UAV
	};
}