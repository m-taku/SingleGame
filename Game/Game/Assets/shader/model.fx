/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t2);	
//todo �V���h�E�}�b�v�B
Texture2D<float4> g_shadowMap : register(t5);		
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);
//�C���X�^���V���O�`��p
StructuredBuffer<float4x4> instanceMatrix : register(t100);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
	//�e�p�̐���
	float4x4 mLightView;	//���C�g�r���[�s��B
	float4x4 mLightProj;	//���C�g�v���W�F�N�V�����s��B
	int isShadowReciever;	//�V���h�E���V�[�o�[�t���O�B
};
cbuffer PSCb : register(b1) {
	float3 angle;
	float4 color;
	float3 pos;
};

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 WorldPos     : TEXCOORD1;
	float4 posInLVP		: TEXCOORD2;	//���C�g�r���[�v���W�F�N�V������Ԃł̍��W�B
	
};
/// <summary>
/// �V���h�E�}�b�v�p�̃s�N�Z���V�F�[�_�ւ̓��͍\���́B
/// </summary>
struct PSInput_ShadowMap {
	float4 Position 			: SV_POSITION;	//���W�B
};
/*!
 *@brief	�X�L���s����v�Z�B
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMaincreate(VSInputNmTxVcTangent In, float4x4 worldMat)
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(worldMat, In.Position);	
	psInput.WorldPos = pos;	
	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(ja.mLightView, pos);
		psInput.posInLVP = mul(ja.mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;

	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}
PSInput VSMainInstancing(VSInputNmTxVcTangent In, uint instanceID : SV_InstanceID)
{
	return VSMaincreate(In, instanceMatrix[instanceID]);
}
PSInput VSMain(VSInputNmTxVcTangent In)
{
	return VSMaincreate(In, mWorld);
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkincreate( VSInputNmTxWeights In ,float4x4 worldMat)
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;
	float4 pos =0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	}
	pos = mul(skinning, In.Position);
	pos = mul(worldMat, pos);
	float4x4 normal = 0;
	normal= mul(worldMat, skinning);
	psInput.Normal = normalize( mul(normal, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	psInput.WorldPos = pos;
	if (isShadowReciever == 1) {
		//�����āA���C�g�r���[�v���W�F�N�V������Ԃɕϊ��B
		psInput.posInLVP = mul(ja.mLightView, pos);
		psInput.posInLVP = mul(ja.mLightProj, psInput.posInLVP);
	}
	pos = mul(mView, pos);
	pos = mul(mProj, pos);

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}
PSInput VSMainSkinInstancing(VSInputNmTxWeights In, uint instanceID : SV_InstanceID)
{
	return VSMainSkincreate(In, instanceMatrix[instanceID]);
}
PSInput VSMainSkin(VSInputNmTxWeights In)
{
	return VSMainSkincreate(In, mWorld);
}
//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
    //�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = max(0.0f, dot(angle*-1.0f, In.Normal)) * color;
	float3 toEyeDir = normalize(pos - In.WorldPos);
	float3 na = reflect(-toEyeDir, In.Normal);
	//float3 na = -toEyeDir + 2.0f * dot(In.Normal, toEyeDir) * In.Normal;
	float n2 = max(0.0f, dot(na, -angle));
	float3 ka = pow(n2, 10.0f)*color.xyx;
//	lig = lig + ka;
	if (isShadowReciever == 1) {	//�V���h�E���V�[�o�[�B	//LVP��Ԃ��猩�����̍ł���O�̐[�x�l���V���h�E�}�b�v����擾����B
		float2 shadowMapUV = In.posInLVP.xy / In.posInLVP.w;
		shadowMapUV *= float2(0.5f, -0.5f);
		shadowMapUV += 0.5f;
		////�V���h�E�}�b�v�͈͓̔����ǂ����𔻒肷��B
		if (shadowMapUV.x < 1.0f
			&& shadowMapUV.x >0.0f
			&& shadowMapUV.y < 1.0f
			&& shadowMapUV.y > 0.0f
			) {
			///LVP��Ԃł̐[�x�l���v�Z�B
			//lig *= 0.0f;
			float zInLVP = In.posInLVP.z / In.posInLVP.w;
			//�V���h�E�}�b�v�ɏ������܂�Ă���[�x�l���擾�B
			float zInShadowMap = g_shadowMap.Sample(Sampler, shadowMapUV);
			if (zInLVP > zInShadowMap+0.001f) {
				//�e�������Ă���̂ŁA�����キ����
				lig *= 0.1f;
			}
		
		}
	}
    float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	finalColor.xyz = albedoColor.xyz *lig;
	finalColor.xyz += albedoColor.xyz*0.3;

	return finalColor;
}
/// <summary>
/// �V���h�E�}�b�v�����p�̒��_�V�F�[�_�[�B
/// </summary>
PSInput_ShadowMap VSMainShadowMap(VSInputNmTxVcTangent In, float4x4 worldMat)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4 pos = mul(worldMat, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
PSInput_ShadowMap VSMainShadow(VSInputNmTxVcTangent In)
{
	return VSMainShadowMap(In, mWorld);
}
PSInput_ShadowMap VSMainShadowInstancing(VSInputNmTxVcTangent In, uint instanceID : SV_InstanceID)
{
	return VSMainShadowMap(In, instanceMatrix[instanceID]);
}

PSInput_ShadowMap VSMain_skinShadowMap(VSInputNmTxWeights In, float4x4 worldMat)
{
	PSInput_ShadowMap psInput = (PSInput_ShadowMap)0;
	float4x4 skinning = 0;
	float4 pos = 0;
	{
		float w = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
			skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
			w += In.Weights[i];
		}
		//�Ō�̃{�[�����v�Z����B
		skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
		//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
		pos = mul(skinning, In.Position);
	}
	pos = mul(worldMat, pos);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}
PSInput_ShadowMap VSMainSkinShadow(VSInputNmTxWeights In)
{
	return VSMain_skinShadowMap(In, mWorld);
}
PSInput_ShadowMap VSMainSkinShadowInstancing(VSInputNmTxWeights In, uint instanceID : SV_InstanceID)
{
	return VSMain_skinShadowMap(In, instanceMatrix[instanceID]);
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
/// </summary>
float4 PSMain_ShadowMap(PSInput_ShadowMap In) : SV_Target0
{
	//�ˉe��Ԃł�Z�l��Ԃ��B
	return In.Position.z / In.Position.w;
}

