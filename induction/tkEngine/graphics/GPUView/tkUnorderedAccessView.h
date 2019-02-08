/*!
 *@brief	UnorderedAccessView
 */

#pragma once

namespace tkEngine{
	class CStructuredBuffer;
	/*!
	 *@brief	UnorderedAccessView
	 *@details
	 * �R���s���[�g�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�̏o�͂Ɏg�p����r���[�B
	 * �o�̓o�b�t�@�ł͂�����g�p����B
	 */
	class CUnorderedAccessView{
	public:
		CUnorderedAccessView();
		~CUnorderedAccessView();
		/*!
		 *@brief	StructuredBuffer�p��UAV���쐬�B
		 *@param[in]	structuredBuffer	structuredBuffer
		 */
		bool Create(CStructuredBuffer& structuredBuffer);
		/*!
		*@brief	Texture�p��UAV���쐬�B
		*@param[in]	texture		�e�N�X�`���B
		*/
		bool Create(ID3D11Texture2D* texture);
		/*!
		 *@brief	�����I�ȊJ���B
		 *@details
		 * �����I�ɊJ������K�v������Ƃ��Ɏg�p���Ă��������B
		 */
		void Release();
		/*!
		*@brief	ID3D11UnorderedAccessView���擾�B
		*/
		ID3D11UnorderedAccessView*& GetBody()
		{
			return m_uav;
		}
		/*!
		*@brief	�L���ȃf�[�^���ǂ�������B
		*/
		bool IsValid() const
		{
			return m_isValid;
		}
	private:
		ID3D11UnorderedAccessView*	m_uav = nullptr;
		bool						m_isValid = false;	//!<�L���ȃf�[�^�H
	};
}