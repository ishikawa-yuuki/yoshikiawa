/*!
 * @brief	���f���p�̃s�N�Z���V�F�[�_�[�B
 */

#include "LightingFunction.h"

/*!
 * @brief	�����x�[�X�����_�����O�B
 */
float4 PBR( 
	float4 albedo,
	float3 tangent,
	float3 normal,
	float3 biNormal,
	float3 worldPos,
	float4 spec,
	float shadow,
	float2 screenPos,
	uint uMatID
) 
{

	float3 lig = 0.0f;
	//���_�܂ł̃x�N�g�������߂�B
	float3 toEye = normalize(eyePos - worldPos);

	//�X�y�L�����B
	float specPow = 0.0f;
	float roughness = 1.0f;

	specPow = spec.x;
	roughness = 1.0f - spec.y;
	
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if (toEyeLen > 0.001f) {
		toEyeDir = toEye / toEyeLen;
	}

	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;

	//�f�B���N�V�������C�g
	float3 finalColor = 0.0f;

	//�e��������\�����Ⴂ�ꍇ�̂݌v�Z����B
	finalColor = CalcDirectionLight(
		albedo,
		worldPos,
		normal,
		tangent,
		biNormal,
		toEyeDir,
		toEyeReflection,
		roughness,
		specPow,
		uMatID,
		shadow
	) ;

	//�|�C���g���C�g���v�Z�B
	finalColor += CalcPointLightInner(
		albedo,
		worldPos,
		screenPos,
		normal,
		tangent,
		biNormal,
		toEyeDir,
		toEyeReflection,
		roughness,
		specPow
	);

	//�A���r�G���g���C�g�B
	finalColor += CalcAmbientLight(
		albedo,
		normal,
		tangent,
		biNormal,
		toEyeDir,
		roughness,
		specPow
	);

	// brightness
	float brightness = 1.0f;
	finalColor *= brightness;
	/*
	// exposure
	float exposure = 1.0f;
	finalColor *= pow( 2.0, exposure );
	*/
	float gamma = 2.2f;
	finalColor = max(0.0f, pow(finalColor, 1.0 / gamma));
	if (isnan(finalColor.x) || isnan(finalColor.y) || isnan(finalColor.z)) {
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	return float4(finalColor, 1.0f);
}