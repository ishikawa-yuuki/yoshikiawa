/*!
 * @brief	�u���[���B
 */
 

struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};
struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

/*!
 * @brief	���_�V�F�[�_�[�B
 */
PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}
Texture2D<float4> sceneTexture : register(t0);	//�V�[���e�N�X�`���B
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////
// �P�x���o�p
/////////////////////////////////////////////////////////
/*!
 * @brief	�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
 */
float4 PSSamplingLuminance(PSInput In) : SV_Target0
{
	float2 texSize;
	float level;
	sceneTexture.GetDimensions( 0, texSize.x, texSize.y, level );
	float2 tex = In.uv;
	tex += float2( -0.5/texSize.x, -0.5/texSize.y);
	float4 color = sceneTexture.Sample(Sampler, tex );
	float t = dot( color.xyz, float3(0.2125f, 0.7154f, 0.0721f) );
	clip(t - 1.001f);			//�P�x��1.0�ȉ��Ȃ�s�N�Z���L��
	color.xyz *= (t - 1.0f);
	color.a = 1.0f;
	return color;
}


/////////////////////////////////////////////////////////
// �u���[
/////////////////////////////////////////////////////////
struct PS_BlurInput{
	float4 pos	: SV_POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};

Texture2D<float4> luminanceTexture : register(t0);	//�P�x�e�N�X�`���B

/*!
 * @brief	�u���[�p�̒萔�o�b�t�@�B
 */
cbuffer CBBlur : register(b0)
{
	float4 offset;		//!<�I�t�Z�b�g�B
	float4 weight[2];	//!<�d�݁B
	
}
/*!
 * @brief	X�u���[���_�V�F�[�_�[�B
 */
PS_BlurInput VSXBlur(VSInput In)
{
	float2 texSize;
	float level;
	luminanceTexture.GetDimensions( 0, texSize.x, texSize.y, level );
	PS_BlurInput Out;
	Out.pos = In.pos;
	float2 tex = In.uv;
	tex += float2( -0.5/texSize.x, -0.5/texSize.y);
	Out.tex0 = tex + float2( - 1.0f/texSize.x, 0.0f );
    Out.tex1 = tex + float2( - 3.0f/texSize.x, 0.0f );
    Out.tex2 = tex + float2( - 5.0f/texSize.x, 0.0f );
    Out.tex3 = tex + float2( - 7.0f/texSize.x, 0.0f );
    Out.tex4 = tex + float2( - 9.0f/texSize.x, 0.0f );
    Out.tex5 = tex + float2( -11.0f/texSize.x, 0.0f );
    Out.tex6 = tex + float2( -13.0f/texSize.x, 0.0f );
    Out.tex7 = tex + float2( -15.0f/texSize.x, 0.0f );
    return Out;
}

/*!
 * @brief	Y�u���[���_�V�F�[�_�[�B
 */
PS_BlurInput VSYBlur(VSInput In)
{
	float2 texSize;
	float level;
	luminanceTexture.GetDimensions( 0, texSize.x, texSize.y, level );
	PS_BlurInput Out;
	Out.pos = In.pos;
	float2 tex = In.uv;
	tex += float2( -0.5/texSize.x, -0.5/texSize.y);
	Out.tex0 = tex + float2( 0.0f,- 1.0f/texSize.y  );
    Out.tex1 = tex + float2( 0.0f,- 3.0f/texSize.y  );
    Out.tex2 = tex + float2( 0.0f,- 5.0f/texSize.y  );
    Out.tex3 = tex + float2( 0.0f,- 7.0f/texSize.y  );
    Out.tex4 = tex + float2( 0.0f,- 9.0f/texSize.y  );
    Out.tex5 = tex + float2( 0.0f,-11.0f/texSize.y  );
    Out.tex6 = tex + float2( 0.0f,-13.0f/texSize.y  );
    Out.tex7 = tex + float2( 0.0f,-15.0f/texSize.y  );
    return Out;
}

/*!
 * @brief	�u���[�s�N�Z���V�F�[�_�[�B
 */
float4 PSBlur( PS_BlurInput In ) : SV_Target0
{
	float4 Color;
	Color  = weight[0].x * (luminanceTexture.Sample( Sampler, In.tex0 )
	               + luminanceTexture.Sample( Sampler, In.tex7 + offset ));
	Color += weight[0].y * (luminanceTexture.Sample( Sampler, In.tex1 )
	               + luminanceTexture.Sample( Sampler, In.tex6 + offset ));
	Color += weight[0].z * (luminanceTexture.Sample( Sampler, In.tex2 )
	          + luminanceTexture.Sample( Sampler, In.tex5 + offset ));
	Color += weight[0].w * (luminanceTexture.Sample( Sampler, In.tex3 )
	               + luminanceTexture.Sample( Sampler, In.tex4 + offset ));
	Color += weight[1].x * (luminanceTexture.Sample( Sampler, In.tex4 )
	               + luminanceTexture.Sample( Sampler, In.tex3 + offset ));
	Color += weight[1].y * (luminanceTexture.Sample( Sampler, In.tex5 )
	               + luminanceTexture.Sample( Sampler, In.tex2 + offset ));
	Color += weight[1].z * (luminanceTexture.Sample( Sampler, In.tex6 )
	               + luminanceTexture.Sample( Sampler, In.tex1 + offset ));
	Color += weight[1].w * (luminanceTexture.Sample( Sampler, In.tex7 )
	                 + luminanceTexture.Sample( Sampler, In.tex0 + offset ));
	return float4(Color.xyz, 1.0f);
}

/////////////////////////////////////////////////////////
// ����
/////////////////////////////////////////////////////////

Texture2D<float4> combineTexture00 : register(t0);
Texture2D<float4> combineTexture01 : register(t1);	
Texture2D<float4> combineTexture02 : register(t2);	
Texture2D<float4> combineTexture03 : register(t3);	
Texture2D<float4> combineTexture04 : register(t4);	
/*!
 * @brief	�����B
 */
float4 PSCombine( PSInput In ) : SV_Target0
{
	float2 uv = In.uv;
	float4 combineColor = combineTexture00.Sample(Sampler, uv);
	combineColor += combineTexture01.Sample(Sampler, uv);
	combineColor += combineTexture02.Sample(Sampler, uv);
	combineColor += combineTexture03.Sample(Sampler, uv);
	combineColor += combineTexture03.Sample(Sampler, uv);
	combineColor /= 5.0f;
	combineColor.a = 1.0f;
	return combineColor;
}