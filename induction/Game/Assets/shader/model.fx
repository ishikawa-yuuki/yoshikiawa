/*!
 * @brief	���f���V�F�[�_�[�B
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"
#include "modelPSFunction.h"


/*!
 *@brief	�e��������m�����v�Z����B
 */
float CalcShadowPercentPCF4x4(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float2 offsetTbl[] = {
		float2(	 -1.5f * offset.x, -1.5f * offset.y),
		float2(	 -0.5f * offset.x, -1.5f * offset.y),
		float2(   0.5f * offset.x, -1.5f * offset.y),
		float2(	  1.5f * offset.x, -1.5f * offset.y),

		float2(	 -1.5f * offset.x, -0.5f * offset.y),
		float2(	 -0.5f * offset.x, -0.5f * offset.y),
		float2(	  0.5f * offset.x, -0.5f * offset.y),
		float2(	  1.5f * offset.x, -0.5f * offset.y),

		float2(	-1.5f * offset.x, 0.5f * offset.y),
		float2(	-0.5f * offset.x, 0.5f * offset.y),
		float2(	 0.5f * offset.x, 0.5f * offset.y),
		float2(	 1.5f * offset.x, 0.5f * offset.y),

		float2(	-1.5f * offset.x, 1.5f * offset.y),
		float2(	-0.5f * offset.x, 1.5f * offset.y),
		float2(	 0.5f * offset.x, 1.5f * offset.y),
		float2(	 1.5f * offset.x, 1.5f * offset.y),
		
	};
	float weightTbl[] = {
		1,2,2,1,
		2,3,3,2,
		2,3,3,2,
		1,2,2,1,
	};
	float percent = 0.0f;
	float shadow_val=0.0f;
	float totalWeight = 0.0f;
	for (int i = 0; i < 16; i++) {
		shadow_val = tex.Sample(Sampler, uv + offsetTbl[i]).r;
		totalWeight += weightTbl[i];
		if (depth > shadow_val.r + dOffset) {
			//�e�������Ă���B
			percent += 1.0f * weightTbl[i];
		}
	}
	percent /= totalWeight;
	return percent;
}
/*!
*@brief	�e��������m�����v�Z����B
*/
float CalcShadowPercentPCF2x2(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float2 offsetTbl[] = {
		float2(-0.5f * offset.x, -0.5f * offset.y),
		float2(0.5f * offset.x, -0.5f * offset.y),
		float2(-0.5f * offset.x, 0.5f * offset.y),
		float2(0.5f * offset.x, 0.5f * offset.y),

	};

	float percent = 0.0f;
	float shadow_val = 0.0f;
	for (int i = 0; i < 4; i++) {
		shadow_val = tex.Sample(Sampler, uv + offsetTbl[i]).r;
		if (depth > shadow_val.r + dOffset) {
			//�e�������Ă���B
			percent += 1.0f;
		}
	}
	percent /= 4.0f;
	return percent;
}
float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float shadow_val = tex.Sample(Sampler, uv).r;
	if (depth > shadow_val.r + dOffset) {
		return 1.0f;
	}
	return 0.0f;
}
/*!
 *@brief	�\�t�g�e���v�Z�B
 *@return �e��������m�����Ԃ�܂��B0.0�Ȃ�e�������Ȃ��B1.0�Ȃ�e��������B
 */
float CalcSoftShadow( float3 worldPos )
{
	float shadow = 0.0f;
	//������ƓK���B
	if(isShadowReceiver){
		//�e�𗎂Ƃ��B
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv���W�ɕϊ��B
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float shadow_val = 1.0f;
			if(shadowMapUV.x < 0.95f && shadowMapUV.y < 0.95f && shadowMapUV.x > 0.05f && shadowMapUV.y > 0.05f){
				if(i == 0){					
					shadow = CalcShadowPercentPCF4x4(shadowMap_0, shadowMapUV, texOffset[i], depth, depthOffset.x);
				}else if(i == 1){
					shadow = CalcShadowPercentPCF2x2(shadowMap_1, shadowMapUV, texOffset[i], depth, depthOffset.y);
				}else if(i == 2){
					shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[i], depth, depthOffset.z);
				}
				break;
			}
		}
	}
	return shadow;
}
/*!
 *@brief	�\�t�g�e���v�Z�B
 *@return �e��������m�����Ԃ�܂��B0.0�Ȃ�e�������Ȃ��B1.0�Ȃ�e��������B
 */
float CalcShadow( float3 worldPos )
{
	float shadow = 0.0f;
	//������ƓK���B
	if(isShadowReceiver){
		//�e�𗎂Ƃ��B
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv���W�ɕϊ��B
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float shadow_val = 1.0f;
			if(shadowMapUV.x < 0.95f && shadowMapUV.y < 0.95f && shadowMapUV.x > 0.05f && shadowMapUV.y > 0.05f){
				if(i == 0){
					shadow = CalcShadowPercent(shadowMap_0, shadowMapUV, texOffset[i], depth, depthOffset.x);
				}else if(i == 1){
					shadow = CalcShadowPercent(shadowMap_1, shadowMapUV, texOffset[i], depth, depthOffset.y);
				}else if(i == 2){
					shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[i], depth, depthOffset.z);
				}
				break;
			}
		}
	}
	return shadow;
}
/*!
 *@brief	�@�����v�Z�B
 */
float3 CalcNormal( float3 normal, float3 biNormal, float3 tangent, float2 uv )
{
	if(hasNormalMap){
		//�@���}�b�v������B
		float3 binSpaceNormal = normalMap.Sample(Sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z; 
	}
	return normal;
}
/*!
 *@brief	�X�L���s����v�Z�B
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�̃R�A�v���O�����B
-------------------------------------------------------------------------------------- */
PSInput VSMainCore( VSInputNmTxVcTangent In, float4x4 worldMat )
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(worldMat, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(worldMat, In.Normal));
	psInput.Tangent = normalize(mul(worldMat, In.Tangent));
    return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	return VSMainCore(In, mWorld);
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[(�C���X�^���V���O�`��p)�B
-------------------------------------------------------------------------------------- */
PSInput VSMainInstancing( VSInputNmTxVcTangent In, uint instanceID : SV_InstanceID )
{
	return VSMainCore(In, instanceMatrix[instanceID]);
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	//�X�L���s����v�Z�B
	float4x4 skinning = CalcSkinMatrix(In);
	//���[���h���W�A�@���A�ڃx�N�g�����v�Z�B
	float4 pos = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}


/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L���Ȃ����f���p
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
PSInput_RenderToDepth VSMain_RenderDepth(VSInputNmTxVcTangent In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L���Ȃ��C���X�^���V���O���f���p
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */

PSInput_RenderToDepth VSMainInstancing_RenderDepth(
	VSInputNmTxVcTangent In, 
	uint instanceID : SV_InstanceID
)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(instanceMatrix[instanceID], In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p����钸�_�V�F�[�_�[�B
 *			�X�L�����胂�f���p�B
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
PSInput_RenderToDepth VSMainSkin_RenderDepth(VSInputNmTxWeights In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	//�X�L���s����v�Z�B
	float4x4 skinning = CalcSkinMatrix(In);
	//���[���h���W�A�@���A�ڃx�N�g�����v�Z�B
	float4 pos = mul(skinning, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
	
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float3 lig = 0.0f;
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - In.Pos);
	//�]�x�N�g�����v�Z����B
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//�A���x�h�B
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//�@�����v�Z�B
	float3 normal = CalcNormal( In.Normal, biNormal, In.Tangent, In.TexCoord);
	
	float4 spec = 0.0f;
	if(hasSpecularMap){
		spec = specularMap.Sample(Sampler, In.TexCoord);
	}
	//�e�}�b�v���Q�Ƃ���B
	float2 uv = In.posInProj.xy / In.posInProj.w;
	uv = (uv * float2(0.5f, -0.5f)) + 0.5f;
	float shadow = softShadowMap.Sample(Sampler, uv).r ;	
	
	float4 finalColor = PBR(
		albedo, 
		In.Tangent, 
		normal, 
		biNormal, 
		In.Pos, 
		spec,
		shadow,
		In.posInProj,
		materialID
	);
	//���Ȕ��������Z�B
	finalColor.xyz += emissionColor;
	return finalColor;
}


/*!
 *@brief	Z�l���������ނ��߂����̕`��p�X�Ŏg�p�����s�N�Z���V�F�[�_�[�B
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
float4 PSMain_RenderDepth( PSInput_RenderToDepth In ) : SV_Target0
{
	float z = In.posInProj.z / In.posInProj.w;
	return z;
}
/*!
 * @brief	G-Buffer�������ݗp�̕`��p�X�Ŏg�p�����s�N�Z���V�F�[�_�[�B
 */
PSOutput_RenderGBuffer PSMain_RenderGBuffer( PSInput In )
{
	PSOutput_RenderGBuffer Out = (PSOutput_RenderGBuffer)0;
	
	//�A���x�h�B
	Out.albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//�X�y�L�����B
	Out.spacular = 0.0f;
	if (hasSpecularMap) {
		float4 spec = specularMap.Sample(Sampler, In.TexCoord);
		Out.spacular.x = spec.x; 
		Out.spacular.y = spec.y;
	}
	//�]�x�N�g�����v�Z����B(todo �����G-Buffer�ɏo�����E�E�E)
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));

	//�@�����v�Z�B
	Out.normal = CalcNormal(In.Normal, biNormal, In.Tangent, In.TexCoord);
	
	//�ڃx�N�g���B
	Out.tangent = In.Tangent;

	//�V���h�E�}�X�N�o�͂���B
	if(isPCFShadowMap){
		//PCF��������B
		Out.shadow = CalcSoftShadow(In.Pos);
	}else{
		//�������Ȃ��B
		Out.shadow = CalcShadow(In.Pos);
	}
	//�ˉe��Ԃł̐[�x�l��x�ɁB
	Out.depth.x = In.posInProj.z / In.posInProj.w;
	//�J������Ԃł̐[�x�l��y�ɁB
	Out.depth.y = In.posInView.z;
	//�}�e���A��ID
	Out.materialID = (float)materialID;
	//���Ȕ����F�B
	Out.emissionColor = emissionColor;

	return Out;
}


TextureCube<float4> skyCubeMap : register(t0);	//�X�J�C�L���[�u�}�b�v�B

/*!
 *@brief	��p�̃V�F�[�_�[�B
 */
float4 PSMain_SkyCube( PSInput In ) : SV_Target0
{
	float4 color = skyCubeMap.Sample( Sampler, In.Normal);
	color.xyz += emissionColor;
	return color ;
}

/*!
 *@brief	�V���G�b�g�`��B
 * GameDemo�̂��߂̃X�y�V�����V�F�[�_�[�B
 */
float4 PSMain_Silhouette( PSInput In ) : SV_Target0
{
	float2 screenPos = In.posInProj.xy / In.posInProj.w;
	screenPos = screenPos * float2( 0.5f, -0.5f ) + 0.5f;
	
#if 1 ////�f�B�U�����O�������B
	//�f�B�U�p�^�[��
	static const int pattern[] = {
	    0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
	    48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
	    12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
	    60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
	    3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
	    51, 19, 59, 27, 49, 17, 57, 25,
	    15, 47,  7, 39, 13, 45,  5, 37,
	    63, 31, 55, 23, 61, 29, 53, 21 
	};
	screenPos.x *= 1.7777f;
	float2 uv = fmod(screenPos * 200.0f, 8.0f);
	float t = 0.0f;
	int x = (int)uv.x;
	int y = (int)uv.y;
	int index = y * 8 + x;
	t = (float)pattern[index] / 64.0f;
	//�f�B�U
	clip(t - 0.5f);
	return float4(t, t, t, 1.0f);

#else
	screenPos.x *= 1.7777f;		//�A�X�y�N�g���������B
	return silhouetteTexture.Sample(Sampler, screenPos * 12.0f) * 4.0f;
#endif
}