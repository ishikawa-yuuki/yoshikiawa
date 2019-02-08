/*!
 * @brief	���f���֌W�̍\���̃w�b�_�B
 */
 
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float2 TexCoord : TEXCOORD0;
    float4 Color    : COLOR;
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;
    float3 Normal   : NORMAL;
    float2 TexCoord	: TEXCOORD0;
    float3 Tangent	: TANGENT;
    uint4  Indices  : BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 Pos			: TEXCOORD1;		//���[���h���W�n�ł̒��_���W�B
	float3 posInView	: TEXCOORD2;		//�J������Ԃł̍��W�B
	float4 posInProj	: TEXCOORD3;		//���K�����W�n�ł̍��W�B
};
/*!
 *@brief	Z�l�̏������݂݂̂��s���s�N�Z���V�F�[�_�[�ւ̓��́B
 *@details
 * ���݂̓V���h�E�}�b�v�쐬��ZPrepass�Ŏg�p����Ă��܂��B
 */
struct PSInput_RenderToDepth{
	float4 Position 	: SV_POSITION;
	float4 posInProj	: TEXCOORD0;		//���K�����W�n�ł̍��W�B
};

/*!
 * @brief	G-Buffer�`��p�̃s�N�Z���V�F�[�_�[����̏o�́B
 */
struct PSOutput_RenderGBuffer{
	float4 albedo		: SV_Target0;		//�A���x�h
	float3 normal		: SV_Target1;		//�@���B
	float2 spacular		: SV_Target2;		//�X�y�L�����B
	float shadow		: SV_Target3;		//�V���h�E�B
	float2 depth		: SV_Target4;		//�[�x�l�B
	float3 tangent		: SV_Target5;		//�ڃx�N�g���B
	float materialID	: SV_Target6;		//�}�e���A��ID�B
	float3 emissionColor : SV_Target7;		//���Ȕ����F�B
};

/*!
 * @brief	�f�B���N�V�������C�g�B
 */
struct SDirectionLight{
	float4	color;			//!<���C�g�̃J���[�B
	float3	direction;		//!<���C�g�̕����B
	unsigned int lightingMaterialIDGroup;	//!<���C�g�̉e����^���鑊������ʂ���}�e���A��ID�O���[�v�B0xFFFFFFFF�ł��ׂẴI�u�W�F�N�g�Ƀ��C�g�𓖂Ă�B
};

//�|�C���g���C�g�B
struct SPointLight {
	float3	position;		//�ʒu�B
	float3	positionInView;	//�J�������W�n�ł̃|�C���g���C�g�̈ʒu�B
	float4	color;			//�J���[�B
	float4  attn;			//�����萔�B(x������������ƃ��C�g�̖��邳�������Ay��z���傫���Ȃ�ƃ��C�g�������܂œ͂��悤�ɂȂ�B)
	unsigned int lightingMaterialIDGroup;	//!<���C�g�̉e����^���鑊������ʂ���}�e���A��ID�O���[�v�B0xFFFFFFFF�ł��ׂẴI�u�W�F�N�g�Ƀ��C�g�𓖂Ă�B
};
