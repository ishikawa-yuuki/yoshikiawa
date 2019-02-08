/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * �ŏI�����B
 */

Texture2D<float4> cocTexture : register(t0);			//CoC���������܂ꂽ�e�N�X�`��
Texture2D<float4> hexaBokeTexture : register(t1);		//�Z�p�`�u���[�Ő������ꂽ�{�P�e�N�X�`���B

sampler bilinearSampler : register(s0);			//�o�C���j�A�T���v�����O���s���T���v���B

/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSIn{
	float4 position : SV_Position;
	float2 uv		: TEXCOORD0;
};
/*!
 *@brief	�萔�o�b�t�@�B
 * ���̒��g��ύX������AtkDof.h��CFinalCB��
 * �X�V����B
 */
cbuffer cbParam : register( b0 )
{
	float bokeTextureLuminance;
};
/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSIn VSMain( float4 pos : POSITION, float2 uv : TEXCOORD0 )
{
	PSIn psIn = (PSIn)0;
	psIn.position = pos;
	psIn.uv = uv;
	return psIn;
}
/*!
 *@brief	�s�N�Z���V�F�[�_�[�B
 */
float4 PSMain( PSIn psIn ) : SV_Target0
{
	
	//�s�N�Z����CoC���擾�B
	float4 color = cocTexture.Sample( bilinearSampler, psIn.uv);
	float coc = color.a;
	coc = min( 1.0f, coc );
	//�����~�̔��a��0.001�ȉ��̓{�P�Ȃ��̂ŁA�s�N�Z���L���B
	clip( coc - 0.0001f );
	
	float4 bokeColor = hexaBokeTexture.Sample(bilinearSampler, psIn.uv) * 0.7f * bokeTextureLuminance;
	
	//CoC�����̂܂܃u�����f�B���O���B
	float blendRate = min( 1.0f, coc ) ;
	
	float4 blendColor = lerp(color, bokeColor, blendRate);
	//�K���Ƀ{�P�{�P
	return float4(blendColor.xyz, 1.0f);
}
