/*!
 *@brief	�X�L�����f���֌W�֌W�̃V�F�[�_�[�p�����[�^�B
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�萔�o�b�t�@�̃��W�X�^�ԍ�
	 */
	enum EnSkinModelCBReg{
		enSkinModelCBReg_VSPS,		//!<���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[���ʂ̒萔�o�b�t�@�B
		enSkinModelCBReg_Light,		//!<���C�g�p�̒萔�o�b�t�@�B
		enSkinModelCBReg_Material,	//!<�}�e���A���p�����[�^�B
		enSkinModelCBReg_Shadow,	//!<�e�B
		enSkinModelCBReg_GBuffer,	//!<G-Buffer�B
		
	};
	/*!
	 *@brief	SRV�̃��W�X�^�ԍ��B
	 */
	enum EnSkinModelSRVReg{
		enSkinModelSRVReg_AlbedoTexture = 0,		//!<�A���x�h�e�N�X�`���B
		enSkinModelSRVReg_NormalMap,				//!<�@���}�b�v�B
		enSKinModelSRVReg_Specularmap,				//!<�X�y�L�����}�b�v�B
		enSkinModelSRVReg_ShadowMap_0,				//!<�V���h�E�}�b�v
		enSkinModelSRVReg_ShadowMap_1,				//!<�V���h�E�}�b�v
		enSkinModelSRVReg_ShadowMap_2,				//!<�V���h�E�}�b�v
		enSkinModelSRVReg_SilhouetteTexture,		//!<�V���G�b�g�e�N�X�`���B
		enSkinModelSRVReg_SoftShadowMap,			//!<�\�t�g�V���h�E�}�b�v�B
		enSkinModelSRVReg_DepthMap,					//!<�[�x�}�b�v�B
		enSkinModelSRVReg_Tangent,					//!<�ڃx�N�g���B
		enSkinModelSRVReg_MaterialID,				//!<�}�e���A��ID�B
		enSkinModelSRVReg_EmissionColor,			//!<�G�~�b�V�����J���[�B
		
		enSkinModelSRVReg_DirectionLight = 100,		//!<�f�B���N�V�������C�g�B
		enSkinModelSRVReg_PointLight,				//!<�|�C���g���C�g�̃��X�g�B
		enSkinModelSRVReg_PointLightListInTile,		//!<�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�B
		enSkinModelSRVReg_BoneMatrix,				//!<�{�[���s��B
		enSkinModelSRVReg_InstanceMatrix,			//!<�C���X�^���V���O�p�̍s��B
	};
}