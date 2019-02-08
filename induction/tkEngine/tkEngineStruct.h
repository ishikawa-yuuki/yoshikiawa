/*!
 *@brief	tkEngine�p�̊e��\���́B
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�G���W���������p�̃p�����[�^�B
	 */
	struct SInitParam{
		SInitParam(){
			gameObjectPrioMax = 32;
		}
		HINSTANCE hInstance = nullptr;		//!<�A�v���P�[�V�����C���X�^���X�B
		int	screenWidth = 0;				//!<�X�N���[���̕��B
		int	screenHeight = 0;				//!<�X�N���[���̍����B
		int frameBufferHeight = 0;			//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
		int frameBufferWidth = 0;			//!<�t���[���o�b�t�@�̍����B���ꂪ�����𑜓x�B
		int nCmdShow = 0;						//!<
		std::uint8_t gameObjectPrioMax = 32;
		SGraphicsConfig graphicsConfing;	//!<�`��R���t�B�O�B
	};
}