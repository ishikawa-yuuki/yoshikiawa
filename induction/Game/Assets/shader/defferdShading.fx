/*!
 * @brief	�f�B�t�@�[�h�V�F�[�f�B���O�B
 */
#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"
#include "modelPSFunction.h"
#include "CommonFunc.h"

cbuffer PSDefferdCb : register( b0 )
{
	float4x4 mViewProjInv;	//�r���[�v���W�F�N�V�����s��̋t�s��B
};

struct VSDefferdInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSDefferdInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

PSDefferdInput VSMain( VSDefferdInput In ) 
{
	PSDefferdInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

/*!
 * @brief	UV���W���烏�[���h���W���v�Z����B
 */
float3 CalcWorldPosFromUV( float2 uv )
{
	return CalcWorldPosFromUVZ(
		uv, 
		depthMap.Sample(Sampler, uv).r, 
		mViewProjInv
	);
}
float4 PSMain( PSDefferdInput In ) : SV_Target0
{
	//�A���x�h�B
	float4 albedo = albedoTexture.Sample(Sampler, In.uv);

	//�ڃx�N�g�����擾�B�B
	float3 tangent = tangentMap.Sample(Sampler, In.uv);
	//�ڃx�N�g����Ԃ̖@�����擾�B
	float3 normal = normalMap.Sample(Sampler, In.uv);
	//�]�@�����v�Z�B(todo ��Ŏ����H	)
	float3 biNormal = normalize(cross(tangent, normal));

	//���[���h���W���v�Z����B
	float3 worldPos = CalcWorldPosFromUVZ(
		In.uv,
		depthMap.Sample(Sampler, In.uv).r,
		mViewProjInv
	);
	//�X�y�L�����B
	float4 spec = specularMap.Sample(Sampler, In.uv);
	
	float shadow = softShadowMap.Sample(Sampler, In.uv).r;
	
	uint uMatID = floor(materialIDMap.Sample(Sampler, In.uv).r + 0.001f);
	
	//�����x�[�X���C�e�B���O�B
	float4 finalColor = PBR(
		albedo, 
		tangent, 
		normal, 
		biNormal, 
		worldPos, 
		spec,
		shadow,
		In.uv,
		uMatID
	);
	
	//���Ȕ��������Z�B
	finalColor.xyz += albedo.xyz * emissionColorTexture.Sample( Sampler, In.uv).xyz;
	return finalColor;
}
