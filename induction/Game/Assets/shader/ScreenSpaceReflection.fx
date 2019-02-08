/*!
 * @brief	SSR
 */
#include "CommonFunc.h"

struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

//�J�����p�����[�^�̒萔�o�b�t�@
cbuffer cb : register(b0){
	float4x4 mViewProjInv;				//�r���[�v���W�F�N�V�����s��̋t�s��B
	float4x4 mViewProj;					//�r���[�v���W�F�N�V�����s��B
	float4x4 mViewProjInvLastFrame;		//1�t���[���O�̃r���[�v���W�F�N�V�����s��B
	float4 cameraPosInWorld;	//���[���h���W�n�ł̃J�����̎��_�B
	float4 renderTargetSize;	//�����_�����O�^�[�Q�b�g�̃T�C�Y�BPSFinal�ł����g�p�ł��܂���B
								//�ق��̉ӏ��Ŏg�������Ȃ�Acpp���̑Ή����K�v�ł��B
	float rayMarchStepRate;		//���C�}�[�`�̃X�e�b�v���[�g�B�B
};

Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
Texture2D<float4> normalTexture : register(t1);	//�@���e�N�X�`���B
Texture2D<float4> depthTexture : register(t2);	//�[�x�e�N�X�`���B
Texture2D<float4> lastFrameDepthTexture : register(t3);	//1�t���[���O�̐[�x�e�N�X�`���B

sampler Sampler : register(s0);



PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}
float GetRandomNumber(float2 texCoord, float Seed)
{
	return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}
float4 PSMain( PSInput In ) : SV_Target0
{
	//�s�N�Z���̃��[���h���W���v�Z����B
	float3 worldPos = CalcWorldPosFromUVZ(
		In.uv,
		depthTexture.Sample(Sampler, In.uv).r,
		mViewProjInv
	);
	//1�t���[���O�̃s�N�Z���̃��[���h���W���v�Z����B
	float3 worldPosLastFrame = CalcWorldPosFromUVZ(
		In.uv,
		lastFrameDepthTexture.Sample(Sampler, In.uv).r,
		mViewProjInvLastFrame
	);
	float len = length(worldPos - worldPosLastFrame);
	float alpha = lerp(0.1f, 0.5f, min(1.0f, len / 1.0f));
	float4 sceneColor = sceneTexture.Sample(Sampler, In.uv);
	//�s�N�Z���̖@�����擾�B
	float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
	//�J�����̎��_����s�N�Z���Ɍ������x�N�g�����v�Z����B
	float3 toPixelDir = normalize( worldPos - cameraPosInWorld );
	//���˃x�N�g�������߂�B
	float3 toPixelDirReflect = reflect( toPixelDir, normal );
	//���˃x�N�g�����g���āA���C�}�[�`���O���s���B
	//���C�}�[�`���O�̃C�e���[�V�����񐔂Ɛ�����L�΂�������
	//��Œ萔�o�b�t�@�ɂ�����ŁH
	int maxRayNum = 20;
	float3 raystep = 100.0f/maxRayNum * toPixelDirReflect;
	float maxThickness = 0.01f / maxRayNum;
	for( int step = 1; step < maxRayNum; step++){ //�������g�ƂԂ���̂ŁAstep��1����i�߂�B
		float3 rayPos = worldPos + step * raystep * lerp( 0.8f, 1.0f, GetRandomNumber(In.uv, rayMarchStepRate));
		float4 posInProj = float4	(rayPos, 1.0f);
		//�r���[�v���W�F�N�V������Ԃɕϊ�����B
		posInProj = mul(mViewProj, posInProj);
		posInProj.xyz /= posInProj.w;
		posInProj.xy = posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
		float pixelZ = depthTexture.Sample(Sampler, posInProj.xy).r;
		if (posInProj.z - pixelZ > 0 && posInProj.z - pixelZ < maxThickness) {
			//�Ԃ������̂Ń��C�}�[�`���O�������݂ɍs���Đ��x���グ��B�B
			float sign = -1.0;
			/*for (int m = 1; m <= 4; ++m) {
				rayPos += raystep * (sign * pow(0.5, m));
				posInProj = mul(mViewProj, float4(rayPos, 1.0f));
				posInProj.xyz /= posInProj.w;
				posInProj.xy = posInProj.xy * float2(0.5f, -0.5f) + 0.5f;
				float pixelZ = depthTexture.Sample(Sampler, posInProj.xy).r;
				sign = posInProj.z - pixelZ > 0 ? -1 : 1;
			}*/
			float4 reflectColor = sceneTexture.Sample(Sampler, posInProj.xy);
			return float4(reflectColor.xyz, alpha);
		}
	}
	return float4(sceneColor.xyz, alpha);
}

Texture2D<float4> reflectTexture : register(t1);		//���˃e�N�X�`���B
Texture2D<float4> specTexture : register(t2);	//�X�y�L���b��


//�ŏI�����B
float4 PSFinal(PSInput In) : SV_Target0
{
	//���˃J���[�̕��ς��Ƃ�B
	float4 reflectColor = reflectTexture.Sample(Sampler, In.uv);
	float4 sceneColor = sceneTexture.Sample(Sampler, In.uv);
	//�f�荞�݂���B
	float spec = min( 1.0f, specTexture.Sample(Sampler, In.uv).r );
	//spec *= all(max(0.0f, length(reflectColor.xyz)-0.1f));
	sceneColor.xyz = lerp(sceneColor.xyz, reflectColor.xyz, spec);
	return float4(sceneColor.xyz, 1.0f);

}
