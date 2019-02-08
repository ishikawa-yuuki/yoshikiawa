/*!
 * @brief	���C�g�v�Z�֌W�B
 */


#define TILE_WIDTH	16		//�^�C���̕��B

float3 CalcSpecular(float3 lightDir, float4 lightColor, float3 toEyeReflection, float specPow)
{
	return lightColor.xyz * pow(max(0.0f, dot(-lightDir,toEyeReflection)), 2 ) * lightColor.w * specPow;
}
/*!
 * @brief	�f�B���N�V�������C�g�̉e�����v�Z�B
 *@param[in]	albedo			�A���x�h�B
 *@param[in]	posInWorld		���[���h��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 *@param[in]	specPow			�X�y�L�������x�B
 *@param[in]	shadow			�e�̗����闦(1.0�Ŋ��S�ɉe�������Ă���B)
 */
float3 CalcDirectionLight(
	float4 albedo,
	float3 posInWorld, 
	float3 normal,
	 float3 tangent,
	float3 biNormal, 
	float3 toEyeDir, 
	float3 toEyeReflection, 
	float roughness,
	float specPow,
	uint uMatID,
	float shadow
)
{
	float3 lig = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		if( shadow < 1.0f){
			//�e�̗�����m����1.0�ȉ��̎������v�Z����B		
			if( 1 << uMatID & directionLight[i].lightingMaterialIDGroup ){
				float3 lightDir = directionLight[i].direction;
				float t = saturate( dot( normal, -lightDir ) ) * ( 1.0f - shadow );
				lig += BRDF(-lightDir, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow ) * directionLight[i].color * t ;
				
			}
		}
		//�Օ�����f�B���N�V�������C�g�͍ŏ��̈�{�����B
		shadow = 0.0f;
	}
	
	return lig;
}
/*!
 * @brief	�|�C���g���C�g���v�Z�B
 *@param[in]	posInWorld		���[���h���W�n�ł̍��W�B
 *@param[in]	posInProj		�ˉe��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	tangent			�ڃx�N�g���B
 *@param[in]	biNormal		�]�x�N�g���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 */
float3 CalcPointLightInner(
	float4 albedo,
	float3 posInWorld, 
	float2 screenPos, 
	float3 normal,
	float3 tangent,
	float3 biNormal,
	float3 toEyeDir,
	float3 toEyeReflection, 
	float roughness,
	float specPow
)
{
	//�r���[�|�[�g���W�n�ɕϊ�����B
	float2 viewportPos = screenParam.zw * screenPos;
	//�X�N���[�����^�C���ŕ��������Ƃ��̃Z����X���W�����߂�B
	uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
	//�^�C���C���f�b�N�X���v�Z����B
	uint tileIndex = floor( viewportPos.x / TILE_WIDTH ) + floor( viewportPos.y / TILE_WIDTH ) * numCellX;
	
	//���̃s�N�Z�����܂܂��^�C���̃��C�g�C���f�b�N�X���X�g�̊J�n�ʒu���v�Z����B
	uint lightStart = tileIndex * numPointLight;
	//���̃s�N�Z�����܂܂��^�C���̃��C�g�C���f�b�N�X���X�g�̏I���ʒu���v�Z����B
	uint lightEnd = lightStart + numPointLight;
	
	float3 lig = 0.0f;
	for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++){
		uint lightIndex = pointLightListInTile[lightListIndex];
		if(lightIndex == 0xffffffff){
			//���̃^�C���Ɋ܂܂��|�C���g���C�g�͂����Ȃ��B
			break;
		}
		SPointLight light = pointLightList[lightIndex];
		if( 1 << materialID & light.lightingMaterialIDGroup ){
			float3 lightDir = posInWorld - light.position;
			float len = length(lightDir);
			lightDir /= max( 0.01f, len );	//���K���B
			float t = saturate(-dot(normal, lightDir));
			float3 pointLightColor = BRDF(-lightDir, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow) * light.color.xyz * t;
			//�������v�Z����B
			float	litRate = len / light.attn.x;
			float	attn = max(1.0 - litRate * litRate, 0.0);
			pointLightColor *= pow(attn, light.attn.y);
			lig += pointLightColor;
		}
		
	}
	
	return lig;
}

/*!
 * @brief	�f�B���N�V�������C�g�̉e�����v�Z�B
 *@param[in]	albedo			�A���x�h�B
 *@param[in]	posInWorld		���[���h��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 *@param[in]	specPow			�X�y�L�������x�B
 */
float3 CalcPointLightInner(
	float4 albedo,
	float3 posInWorld, 
	float3 normal,
	 float3 tangent,
	float3 biNormal, 
	float3 toEyeDir, 
	float3 toEyeReflection, 
	float roughness,
	float specPow
)
{
	float3 lig = 0.0f;
	for( int i = 0; i < numDirectionLight; i++){
		if( 1 << materialID & directionLight[i].lightingMaterialIDGroup ){
			float3 lightDir = directionLight[i].direction;
			float t = saturate( dot( normal, -lightDir ) );
			lig += BRDF(-lightDir, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow ) * directionLight[i].color * t;
		}
	}
	
	return lig;
}
/*!
 * @brief	�|�C���g���C�g���v�Z�B
 *@param[in]	posInWorld		���[���h���W�n�ł̍��W�B
 *@param[in]	posInProj		�ˉe��Ԃł̍��W�B
 *@param[in]	normal			�@���B
 *@param[in]	tangent			�ڃx�N�g���B
 *@param[in]	biNormal		�]�x�N�g���B
 *@param[in]	toEye			���_�܂ł̃x�N�g���B
 */
float3 CalcPointLight(
	float4 albedo,
	float3 posInWorld, 
	float4 posInProj, 
	float3 normal,
	float3 tangent,
	float3 biNormal,
	float3 toEyeDir,
	float3 toEyeReflection, 
	float roughness,
	float specPow
)
{
	
	//�X�N���[���̍����(0,0)�A�E����(1,1)�Ƃ�����W�n�ɕϊ�����B
	float2 screenPos = (posInProj.xy / posInProj.w) * float2(0.5f, -0.5f) + 0.5f;
	return CalcPointLightInner(
						 	albedo, 
							posInWorld, 
							screenPos, 
							normal, 
							tangent, 
							biNormal, 
							toEyeDir, 
							toEyeReflection, 
							roughness, 
							specPow );
}


/*!
 * @brief	����
 */
float3 CalcAmbientLight(
	float4 albedo,
	float3 normal,
	float3 tangent,
	float3 biNormal, 
	float3 toEyeDir, 
	float roughness,
	float specPow
)
{
	return BRDF(normal, toEyeDir, normal, tangent, biNormal, albedo, roughness, specPow) * ambientLight;
}