/*!
 *@brief	��p�̃s�N�Z���V�F�[�_�[�B
 * model.fx�ŃC���N���[�h����Ă��܂��B
 */
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