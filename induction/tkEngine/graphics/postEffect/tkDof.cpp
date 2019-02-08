/// <summary>
/// DOF(��ʊE�[�x
/// </summary>
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkDof.h"
#include "tkEngine/graphics/tkPresetRenderState.h"
#include "tkEngine/graphics/tkPresetSamplerState.h"

namespace tkEngine {
	CDof::CDof()
	{
	}
	CDof::~CDof()
	{
		Release();
	}
	void CDof::Release()
	{
		m_createCocParam.calcCocAndColorRt.Release();
		m_createCocParam.vs.Release();
		m_createCocParam.ps.Release();
		m_createCocParam.cb.Release();
		if (m_createCocParam.blendState != nullptr) {
			m_createCocParam.blendState->Release();
		}

		m_createBokeTextureParam.vs.Release();
		m_createBokeTextureParam.ps.Release();
		m_createBokeTextureParam.cb.Release();
	}
	void CDof::Init(const SGraphicsConfig& config)
	{
		if (config.dofConfig.isEnable==false) {
			return;
		}
		m_isEnable = config.dofConfig.isEnable;
		m_isEnableGlobal = config.dofConfig.isEnable;
		//����B
		Release();

		//�V�F�[�_�[���������B
		InitShaders();
		//�����_�����O�^�[�Q�b�g���������B
		InitRenderTargets();
		//�萔�o�b�t�@�̏������B
		InitConstantBuffers();
	}
	void CDof::InitConstantBuffers()
	{
		m_createCocParam.cb.Create(nullptr, sizeof(SCreateCocParamCB));
		m_createBokeTextureParam.cb.Create(nullptr, sizeof(SCreateBokeTextureCB));
		m_finalParam.gpuCB.Create(nullptr, sizeof(SFinalCB));
	}

	void CDof::InitShaders()
	{
		m_createCocParam.vs.Load(
			"shader/dof/dof_CreateCoCTexture.fx",
			"VSMain",
			CShader::EnType::VS);
		m_createCocParam.ps.Load(
			"shader/dof/dof_CreateCoCTexture.fx",
			"PSMain",
			CShader::EnType::PS);

		m_finalParam.vs.Load(
			"shader/dof/dof_Final.fx",
			"VSMain",
			CShader::EnType::VS);
		m_finalParam.ps.Load(
			"shader/dof/dof_Final.fx",
			"PSMain",
			CShader::EnType::PS);
	}
	void CDof::InitRenderTargets()
	{
		auto& ge = GraphicsEngine();
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;
		//CoC�v�Z�p�̃����_�����O�^�[�Q�b�g���쐬����B
		m_createCocParam.calcCocAndColorRt.Create(
			ge.GetFrameBufferWidth(),
			ge.GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R16G16B16A16_FLOAT,
			DXGI_FORMAT_UNKNOWN,
			multiSampleDesc
		);
		m_createBokeTextureParam.blur.Init(
			m_createCocParam.calcCocAndColorRt.GetRenderTargetSRV(),
			1.5f
		);
	}
	void CDof::InitBlendStates()
	{
		auto d3dDevice = GraphicsEngine().GetD3DDevice();
		CD3D11_DEFAULT def;
		CD3D11_BLEND_DESC desc(def);

		//CoC���v�Z���郌���_�����O�^�[�Q�b�g�̓A���t�@�u�����f�B���O�̓I�t�B
		desc.RenderTarget[0].BlendEnable = false;
		//Dof�}�X�N���쐬���郌���_�����O�^�[�Q�b�g���A���t�@�u�����f�B���O�̓I�t�B
		desc.RenderTarget[1].BlendEnable = false;

		d3dDevice->CreateBlendState(&desc, &m_createCocParam.blendState);
	}
	void CDof::Update()
	{
	}
	void CDof::CreateCoCTexture(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::CreateCoCTexture");
		//�V�[�����������܂�Ă��郌���_�����O�^�[�Q�b�g���擾����B
		auto& sceneRt = postEffect->GetFinalRenderTarget();
		auto& calcCocAndColorRt = m_createCocParam.calcCocAndColorRt;
		auto& vs = m_createCocParam.vs;
		auto& ps = m_createCocParam.ps;
		auto& cb = m_createCocParam.cb;
		auto& depthTextureSrv = ge.GetGBufferRender().GetRenderTarget(enGBufferDepth).GetRenderTargetSRV();
		//�����_�����O�^�[�Q�b�g��؂�ւ���B

		CChangeRenderTarget chgRt(rc, calcCocAndColorRt);
		//�萔�o�b�t�@�̍X�V�B
		SCreateCocParamCB cbParam;
		cbParam.dofRange.x = m_nearStartDistance;
		cbParam.dofRange.y = m_nearEndDistance;
		cbParam.dofRange.z = m_farStartDistance;
		cbParam.dofRange.w = m_farEndDistance;

		//���C������������VRAM�Ƀf�[�^��]���B
		rc.UpdateSubresource(cb, &cbParam);
		//�萔�o�b�t�@�����W�X�^b0�ɐݒ肷��B
		rc.VSSetConstantBuffer(0, cb);
		rc.PSSetConstantBuffer(0, cb);
		rc.PSSetShaderResource(0, sceneRt.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, depthTextureSrv);
		rc.VSSetShader(vs);
		rc.PSSetShader(ps);

		rc.PSSetSampler(0, *CPresetSamplerState::clamp_clamp_clamp_point);
		rc.OMSetBlendState(m_createCocParam.blendState);
		
		postEffect->DrawFullScreenQuad(rc);

		//�����_�����O�^�[�Q�b�g���O���B
		rc.OMSetRenderTargets(2, nullptr);

		ge.EndGPUEvent();

	}
	void CDof::CreateBokeTexture(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		auto& depthTextureSrv = ge.GetGBufferRender().GetRenderTarget(enGBufferDepth).GetRenderTargetSRV();

		ge.BeginGPUEvent(L"enRenderStep_Dof::CreateBokeTexture");

		//�{�P�摜�̐���
		rc.PSSetSampler(0, *CPresetSamplerState::clamp_clamp_clamp_linear);
		rc.PSSetShaderResource(1, depthTextureSrv);
		m_createBokeTextureParam.blur.Execute(rc);
		

		ge.EndGPUEvent();
	}
	void CDof::Final(CRenderContext& rc, CPostEffect* postEffect)
	{
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof::Final");

		//�����_�����O�^�[�Q�b�g�؂�ւ��B
		CChangeRenderTarget chgRt(rc, postEffect->GetFinalRenderTarget());

		rc.VSSetShader(m_finalParam.vs);
		rc.PSSetShader(m_finalParam.ps);
		rc.PSSetShaderResource(0, m_createCocParam.calcCocAndColorRt.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, m_createBokeTextureParam.blur.GetHexaBlurResultSRV());
	
		rc.OMSetBlendState(AlphaBlendState::disable);
		rc.PSSetSampler(0, *CPresetSamplerState::clamp_clamp_clamp_linear);
		rc.PSSetSampler(1, *CPresetSamplerState::clamp_clamp_clamp_point);
		rc.UpdateSubresource(m_finalParam.gpuCB, &m_finalParam.cpuCB);
		rc.PSSetConstantBuffer(0, m_finalParam.gpuCB);

		postEffect->DrawFullScreenQuad(rc);

		ge.EndGPUEvent();
	}
	void CDof::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		if (m_isEnable == false || m_isEnableGlobal == false) {
			return;
		}
		
		auto& ge = GraphicsEngine();
		ge.BeginGPUEvent(L"enRenderStep_Dof");

		//�����_�����O�X�e�[�g��ޔ�����B
		rc.PushRenderState();

		rc.SetRenderStep(enRenderStep_Dof);

		CreateCoCTexture(rc, postEffect);

		CreateBokeTexture(rc, postEffect);

		Final(rc, postEffect);

		//�����_�����O�X�e�[�g��߂��B
		rc.PopRenderState(true);

		ge.EndGPUEvent();
	}
}