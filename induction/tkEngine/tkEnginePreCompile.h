#pragma once

#pragma warning (disable  : 4201)
#pragma warning (disable  : 4127)
#pragma warning (disable :  4100)

#define BUILD_LEVEL_DEBUG		0		//�f�o�b�O�r���h
#define BUILD_LEVEL_PREVIEW		1		//�v���r���[�r���h
#define BUILD_LEVEL_MASTER		2		//�}�X�^�[�r���h�B

/*!
* @brief	�r���h���x���B
* @details
*  BUILD_LEVEL��BUILD_LEVEL_DEBUG�ABUILD_LEVEL_PREVIEW�ABUILD_LEVEL_MASTER</br>
*	�̂R�̒l���Ƃ�܂��B���̂R�̒l�͉��L�̈Ӗ��������܂��B
*		BUILD_LEVEL_DEBUG		���S�ȃf�o�b�O�r���h�B
*		BUILD_LEVEL_PREVIEW		�R�[�h�͍œK������Ă��邪�A�f�o�b�O�@�\�͎c���Ă���B
*		BUILD_LEVEL_MASTER		�}�X�^�[�r���h�B�f�o�b�O�@�\�͊��S�ɍ폜����Ă���B
* �f�o�b�O�R�[�h�𖄂ߍ��ގ��́ABUILD_LEVEL_MASTER�ł͖����ɂȂ�悤�Ɏ������Ă��������B
*/
#ifdef _DEBUG
#define BUILD_LEVEL		BUILD_LEVEL_DEBUG
#elif defined(TK_MASTER)
#define BUILD_LEVEL		BUILD_LEVEL_MASTER
#else
#define BUILD_LEVEL		BUILD_LEVEL_PREVIEW
#endif

/*!
 *@brief	�V�X�e���P��
 */
#define TK_SYSTEM_UNIT_CM		0		//��{�P��cm
#define TK_SYSTEM_UNIT_M		1		//��{�P��m

#define TK_SYSTEM_UNIT			TK_SYSTEM_UNIT_CM

namespace tkEngine {

	static constexpr inline float UnitCM(float param)
	{
#if TK_SYSTEM_UNIT==TK_SYSTEM_UNIT_CM
		//��{�P�ʂ�cm�Ȃ炻�̂܂ܕԂ��B
		return param;
#elif TK_SYSTEM_UNIT==TK_SYSTEM_UNIT_M
		//���[�g���P�ʂɖ߂��B
		return param * 0.01f;
#else
		TK_ASSERT(0, "�P�ʐݒ肪�s���ł��B");
		return 0.0f;
#endif
	}

	static constexpr inline float UnitM(float param)
	{
#if TK_SYSTEM_UNIT==TK_SYSTEM_UNIT_CM
		//��{�P�ʂ�cm�Ȃ̂�*100
		return param * 100.0f;
#elif TK_SYSTEM_UNIT==TK_SYSTEM_UNIT_M
		//���[�g���P�ʂȂ̂ł��̂܂܁B
		return param;
#else
		TK_ASSERT(0, "�P�ʐݒ肪�s���ł��B");
		return 0.0f;
#endif
	}

	static constexpr int NUM_SHADOW_MAP = 3;	//�V���h�E�}�b�v�̖����B
}
#include <windows.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <Xinput.h>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "Effekseer.h"
#include "EffekseerRendererDX11.h"

#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "tkEngine/tkEngineConst.h"
#include "tkEngine/policy/tkNoncopyable.h"
#include "tkEngine/policy/tkScopedResource.h"
#include "tkEngine/debug/tkLog.h"
#include "tkEngine/debug/tkAssert.h"
#include "tkEngine/math/tkMath.h"
#include "tkEngine/math/tkVector.h"
#include "tkEngine/math/tkMatrix.h"
#include "graphics/tkRenderContext.h"

#include "gameObject/tkGameObjectManager.h"

#include "tkEngine\graphics\tkShader.h"
#include "tkEngine/graphics/GPUBuffer/tkVertexBuffer.h"
#include "tkEngine/graphics/GPUBuffer/tkStructuredBuffer.h"
#include "tkEngine/graphics/GPUView/tkShaderResourceView.h"
#include "tkEngine/graphics/GPUView/tkUnorderedAccessView.h"
#include "tkEngine/graphics/tkMapper.h"
#include "tkEngine/graphics/GPUBuffer/tkConstantBuffer.h"
#include "tkEngine/graphics/tkSamplerState.h"
#include "tkEngine/graphics/tkSkinModelData.h"
#include "tkEngine/graphics/tkSkinModel.h"
#include "tkEngine/util/tkNameKey.h"
#include "tkEngine/timer/tkGameTime.h"
#include "tkEngine/Input/tkPad.h"
#include "tkEngine/tkEngine.h"
#include "tkEngine/sound/tkSoundSource.h"
#include "tkEngine/graphics/animation/tkAnimation.h"

#include "tkEngine/graphics/2D/tkSprite.h"
#include "tkEngine/graphics/tkGraphicsEngine_inline.h"
#include "tkEngine/util/tkLocData.h"
#include "tkEngine/graphics/tkSkinModelRender.h"
#include "tkEngine/graphics/2D/tkSpriteRender.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/level/tkLevel.h"
#include "tkEngine/level/tkMapChip.h"
#include "tkEngine/debug/math/tkVectorRenderInline.h"
#include "tkEngine/Character/tkCharacterController.h"
#include "tkEngine/physics/tkPhysicsDynamicObject.h"
#include "tkEngine/graphics/font/tkFontRender.h"
#include "tkEngine/nature/tkSky.h"
#include "tkEngine/graphics/tkChangeRenderTarget.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"