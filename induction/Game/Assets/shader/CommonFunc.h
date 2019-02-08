/*!
 * @brief	UV���W�Ɛ[�x�l���烏�[���h���W���v�Z����B
 *@param[in]	uv				uv���W
 *@param[in]	zInScreen		�X�N���[�����W�n�̐[�x�l
 *@param[in]	mViewProjInv	�r���[�v���W�F�N�V�����s��̋t�s��B
 */
float3 CalcWorldPosFromUVZ( float2 uv, float zInScreen, float4x4 mViewProjInv )
{
	float3 screenPos;
	screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2( -1.0f, 1.0f);
	screenPos.z = zInScreen;//depthMap.Sample(Sampler, uv).r;
	
	float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
	worldPos.xyz /= worldPos.w;
	return worldPos.xyz;
}