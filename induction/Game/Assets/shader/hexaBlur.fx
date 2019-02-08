/*!
 *@brief	�Z�p�`�u���[�B
 */
 

#include "common.h"

struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

/*!
 *@brief	�萔�o�b�t�@�B
 */
cbuffer cbParam : register( b0 ){
	float2 texSize : packoffset(c0);		//�u���[��������e�N�X�`���̃T�C�Y�B
	float radius : packoffset(c0.z);		//�u���[�������锼�a�B
};
/*!
 *@brief	���_�V�F�[�_�[�B
 */
PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}

//1�p�X�ڂ̃s�N�Z���V�F�[�_�[�̏o�́B
struct PSOutput_1{
	float4 color_0 : SV_Target0;	//�����u���[�̏o�͐�
	float4 color_1 : SV_Target1;	//�΂߃u���[�̏o�͐�B
};

Texture2D<float4> originalTexture	: register(t0);		//�u���[��������O�̃I���W�i���e�N�X�`���B

/*!
 *@brief	�����A�΂߃u���[�̃s�N�Z���V�F�[�_�[�B
 */
PSOutput_1 PSVerticalDiagonalBlur(PSInput pIn)
{
	//�u���[�X�e�b�v�̒����B8�e�N�Z�����Ƀu���[��������ꍇ�́A
	//blurStepLen��1.0�ɂȂ�B16�e�N�Z�����Ƀu���[���~�ꍇ�́AblurStepLen��2.0�ɂȂ�B
	//8�e�N�Z���t�F�b�`���ău���[��������̂ŁAblurStepLen��2.0�̏ꍇ�́A2 �~ 8 ��16�e�N�Z����
	//�u���[��������B
	float blurStepLen = radius / 4.0f;
	
	float4 sceneColor = originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv );
		
	float2 uvOffset = float2(0.0f, -1.0f / texSize.y );
	uvOffset *= blurStepLen;
	
	PSOutput_1 psOut = (PSOutput_1)0;
	
	psOut.color_0 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset );
		
	psOut.color_0 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 2 );
		
	psOut.color_0 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 3 );
		
	psOut.color_0 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 4 );
		
	psOut.color_0 /= 4.0f;	
	
	uvOffset.x = -0.86602f / texSize.x;
	uvOffset.y = 0.5f / texSize.y;
	uvOffset *= blurStepLen;
	
	psOut.color_1 = originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset );
	
	psOut.color_1 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 2 );
		
	psOut.color_1 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 3 );
		
	psOut.color_1 += originalTexture.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 4 );
		
	psOut.color_1 += sceneColor;
	psOut.color_1 /= 5.0f;
	psOut.color_1 += psOut.color_0;
	return psOut;
}

Texture2D<float4> blurTexture_0	: register(t0);		//�u���[�e�N�X�`��_0�B1�p�X�ڂō쐬���ꂽ�e�N�X�`���B
Texture2D<float4> blurTexture_1	: register(t1);		//�u���[�e�N�X�`��_1�B1�p�X�ڂō쐬���ꂽ�e�N�X�`���B

float4 PSCombineVerticalDiagonalBlur(PSInput pIn) : SV_Target0
{
	float4 color = blurTexture_0.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv );
	float coc = color.a;
	
	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv );
	
	return float4( color.xyz, coc );
}
/*!
 *@brief	�Z�p�`�쐬�u���[
 */
float4 PSRhomboidBlur(PSInput pIn) : SV_Target0
{
	//�u���[�X�e�b�v�̒����B8�e�N�Z�����Ƀu���[��������ꍇ�́A
	//blurStepLen��1.0�ɂȂ�B16�e�N�Z�����Ƀu���[���~�ꍇ�́AblurStepLen��2.0�ɂȂ�B
	//8�e�N�Z���t�F�b�`���ău���[��������̂ŁAblurStepLen��2.0�̏ꍇ�́A2 �~ 8 ��16�e�N�Z����
	//�u���[��������B
	float blurStepLen = radius / 4.0f;
		
	float2 uvOffset;
	uvOffset.x = -0.86602f / texSize.x;
	uvOffset.y = 0.5f / texSize.y;
	uvOffset *= blurStepLen;
	
	float4 color = blurTexture_0.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset );
		
	color += blurTexture_0.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 2 );
	
	color += blurTexture_0.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 3 );
	
	color += blurTexture_0.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 4 );
	

	uvOffset.x = 0.86602f / texSize.x * blurStepLen;

	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv );
		
	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset );
		
	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 2 );
	
	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 3 );
	
	color += blurTexture_1.Sample(
		clamp_clamp_clamp_linearSampler, pIn.uv + uvOffset * 4 );
	
	color /= 9.0f;
	
	return color;
}