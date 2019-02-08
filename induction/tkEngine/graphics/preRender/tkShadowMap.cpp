/*!
 * @brief	�V���h�E�}�b�v�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkShadowMap.h"
#include "tkEngine/graphics/preRender/tkShadowCaster.h"
#include "tkEngine/graphics/tkSkinModelShaderConst.h"

namespace tkEngine{
	
	CShadowMap::CShadowMap()
	{
	}
	
	CShadowMap::~CShadowMap()
	{
	}
	
	bool CShadowMap::Init(const SShadowRenderConfig& config)
	{
		Release();
		m_lightHeight = config.lightHeight;
		m_isEnable = config.isEnable;
		m_far = m_lightHeight * 2.0f;
		m_near = m_lightHeight * 0.2f;
		if (config.farPlane > 0.0f) {
			m_far = config.farPlane;
		}
		if (config.nearPlane > 0.0f) {
			m_near = config.nearPlane;
		}
		m_softShadowLevel = config.softShadowLevel;

		m_shadowCbEntity.depthOffset[0] = config.depthOffset[0];
		m_shadowCbEntity.depthOffset[1] = config.depthOffset[1];
		m_shadowCbEntity.depthOffset[2] = config.depthOffset[2];
		if (m_isEnable == false) {
			return true;
		}
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
		return true;
	}
	
	void CShadowMap::Release()
	{
		m_shadowCb.Release();
		for (auto& rt : m_shadowMapRT) {
			rt.Release();
		}
	}
	
	void CShadowMap::Entry(IShadowCaster* caster)
	{
		if (!m_isEnable) {
			return;
		}
		m_shadowCaster.push_back(caster);
	}
	
	void CShadowMap::Update()
	{
		if (!m_isEnable) {
			return;
		}
		//�V�[���������_�����O�g�p�Ƃ��Ă���J�������g���āA���C�g�J�����̉�]�����߂�B
		CVector3 cameraDirXZ = MainCamera().GetForward();
		if (fabs(cameraDirXZ.x) < FLT_EPSILON && fabsf(cameraDirXZ.z) < FLT_EPSILON) {
			//�قڐ^����ނ��Ă���B
			return;
		}
		/*cameraDirXZ.y = 0.0f;
		cameraDirXZ.Normalize();*/
		//���C�g�r���[�s��̉�]���������v�Z����B
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
			m_lightHeight * 0.4f,
			m_lightHeight * 0.8f,
			m_lightHeight * 1.6f
		};

		//���C�g�r���[�̃^�[�Q�b�g���v�Z�B
		CVector3 lightTarget;
		lightTarget = MainCamera().GetPosition();
		lightTarget.y = MainCamera().GetTarget().y;
		lightTarget += cameraDirXZ ;
		CVector3 lightPos = lightTarget + m_lightDirection * -m_lightHeight;
		
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
			
			CVector3 v[8];
			{
				float t = tan(halfViewAngle);
				CVector3 toUpperNear, toUpperFar;
				toUpperNear = cameraUp * t * nearPlaneZ;
				toUpperFar = cameraUp * t * farPlaneZ;
				t *= MainCamera().GetAspect();
				//�ߕ��ʂ̒������W���v�Z�B
				CVector3 vWk = MainCamera().GetPosition() + cameraDirXZ * nearPlaneZ;
				lightPos = vWk;
				v[0] = vWk + MainCamera().GetRight() * t * nearPlaneZ + toUpperNear;
				v[1] = v[0] - toUpperNear * 2.0f;

				v[2] = vWk + MainCamera().GetRight() * -t * nearPlaneZ + toUpperNear;
				v[3] = v[2] - toUpperNear * 2.0f;

				//�����ʂ̒������W���v�Z�B
				vWk = MainCamera().GetPosition() + cameraDirXZ * farPlaneZ;
				lightPos += vWk;
				v[4] = vWk + MainCamera().GetRight() * t * farPlaneZ + toUpperFar;
				v[5] = v[4] - toUpperFar * 2.0f;
				v[6] = vWk + MainCamera().GetRight() * -t * farPlaneZ + toUpperFar;
				v[7] = v[6] - toUpperFar * 2.0f;

				//���C�g�s����쐬�B
				lightPos *= 0.5f;
				lightPos += m_lightDirection * -m_lightHeight;
				
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
			}
			CMatrix proj;
			proj.MakeOrthoProjectionMatrix(
				w,	//���傢���点��B
				h,
				m_near,
				m_far
			);
			m_LVPMatrix[i] = mLightView * proj;
			m_shadowCbEntity.mLVP[i] = m_LVPMatrix[i];
			
			nearPlaneZ = farPlaneZ;
		}
	}
	/*!
	*@brief	�V���h�E�}�b�v�֏������݁B
	*/
	void CShadowMap::RenderToShadowMap(CRenderContext& rc)
	{
		rc.SetRenderStep(enRenderStep_RenderToShadowMap);
		if (!m_isEnable) {
			return;
		}
		BeginGPUEvent(L"enRenderStep_RenderToShadowMap");
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSUnsetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i);
		}

		CRenderTarget* oldRenderTargets[MRT_MAX];
		unsigned int numRenderTargetViews;
		rc.OMGetRenderTargets(numRenderTargetViews, oldRenderTargets);
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			BeginGPUEvent(L"Render 3DModel");
			CRenderTarget* renderTargets[] = {
				&m_shadowMapRT[i]
			};

			rc.OMSetRenderTargets(1, renderTargets);
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
		m_shadowCaster.clear();
		//�����_�����O�^�[�Q�b�g�������߂��B
		rc.OMSetRenderTargets(numRenderTargetViews, oldRenderTargets);
		//@todo �����_�����O�X�e�[�g�̓��X�g�A������@�ɕύX����B
		rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
		EndGPUEvent();
	}
	/*!
	*@brief	�e�𗎂Ƃ����߂̃p�����[�^��GPU�ɓ]������B
	*/
	void CShadowMap::SendShadowReceiveParamToGPU(CRenderContext& rc)
	{
		rc.UpdateSubresource(m_shadowCb, &m_shadowCbEntity);
		rc.PSSetConstantBuffer(enSkinModelCBReg_Shadow, m_shadowCb);
		//�e�N�X�`����]���B
		for (int i = 0; i < NUM_SHADOW_MAP; i++) {
			rc.PSSetShaderResource(enSkinModelSRVReg_ShadowMap_0 + i, m_shadowMapRT[i].GetRenderTargetSRV());
		}
	}
}