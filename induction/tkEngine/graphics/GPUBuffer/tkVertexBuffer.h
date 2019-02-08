/*!
 * @brief	���_�o�b�t�@
 */

#pragma once

namespace tkEngine{
	/*!
	 * @brief	���_�o�b�t�@�B
	 */
	class CVertexBuffer : Noncopyable{
	public:
		CVertexBuffer();
		~CVertexBuffer();
		/*!
		 * @brief	���_�o�b�t�@�̍쐬�B
		 *@param[in]	numVertex			���_���B
		 *@param[in]	stride				���_�X�g���C�h�B
		 *@param[in]	pSrcVertexBuffer	�\�[�X���_�o�b�t�@�B
		 */
		bool Create( int numVertex, int stride, const void* pSrcVertexBuffer );
		/*!
		*@brief	�J���B
		*@details
		* ���̊֐��̓f�X�g���N�^������R�[������Ă��܂��B
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release();
		/*!
		*@brief	���_�X�g���C�h���擾�B
		*/
		int GetStride() const
		{
			return m_stride;
		}
		/*!
		*@brief ID3D11Buffer*���擾�B
		*/
		ID3D11Buffer*& GetBody() 
		{
			return m_vertexBuffer;
		}
	private:
		ID3D11Buffer*	m_vertexBuffer = nullptr;	//!<���_�o�b�t�@�B
		int				m_stride = 0;				//!<���_�X�g���C�h�B
	};
}