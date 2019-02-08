/*!
 *@brief	Dof(��ʊE�[�x)
 *@details
 * ��ʊE�[�x���̃s�N�Z����\���}�X�N�摜�̍쐬�ƁA�e�s�N�Z����CoC�̌v�Z���s���B
 */

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
Texture2D<float4> depthTexture : register(t1);	//�[�x�e�N�X�`���By�ɃJ������Ԃ��猩���[�x�l���i�[����Ă���B

sampler pointSampler : register(s0);			//�|�C���g�T���v�����O���s���T���v���B

/*!
 *@brief	�s�N�Z���V�F�[�_�[�ւ̓��́B
 */
struct PSIn{
	float4 position : SV_Position;
	float2 uv		: TEXCOORD0;
};
/*!
 *@brief	�s�N�Z���V�F�[�_�[����̏o�́B
 */
struct PSOutput{
	float4 colorAndCoc : SV_Target0;	//�V�[���̃J���[����CoC�BCoC�̓��`�����l���Ɋi�[����Ă���B
};
/*!
 *@brief	�萔�o�b�t�@�B
 * ���̒��g��ύX������AtkDof.h��SCreateCocParamCB��
 * �X�V����B
 */
cbuffer cbParam : register( b0 )
{
	float4 dofRange;		//��ʊE�[�x�͈̔͂�\���f�[�^�BSetDofRangeParam�֐��Őݒ肳���f�[�^�B
							//x�͎�O�{�P�̌������J�n����J��������̋����B
							//y�͎�O�{�P�̌������I������J��������̋����B
							//z�͉��{�P�̑������J�n����J��������̋����B
							//w�͉��{�P�̑������I������J��������̋����B
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
PSOutput PSMain( PSIn psIn )
{
	PSOutput psOutput = (PSOutput)0;
	//�J������Ԃ���̋������T���v�����O�B
	float depth = depthTexture.Sample( pointSampler, psIn.uv ).y;
	//�V�[���̃J���[���t�F�b�`�B
	psOutput.colorAndCoc = sceneTexture.Sample( pointSampler, psIn.uv );
	
	//CoC��K���Ɍv�Z����B���K���Ȃ̂ŕ����I�Ȑ������͊F���I
	//�����Ōv�Z���Ă���CoC�͒P���Ɏ�O�{�P�Ɖ��{�P�͈̔͂ŁA�ǂ̂�����ɂ���̂���\��
	//���K�����ꂽ0.0�`1.0�̒l�ł��B
	//dofRange.w - dofRange.z��dofRange.y - dofRange.x�̌��ʂ́A
	//�K��0�ȏ�ɂȂ邱�Ƃ�cpu���ŕۏ؂��Ă��܂��B
	//���̂��߁A0���Z���V�F�[�_�[���ōl������K�v�͂���܂���B
	//�ڍׂ�CDof::SetDofRangeParam�֐����Q�ƁB
	
	//�܂��͉��{�P�B
	float farCoc = max( 0.0f, depth - dofRange.z ) / ( dofRange.w - dofRange.z );
	//�����Ď�O�{�P�B
	float nearCoc = max(0.0f, dofRange.y - depth ) / ( dofRange.y - dofRange.x );
	//�傫���ق���coc���̗p����B�ǂ��炩����͕K��0�ɂȂ�ˁB
	float coc = max( farCoc, nearCoc );
	coc = min(1.0f, coc);
	//����CoC���i�[����I
	psOutput.colorAndCoc.a = coc;

	return psOutput;
}
