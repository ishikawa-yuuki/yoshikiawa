/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/shadow/tkDirectionShadowMap.h"
#include "tkEngine/graphics/preRender/shadow/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	
	CDirectionShadowMap::CDirectionShadowMap()
	{
	}
	
	CDirectionShadowMap::~CDirectionShadowMap()
	{
	}
	
	bool CDirectionShadowMap::Init(const SShadowRenderConfig& config)
	{
		Release();
		if (config.isEnable == false) {
			return true;
		}
		m_lightHeight = config.lightHeight;
		m_isInited = config.isEnable;
		m_isEnable = true;

		m_softShadowLevel = config.softShadowLevel;

		m_shadowCbEntity.depthOffset[0] = config.depthOffset[0];
		m_shadowCbEntity.depthOffset[1] = config.depthOffset[1];
		m_shadowCbEntity.depthOffset[2] = config.depthOffset[2];
		
		int wh[][2] = {
			{ config.shadowMapWidth, config.shadowMapHeight},
			{ config.shadowMapWidth, config.shadowMapHeight >> 1},
			{ config.shadowMapWidth >> 1, config.shadowMapHeight >> 1},
		};
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			m_shadowMapRT[i].Create(
				wh[i][0], 
				wh[i][1], 
				1, 
				1,
				DXGI_FORMAT_R32_FLOAT,
				DXGI_FORMAT_D32_FLOAT,
				multiSampleDesc
			);
			m_shadowCbEntity.texOffset[i].x = 1.0f / wh[i][0];
			m_shadowCbEntity.texOffset[i].y = 1.0f / wh[i][1];
		}

		m_shadowCb.Create(&m_shadowCbEntity, sizeof(m_shadowCbEntity));

		//�V���h�E�}�b�v�T���v�����O�p�̃T���v�����쐬����B
		CD3D11_DEFAULT def;
		CD3D11_SAMPLER_DESC desc(def);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		desc.BorderColor[0] = 1.0f ;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		m_fetchShadowMapSampler.Create(desc);
		return true;
	}
	
	void CDirectionShadowMap::Release()
	{
		m_shadowCb.Release();
		for (auto& rt : m_shadowMapRT) {
			rt.Release();
		}
	}
	
	CVector3 CDirectionShadowMap::CalcLightPosition(float lightHeight, CVector3 viewFrustomCenterPosition)
	{
		//�v�Z���̏ڍׂ̓w�b�_�[�t�@�C���̊֐��R�����g���Q�Ƃ��Ă��������B
		auto alpha = (lightHeight - viewFrustomCenterPosition.y) / m_lightDirection.y;
		auto lightPos = viewFrustomCenterPosition + m_lightDirection * alpha;
		return lightPos;
	}
	void CDirectionShadowMap::Update()
	{
		if (IsEnable() == false) {
			return;
		}
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		auto cameraDir = MainCamera().GetForward();
		if (fabs(cameraDir.x) < FLT_EPSILON && fabsf(cameraDir.z) < FLT_EPSILON) {
			//�قڐ^����ނ��Ă���B
			return;
		}
		//���C�g�r���[�s��̉�]�������v�Z����B
		CVector3 lightViewForward = m_lightDirection;
		CVector3 lightViewUp;
		if (fabsf(lightViewForward.y) > 0.999f) {
			//�قڐ^��B
			lightViewUp.Cross(lightViewForward, CVector3::Right);
		}
		else {
			lightViewUp.Cross(lightViewForward, CVector3::Up);
		}
		lightViewUp.Normalize();
		CVector3 lgihtViewRight;
		lgihtViewRight.Cross(lightViewUp, lightViewForward);
		lgihtViewRight.Normalize();
		
		CMatrix lightViewRot;
		//���C�g�r���[�̉���ݒ肷��B
		lightViewRot.m[0][0] = lgihtViewRight.x;
		lightViewRot.m[0][1] = lgihtViewRight.y;
		lightViewRot.m[0][2] = lgihtViewRight.z;
		lightViewRot.m[0][3] = 0.0f;
		//���C�g�r���[�̏��ݒ肷��B
		lightViewRot.m[1][0] = lightViewUp.x;
		lightViewRot.m[1][1] = lightViewUp.y;
		lightViewRot.m[1][2] = lightViewUp.z;
		lightViewRot.m[1][3] = 0.0f;
		//���C�g�r���[�̑O��ݒ肷��B
		lightViewRot.m[2][0] = lightViewForward.x;
		lightViewRot.m[2][1] = lightViewForward.y;
		lightViewRot.m[2][2] = lightViewForward.z;
		lightViewRot.m[2][3] = 0.0f;

		float shadowAreaTbl[] = {
			m_lightHeight * 0.8f,
			m_lightHeight * 1.6f,
			m_lightHeight * 3.6f
		};

		//���C�g�r���[�̍������v�Z�B
		float lightHeight = MainCamera().GetTarget().y + m_lightHeight;
		
		SShadowCb shadowCB;
		float nearPlaneZ = 0.0f;
		float farPlaneZ ;
		CVector3 cameraUp;
		cameraUp.Cross(MainCamera().GetRight(), MainCamera().GetForward());
		//������𕪊�����悤�Ƀ��C�g�r���[�v���W�F�N�V�����s����v�Z����B
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			farPlaneZ = nearPlaneZ + shadowAreaTbl[i];
			CMatrix mLightView = CMatrix::Identity;
			float halfViewAngle = MainCamera().GetViewAngle() * 0.5f;
			//�������8���_�����C�g��Ԃɕϊ�����AABB�����߂āA���ˉe�̕��ƍ��������߂�B
			float w, h;
			float far_z = -1.0f;
			CVector3 v[8];
			{
				float t = tan(halfViewAngle);
				CVector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperFar = cameraUp * t * farPlaneZ;
				t *= MainCamera().GetAspect();
				//�ߕ��ʂ̒������W���v�Z�B
				auto nearPlaneCenterPos = MainCamera().GetPosition() + cameraDir * nearPlaneZ;
				v[0] = nearPlaneCenterPos + MainCamera().GetRight() * t * nearPlaneZ + toUpperNear;
				v[1] = v[0] - toUpperNear * 2.0f;

				v[2] = nearPlaneCenterPos + MainCamera().GetRight() * -t * nearPlaneZ + toUpperNear;
				v[3] = v[2] - toUpperNear * 2.0f;

				//�����ʂ̒������W���v�Z�B
				auto farPlaneCneterPos = MainCamera().GetPosition() + cameraDir * farPlaneZ;
				v[4] = farPlaneCneterPos + MainCamera().GetRight() * t * farPlaneZ + toUpperFar;
				v[5] = v[4] - toUpperFar * 2.0f;
				v[6] = farPlaneCneterPos + MainCamera().GetRight() * -t * farPlaneZ + toUpperFar;
				v[7] = v[6] - toUpperFar * 2.0f;

				//���C�g�s����쐬�B
				auto viewFrustumCenterPosition = (nearPlaneCenterPos + farPlaneCneterPos) * 0.5f;
				auto lightPos = CalcLightPosition(lightHeight, viewFrustumCenterPosition);
				
				mLightView = lightViewRot;
				
				mLightView.m[3][0] = lightPos.x;
				mLightView.m[3][1] = lightPos.y;
				mLightView.m[3][2] = lightPos.z;
				mLightView.m[3][3] = 1.0f;
				mLightView.Inverse(mLightView);	//���C�g�r���[�����B
				//��������\������8���_���v�Z�ł����̂ŁA���C�g��Ԃɍ��W�ϊ����āAAABB�����߂�B
				CVector3 vMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
				CVector3 vMin = { FLT_MAX, FLT_MAX, FLT_MAX };
				for (auto& vInLight : v) {
					mLightView.Apply(vInLight);
					vMax.Max(vInLight);
					vMin.Min(vInLight);
					
				}
				w = vMax.x - vMin.x;
				h = vMax.y - vMin.y;
				far_z =  vMax.z ;
			}
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				w,
				h,
				far_z/100.0f,
				far_z 
			);
			m_LVPMatrix[i] = mLightView * proj;
			m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
			m_shadowCbEntity.shadowAreaDepthInViewSpace[i] = farPlaneZ * 0.8f;	//�L���L�����ƕςȋ��E���������Ă����̂ŁA������ƃG���A�����߂�B
			nearPlaneZ = farPlaneZ;
		}
	}
	void CDirectionShadowMap::RenderToShadowMapImp(CRenderContext& rc)
	{
		rc.SetRenderStep(enRenderStep_RenderToShadowMap);
		if (IsEnable() == false) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_CDirectionShadowMap::RenderToShadowMap");
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSUnsetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i);
		}

		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			BeginGPUEvent(L"Render 3DModel");

			rc.OMSetRenderTarget(m_shadowMapRT[i]);

			rc.RSSetViewport(
				0.0f, 0.0f, 
				(float)m_shadowMapRT[i].GetWidth(),
				(float)m_shadowMapRT[i].GetHeight()
			);
			float ClearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
			rc.ClearRenderTargetView(0, ClearColor);

			for (auto& caster : m_shadowCaster) {
				caster->Render(rc, m_LVPMatrix[i]);
			}
			EndGPUEvent();

		}
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//@todo �����_�����O�X�e�[�g�̓��X�g�A������@�ɕύX����B
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
		EndGPUEvent();
	}
	void CDirectionShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_shadowCb, &m_shadowCbEntity);
		rc.PSSetConstantBuffer(enSkinModelCBReg_Shadow, m_shadowCb);
		//�e�N�X�`����]���B
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSSetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i, m_shadowMapRT[i].GetRenderTargetSRV());
		}
		D3D11_SAMPLER_DESC desc;
		m_fetchShadowMapSampler.GetBody()->GetDesc(&desc);
		rc.PSSetSampler(3, m_fetchShadowMapSampler);
	}
}