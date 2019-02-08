/*!
 *@brief	�C���f�b�N�X�o�b�t�@
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�C���f�b�N�X�o�b�t�@�B
	 */
	class CIndexBuffer{
	public:
		/*!
		 *@brief	�C���f�b�N�X�̌^�B
		 */
		enum EnIndexType{
			enIndexType_16,		//!<16�r�b�g�C���f�b�N�X�B
			enIndexType_32,		//!<32�r�b�g�C���f�b�N�X�B
		};
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CIndexBuffer();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CIndexBuffer();
		/*!
		 *@brief	�C���f�b�N�X�o�b�t�@���쐬�B
		 *@param[in]	numIndex			�C���f�b�N�X�̐��B
		 *@param[in]	indexType			�C���f�b�N�X�̌^�B
		 *@param[in]	pSrcIndexBuffer		�\�[�X�C���f�b�N�X�o�b�t�@�B
		 */
		bool Create( int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer );
		/*!
		 *@brief	�J���B
		 *@details
		 * ���̊֐��̓f�X�g���N�^����Ă΂�Ă��܂��B
		 * �����I�ȃ^�C�~���O�ŊJ���������ꍇ�͌Ăяo���Ă��������B
		 */
		void Release();
		
		/*!
		*@brief	�C���f�b�N�X�̌^���擾�B
		*/
		EnIndexType GetIndexType() const
		{
			return m_indexType;
		}
		ID3D11Buffer* GetBody() const
		{
			return m_indexBuffer;
		}
		/*!
		*@brief	�C���f�b�N�X�̐����擾�B
		*/
		unsigned int GetNumIndex() const
		{
			return m_numIndex;
		}
		/*!
		*@brief	�C���f�b�N�X�o�b�t�@���쐬����Ă��邩����B
		*/
		bool IsCreated() const
		{
			return m_isCreated;
		}
	private:
		bool			m_isCreated = false;			//!<�C���f�b�N�X�o�b�t�@���쐬����Ă���H
		ID3D11Buffer*	m_indexBuffer = nullptr;		//!<�C���f�b�N�X�o�b�t�@�B
		EnIndexType		m_indexType = enIndexType_16;	//!<�C���f�b�N�X�̌^�B
		unsigned int	m_numIndex = 0;					//!<�C���f�b�N�X�̐��B
	};
}