/*!
 * @brief	�e�N�X�`���f�[�^�B
 */

#pragma once


namespace tkEngine{
	/*!
	 * @brief	�e�N�X�`���f�[�^�B
	 */
	class CTextureData : Noncopyable{
	public:
		CTextureData()
		{
		}
		~CTextureData()
		{
		}
		/*!
		 *@brief	�e�N�X�`����ǂݍ��݁B
		 */
		bool Load(const LPCWSTR fileName);
		/*!
		*@brief	�e�N�X�`����ۑ��B
		*/
		bool Save(const LPCWSTR fileName, size_t mip, size_t item, size_t slice);
		/*!
		*@brief	�r�b�g�}�b�v�C���[�W���擾�B
		*/
		const DirectX::Image* GetImage(size_t mip, size_t item, size_t slice) const
		{
			return m_scratchImage.GetImage(mip, item, slice);
		}
		/*!
		*@brief	�r�b�g�}�b�v�C���[�W���擾�B
		*/
		const DirectX::Image* GetImages() const
		{
			return m_scratchImage.GetImages();
		}
		/*!
		*@brief	�摜�C���[�W�̐����擾�B
		*/
		int GetNumImages() const
		{
			return m_scratchImage.GetImageCount();
		}
		/*!
		*@brief	�摜�̃��^�f�[�^���擾�B
		*/
		const DirectX::TexMetadata& GetMetadata() const
		{
			return m_texMetadata;
		}
	private:
		DirectX::TexMetadata		m_texMetadata;		//!<�e�N�X�`�����^�f�[�^�B
		DirectX::ScratchImage		m_scratchImage;		//!<
	};
}