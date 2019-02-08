/*!
 * @brief	�e�̃u���[�����B
 */

/*!
 * @brief	�u���[�B
 */

struct PS_BlurInput{
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD0;
};

Texture2D<float4> blurTexture : register(t0);	//�u���[�e�N�X�`���B
Texture2D<float4> depthTexture : register(t1);	//�[�x�e�N�X�`���B



struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};
struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};
sampler Sampler : register(s0);

/*!
 * @brief	�u���[�p�̒萔�o�b�t�@�B
 */
cbuffer CBBlur : register(b0)
{
	float4 weight;				//!<�d�݁B
	float4x4	mtxProj;		// ���e�s��
	float4x4 	mtxProjInv;		// ���e�s��̋t�s��B
	float offsetTexelWorld;		// �u���[�̎��Ƀt�F�b�`����I�t�Z�b�g���W�B���[���h��Ԃ̗ʁB�l���傫���قǑ傫���{�P��B
};
/*!
 * @brief	X�u���[���_�V�F�[�_�[�B
 */
PS_BlurInput VSBlur(VSInput In)
{
	PS_BlurInput Out;
	Out.pos = In.pos;
	float2 tex = In.uv;
	Out.uv = In.uv;
    return Out;
}

float4 Blur(float2 uv, float2 offset[4])
{
	float4 Color  = weight.x * (blurTexture.Sample( Sampler, uv + offset[0] )
	               + blurTexture.Sample( Sampler, uv - offset[0] ));
	               
	Color += weight.y * (blurTexture.Sample( Sampler, uv + offset[1] )
	               + blurTexture.Sample( Sampler, uv - offset[1] ));
	               
	Color += weight.z * (blurTexture.Sample( Sampler, uv + offset[2] )
	          + blurTexture.Sample( Sampler, uv - offset[2] ));
	          
	Color += weight.w * (blurTexture.Sample( Sampler, uv + offset[3] )
	               + blurTexture.Sample( Sampler, uv - offset[3] ));
	               
	return Color;
}
/*!
 * @brief	UV���W���J�������W�n�ɕϊ�����B
 */
float4 CalcUVToPosInCamera( float2 uv)
{
	float depth = depthTexture.Sample(Sampler, uv).r;
	float4 posInCamera = float4(uv, depth, 1.0f);
	//xy���ˉe��Ԃɕω�����B
	posInCamera.xy = posInCamera.xy * float2( 2.0f, -2.0f ) - float2( 1.0f, -1.0f);
	posInCamera = mul(mtxProjInv, posInCamera);
	posInCamera /= posInCamera.w;
	return posInCamera;
}

/*!
 * @brief	X�u���[�s�N�Z���V�F�[�_�[�B
 */
float4 PSXBlur( PS_BlurInput In ) : SV_Target0
{
	float4 Color;
	
	//�J������Ԃł̋ߖT�s�N�Z�������߂�B
	float4 posInCamera = CalcUVToPosInCamera(In.uv);
	
	//�ǂꂭ�炢����Ă���Ƃ���𒲂ׂ邩�͌�Œ萔�o�b�t�@�ő���悤�ɂ�����ŁB
	//X�������ɒ��ׂ�B
	float2 offset[4];
	for(int i = 0; i < 4; i++){
		posInCamera.x += offsetTexelWorld;
		float4 pos = posInCamera;
		pos = mul(mtxProj, pos);
		offset[i] = (pos.xy / pos.w) * float2(0.5f, -0.5f) + 0.5f;
		float4 posInCamera2 = CalcUVToPosInCamera(offset[i]);
		
		if(abs(posInCamera.z - posInCamera2.z) < 5.0f){
			offset[i] -= In.uv ;
		}else{
			offset[i] = 0.0f;
		}
	}
	return Blur(In.uv, offset);
}

/*!
 * @brief	Y�u���[�s�N�Z���V�F�[�_�[�B
 */
float4 PSYBlur( PS_BlurInput In ) : SV_Target0
{
	float4 Color;
	
	//�J������Ԃł̋ߖT�s�N�Z�������߂�B
	float4 posInCamera = CalcUVToPosInCamera(In.uv);
	
	//�ǂꂭ�炢����Ă���Ƃ���𒲂ׂ邩�͌�Œ萔�o�b�t�@�ő���悤�ɂ�����ŁB
	//X�������ɒ��ׂ�B
	float2 offset[4];
	for(int i = 0; i < 4; i++){
		posInCamera.y += offsetTexelWorld;
		float4 pos = posInCamera;
		pos = mul(mtxProj, pos);
		offset[i] = (pos.xy / pos.w) * float2(0.5f, -0.5f) + 0.5f;
		float4 posInCamera2 = CalcUVToPosInCamera(offset[i]);
		
		if(abs(posInCamera.z - posInCamera2.z) < 5.0f){
			offset[i] -= In.uv ;
		}else{
			offset[i] = 0.0f;
		}
		
	}
	return Blur(In.uv, offset);
	
}
