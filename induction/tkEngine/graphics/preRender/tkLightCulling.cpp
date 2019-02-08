/*!
 *@brief	���C�g�J�����O
 *@details
 * TBFR�̂��߂̓��I�����̃^�C���x�[�X�J�����O���s���B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/preRender/tkLightCulling.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CLightCulling::CLightCulling()
	{
	}
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	CLightCulling::~CLightCulling()
	{
	}
	/*!
	*@brief	�������B
	*/
	void CLightCulling::Init()
	{
		m_csLightCulling.Load("shader/LightCulling.fx", "CSMain", CShader::EnType::CS);
		//�J�����p�̒萔�o�b�t�@���쐬�B
		m_cameraParamCB.Create(NULL, sizeof(m_cameraParam));
	}
	/*!
	 *@brief	���C�g�J�����O�̎��s�B
	 */
	void CLightCulling::Render(CRenderContext& rc)
	{
		BeginGPUEvent(L"enRenderStep_LightCulling");
		rc.SetRenderStep(enRenderStep_LightCulling);
		CGraphicsEngine& ge = GraphicsEngine();
		rc.CSSetShader(m_csLightCulling);
		//�[�x�e�N�X�`����ݒ�B
		rc.CSSetShaderResource(0, GetGBufferSRV(enGBufferDepth));
		//�|�C���g���C�g�̃��X�g��ݒ�B
		rc.CSSetShaderResource(1, ge.GetLightManager().GetPointLightsSRV());
		//�o�͐��ݒ�B
		rc.CSSetUnorderedAccessView(0, ge.GetLightManager().GetPointLightsInTileUAV());

		//�J�����萔�o�b�t�@�̐ݒ�B
		CCamera& cam = MainCamera();
		m_cameraParam.screenParam.x = cam.GetNear();
		m_cameraParam.screenParam.y = cam.GetFar();
		m_cameraParam.screenParam.z = (float)ge.GetFrameBufferWidth();
		m_cameraParam.screenParam.w = (float)ge.GetFrameBufferHeight();
		m_cameraParam.mProj = cam.GetProjectionMatrix();
		m_cameraParam.mProjInv.Inverse(m_cameraParam.mProj);
		m_cameraParam.mViewRot.Inverse(cam.GetViewMatrix());
		m_cameraParam.mViewRot.m[3][0] = 0.0f;
		m_cameraParam.mViewRot.m[3][1] = 0.0f;
		m_cameraParam.mViewRot.m[3][2] = 0.0f;
		m_cameraParam.mViewRot.Transpose();
		m_cameraParam.numPointLight = ge.GetLightManager().GetNumPointLight();

		rc.UpdateSubresource(m_cameraParamCB, &m_cameraParam);
		rc.CSSetConstantBuffer(0, m_cameraParamCB);

		rc.Dispatch(ge.GetFrameBufferWidth() / TILE_WIDTH, ge.GetFrameBufferHeight() / TILE_WIDTH, 1);
		
		rc.CSUnsetUnorderedAccessView(0);
		rc.CSUnsetShaderResource(0);
		EndGPUEvent();
	}
}