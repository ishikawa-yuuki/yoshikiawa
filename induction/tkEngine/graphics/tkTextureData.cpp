/*!
 * @brief	�e�N�X�`���f�[�^�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkTextureData.h"


namespace tkEngine{
	/*!
	 *@brief	�e�N�X�`����ǂݍ��݁B
	 */
	bool CTextureData::Load(const LPCWSTR fileName)
	{
		const wchar_t* ext = wcsstr(fileName, L".");
		HRESULT hr = S_OK;
		if (wcscmp(ext, L".dds") == 0){
			//DDS�B
			 hr = DirectX::LoadFromDDSFile(fileName, 0, &m_texMetadata, m_scratchImage);
		}
		else if (wcscmp(ext, L".tga") == 0) {
			//TGA�B
			hr = DirectX::LoadFromTGAFile(fileName, &m_texMetadata, m_scratchImage);
		}
		else {
			//����ȊO�B
			hr = DirectX::LoadFromWICFile(fileName, 0, &m_texMetadata, m_scratchImage);
		}
		
		if (FAILED(hr)) {
			//�ǂݍ��ݎ��s�B
			char mFileName[256];
			wcstombs(mFileName, fileName, sizeof(mFileName)-1);
			static char errorMessage[1024];
			sprintf(errorMessage, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B%s\n", mFileName);
			TK_LOG("errorMessage");
			return false;
		}

		return true;
	}
	/*!
	*@brief	�e�N�X�`����ۑ��B
	*/
	bool CTextureData::Save(const LPCWSTR fileName, size_t mip, size_t item, size_t slice)
	{
		const wchar_t* ext = wcsstr(fileName, L".");
		HRESULT hr = S_OK;
		if (wcscmp(ext, L".dds") == 0) {
			//DDS�B
			hr = DirectX::SaveToDDSFile(*m_scratchImage.GetImage(mip, item, slice), 0, fileName );
		}
		else if (wcscmp(ext, L".tga") == 0) {
			//TGA�B
			hr = DirectX::SaveToTGAFile(*m_scratchImage.GetImage(mip, item, slice), fileName);
		}
		else if(wcscmp(ext, L".png") == 0){
			//png�B
			hr = DirectX::SaveToWICFile(*m_scratchImage.GetImage(mip, item, slice), 0, GUID_ContainerFormatPng, fileName);
		}
		else if (wcscmp(ext, L".jpg") == 0) {
			//jpg�B
			hr = DirectX::SaveToWICFile(*m_scratchImage.GetImage(mip, item, slice), 0, GUID_ContainerFormatJpeg, fileName);
		}
		if (FAILED(hr)) {
			char mFileName[256];
			wcstombs(mFileName, fileName, sizeof(mFileName) - 1);
			static char errorMessage[1024];
			sprintf(errorMessage, "�e�N�X�`���̕ۑ��Ɏ��s���܂����B%s\n", mFileName);
			TK_LOG("errorMessage");
			return false;
		}
		return true;
	}
}