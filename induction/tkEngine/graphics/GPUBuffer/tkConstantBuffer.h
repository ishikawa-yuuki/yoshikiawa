/*!
 * @brief	�萔�o�b�t�@
 */

#pragma once

#include "tkEngine/graphics/GPUBuffer/tkGPUBuffer.h"

namespace tkEngine{
	/*!
	 * @brief	�萔�o�b�t�@�B
	 */
	class CConstantBuffer : public CGPUBuffer{
	public:
		CConstantBuffer();
		~CConstantBuffer();
		/*!
		*@brief ConstantBuffer���쐬�B
		*@param[in]	pInitData		�����f�[�^�B
		*@param[in]	bufferSize		�o�b�t�@�T�C�Y�B
		*/
		bool Create(const void* pInitData, int bufferSize );		
	};
}