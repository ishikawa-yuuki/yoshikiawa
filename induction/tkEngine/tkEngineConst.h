/*!
 *@brief	tkEngine�萔�w�b�_�B
 */

#pragma once

namespace tkEngine{
	static const int MRT_MAX = 8;		//!<MRT�̍ő吔�B
	static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B
	/*!
	 *@brief	�\�t�g�V���h�E�̕i�����x���B
	 */
	enum class EnSoftShadowQualityLevel {
		enNone,		//!<�\�t�g�V���h�E�Ȃ��B
		eSSSS,		//!<SSSS(ScreenSpaceSoftShadow)
		eSSSS_PCF,	//!<SSSS+PCF
	};
}