/*!
 * @brief	GPU�o�b�t�@�N���X�B
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	GPUBuffer
	 */
	class CGPUBuffer : Noncopyable{
	public:
		CGPUBuffer();
		virtual ~CGPUBuffer();
		/*!
		* @brief	GPUBuffer���쐬�B
		*@param[in]	pInitData		�����f�[�^�B
		*@param[in]	bufferDesc		�o�b�t�@��`�B
		*/
		bool Create(const void* pInitData, D3D11_BUFFER_DESC& bufferDesc);
		/*!
		 * @brief	ID3D11Buffer*���擾�B
		 */
		ID3D11Buffer*& GetBody() 
		{
			return m_gpuBuffer;
		}
		/*!
		*@brief	�J���B
		*@details
		* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
	private:
		ID3D11Buffer*		m_gpuBuffer = nullptr;	//!<GPUBuffer
	};
}