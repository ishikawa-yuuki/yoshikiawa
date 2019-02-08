/*!
 * @brief	���f����SRV�B
 */

StructuredBuffer<SDirectionLight> directionLight : register(t100);
StructuredBuffer<SPointLight> pointLightList : register(t101);
//�^�C���Ɋ܂܂��|�C���g���C�g�̃��X�g�B
StructuredBuffer<uint> pointLightListInTile : register(t102);
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t103);
//�C���X�^���V���O�`��p
StructuredBuffer<float4x4> instanceMatrix : register(t104);


Texture2D<float4> albedoTexture : register(t0);	//�A���x�h�e�N�X�`���B
Texture2D<float4> normalMap : register(t1);		//�@���}�b�v�B
Texture2D<float4> specularMap : register(t2);	//�X�y�L�����}�b�v�B

Texture2D<float4> shadowMap_0 : register(t3);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_1 : register(t4);		//�V���h�E�}�b�v�B
Texture2D<float4> shadowMap_2 : register(t5);		//�V���h�E�}�b�v�B
Texture2D<float4> silhouetteTexture : register(t6);	//�V���G�b�g�e�N�X�`���B
Texture2D<float4> softShadowMap : register(t7);		//�\�t�g�V���h�E�}�b�v�B
Texture2D<float4> depthMap : register(t8);			//�[�x�}�b�v�B
Texture2D<float4> tangentMap : register(t9);			//�^���W�F���g�}�b�v�B
Texture2D<float4> materialIDMap : register(t10);		//�}�e���A��ID�B
Texture2D<float4> emissionColorTexture : register(t11);	//�G�~�b�V�����J���[�B

sampler Sampler : register(s0);

