/*!
* @brief	�ǂ��g���T���v���X�e�[�g���܂Ƃ߂����́B
*/
#pragma once

namespace tkEngine {
	class CPresetSamplerState
	{
	public:
		static void Init();
		static CSamplerState* clamp_clamp_clamp_linear;	//�f�t�H���g�̃T���v���X�e�[�g
																//AddressU = CLAMP
																//AddressV = CLAMP
																//AddressW = CLAMP
		static CSamplerState* clamp_clamp_clamp_point;														//Filter = LINEAR
	};
}
