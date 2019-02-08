/*!
 *@brief	�|�X�g�G�t�F�N�g�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"
#include "tkEngine/graphics/tkHexaBlur.h"

namespace tkEngine{
	namespace {
		struct SSimpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	CPostEffect::CPostEffect()
	{
	}
	CPostEffect::~CPostEffect()
	{
		Release();
	}
	void CPostEffect::Release()
	{
		m_fullscreenQuad.Release();
		m_dof.Release();
		m_fxaa.Release();
		m_bloom.Release();
		m_dithering.Release();
	}
	void CPostEffect::Create( const SGraphicsConfig& config )
	{
		Release();
		m_fxaa.Init(config);
		m_tonemap.Init(config);
		m_bloom.Init(config);
		m_dithering.Init(config);
		m_ssr.Init(config);
		m_dof.Init(config);
		InitFullScreenQuadPrimitive();
		InitFinalRenderTarget();
	}
	void CPostEffect::Render(CRenderContext& rc)
	{
		//���C�������_�����O�^�[�Q�b�g�̓��e�����]���u�B
		GraphicsEngine().GetMainRenderTarget().ResovleMSAATexture(rc);
		
		m_tonemap.Render(rc, this);

		//�G�t�F�N�g��`��
		GraphicsEngine().GetEffectEngine().Render(rc, this);

		//���C�������_�����O�^�[�Q�b�g�̓��e���ŏI�����p�̃����_�����O�^�[�Q�b�g�ɕ`��B
		rc.ResolveSubresource(
			GetFinalRenderTarget().GetRenderTarget(),
			0,
			GraphicsEngine().GetMainRenderTarget().GetRenderTarget(),
			0,
			GetFinalRenderTarget().GetRenderTargetTextureFormat()
		);
		
		m_ssr.Render(rc, this); 
		m_bloom.Render(rc, this);
		m_dof.Render(rc, this);
		m_fxaa.Render(rc, this);
		m_dithering.Render(rc, this);
		//
		GraphicsEngine().EndPostEffect(rc);
	}
	void CPostEffect::InitFullScreenQuadPrimitive()
	{
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 1.0f),
			},
			{
				CVector4(1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}

		};
		short indices[] = { 0,1,2,3 };
		
		m_fullscreenQuad.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			CIndexBuffer::enIndexType_16,
			indices
		);
	}
	void CPostEffect::DrawFullScreenQuad(CRenderContext& rc)
	{
		m_fullscreenQuad.Draw(rc);
	}
	void CPostEffect::InitFinalRenderTarget()
	{
		DXGI_SAMPLE_DESC sampleDesc;
		//�|�X�g�Ȃ̂�MSAA�͂Ȃ��B
		ZeroMemory(&sampleDesc, sizeof(sampleDesc));
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;
		CRenderTarget& mainRt = GraphicsEngine().GetMainRenderTarget();
		m_finalRenderTarget[0].Create(
			mainRt.GetWidth(),
			mainRt.GetHeight(),
			1,
			1,
			mainRt.GetRenderTargetTextureFormat(),
			DXGI_FORMAT_UNKNOWN,
			sampleDesc
		);
		m_finalRenderTarget[1].Create(
			mainRt.GetWidth(),
			mainRt.GetHeight(),
			1,
			1,
			mainRt.GetRenderTargetTextureFormat(),
			DXGI_FORMAT_UNKNOWN,
			sampleDesc
		);
	}
}