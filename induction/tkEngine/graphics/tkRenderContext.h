/*!
* @brief	�����_�����O�R���e�L�X�g
*/

#pragma once


#include "tkEngine/graphics/tkShader.h"
#include "tkEngine/graphics/GPUBuffer/tkVertexBuffer.h"
#include "tkEngine/graphics/GPUBuffer/tkIndexBuffer.h"
#include "tkEngine/graphics/GPUBuffer/tkConstantBuffer.h"
#include "tkEngine/graphics/GPUBuffer/tkStructuredBuffer.h"
#include "tkEngine/graphics/GPUView/tkShaderResourceView.h"
#include "tkEngine/graphics/GPUView/tkUnorderedAccessView.h"
#include "tkEngine/graphics/tkSamplerState.h"
#include "tkEngine/graphics/tkRenderTarget.h"

namespace tkEngine {
	class CVertexBuffer;
	class CRenderTarget;
	/*!
	* @brief	�����_�����O�X�e�b�v�B
	*/
	enum EnRenderStep {
		enRenderStep_LightCulling,				//!<���C�g�J�����O�B
		enRenderStep_ZPrepass,					//!<ZPrepass�B
		enRenderStep_RenderToShadowMap,			//!<�V���h�E�}�b�v�ւ̏������݃X�e�b�v�B
		enRenderStep_RenderGBuffer,				//!<G-Buffer�̍쐬�X�e�b�v�B
		enRenderStep_DefferdShading,			//!<�f�B�t�@�[�h�V�F�[�f�B���O�B
		enRenderStep_ForwardPreRender,			//!<�t�H���[�h�v�������_�����O�B(����ȕ\�����s�������I�u�W�F�N�g�͂����ŕ`���B)
		enRenderStep_ForwardRender,				//!<�t�H���[�h�����_�����O�B(����ȕ\�����s�������I�u�W�F�N�g�͂����ŕ`���B)
		enRenderStep_RenderTransObject,			//!<�������I�u�W�F�N�g�������_�����O�B
		enRenderStep_RenderEffect,				//!<�G�t�F�N�g���V�[���ɕ`��B
		enRenderStep_ScreenSpaceReflection,		//!<SSR
		enRenderStep_Bloom,						//!<�u���[���B
		enRenderStep_Toonmap,					//!<�g�[���}�b�v�B
		enRenderStep_AntiAlias,					//!<�A���`�G�C���A�X�B
		enRenderStep_Dof,						//!<DOF�B
		enRenderStep_Render2DToScene,			//!<2D���V�[���ɕ`��B
	};
	class CRenderContext : Noncopyable {
	public:

		CRenderContext() {}
		~CRenderContext() {}
		/*!
		* @brief	�������B
		*@param[in]	pD3DDeviceContext	D3D�f�o�C�X�R���e�L�X�g�B�J���͌Ăяo�����Ƃōs���Ă��������B
		*/
		void Init(ID3D11DeviceContext* pD3DDeviceContext, ID3D11DeviceContext* pD3DDeferredDeviceContext);
		/// <summary>
		/// ���݂̃����_�����O�^�[�Q�b�g���X�^�b�N�Ƀv�b�V���B
		/// </summary>
		void PushRenderTargets()
		{
			SRenderTarget renderTarget;
			OMGetRenderTargets(renderTarget.numRenderTargetViews, renderTarget.renderTargets);
			m_renderTargetStack.push(renderTarget);
		}
		/// <summary>
		/// �X�^�b�N���烌���_�����O�^�[�Q�b�g���|�b�v�B
		/// </summary>
		/// <param name="isApplyRenderState">
		/// �|�b�v���������_�����O�^�[�Q�b�g�������_�����O�p�C�v���C���ɐݒ肷�邩�ǂ����̃t���O�B
		/// </param>
		void PopRenderTargets(bool isSetRenderStateToRenderPipeline)
		{
			auto rt = m_renderTargetStack.top();
			m_renderTargetStack.pop();
			OMSetRenderTargets(rt.numRenderTargetViews, rt.renderTargets);
			if (rt.renderTargets[0] != nullptr) {
				RSSetViewport(
					0.0f, 0.0f, (float)rt.renderTargets[0]->GetWidth(), (float)rt.renderTargets[0]->GetHeight());
			}
		}
		/// <summary>
		/// ���݂̃����_�����O�X�e�[�g���X�^�b�N�Ƀv�b�V���B
		/// </summary>
		void PushRenderState()
		{
			m_renderStateStack.push(m_currentRenderState);
		}
		/// <summary>
		/// �X�^�b�N�ɑޔ����������_�����O�X�e�[�g���|�b�v�B
		/// </summary>
		/// <param name="isApplyRenderState">
		/// �|�b�v���������_�����O�X�e�[�g�������_�����O�p�C�v���C���ɐݒ肷�邩�ǂ����̃t���O�B
		/// </param>
		void PopRenderState(bool isSetRenderStateToRenderPipeline)
		{
			m_currentRenderState = m_renderStateStack.top();
			m_renderStateStack.pop();
			if (isSetRenderStateToRenderPipeline == true) {
				m_pD3DDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
				m_pD3DDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
				m_pD3DDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
			}
		}
		/*!
		* @brief	Blend�X�e�[�g��ݒ肷��B
		* @details
		*  ID3D11DeviceContext::OMSetBlendState�Ɠ����B
		*/
		void OMSetBlendState(ID3D11BlendState *pBlendState)
		{
			m_currentRenderState.blendState = pBlendState;
			m_pD3DDeviceContext->OMSetBlendState(pBlendState, 0, 0xFFFFFFFF);
		}
		/*!
		*@brief	���݂�Blend�X�e�[�g���擾����B
		*/
		ID3D11BlendState* GetBlendState()
		{
			return m_currentRenderState.blendState;
		}
		/*!
		* @brief	DepthStencil�X�e�[�g��ݒ肷��B
		* @details
		*  ID3D11DeviceContext::OMSetDepthStencilState�Ɠ����B
		*/
		void OMSetDepthStencilState(ID3D11DepthStencilState *pDepthStencilState)
		{
			m_pD3DDeviceContext->OMSetDepthStencilState(pDepthStencilState, 0);
			m_currentRenderState.depthStencilState = pDepthStencilState;
		}
		/*!
		* @brief	DepthStencil�X�e�[�g���擾����B
		*/
		ID3D11DepthStencilState* GetDepthStencilState() const
		{
			return m_currentRenderState.depthStencilState;
		}
		/*!
		* @brief	�����_�����O�^�[�Q�b�g�r���[��ݒ�B
		* @details
		*  ID3D11DeviceContext::OMSetRenderTargets�Ɠ����B
		*@param[in]	NumViews		�o�C���h���郌���_�����O�^�[�Q�b�g�̐��B
		*@param[in]	renderTarget	�o�C���h���郌���_�����O�^�[�Q�b�g�̔z��ւ̃|�C���^�B
		*/
		void OMSetRenderTargets(unsigned int NumViews, CRenderTarget* renderTarget[]);
		void OMSetRenderTargets(unsigned int NumViews, ID3D11RenderTargetView *const *ppRenderTargetViews, ID3D11DepthStencilView *pDepthStencilView)
		{
			m_pD3DDeviceContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
			m_numRenderTargetView = NumViews;
		}
		/*!
		* @brief	���݃o�C���h����Ă��郌���_�����O�^�[�Q�b�g�r���[���擾�B
		*@param[out]	numViews		�o�C���h����Ă��郌���_�����O�^�[�Q�b�g�̐��B
		*@param[out]	renderTarget	�o�C���h���郌���_�����O�^�[�Q�b�g�̔z��ւ̃|�C���^�B
		*/
		void OMGetRenderTargets(unsigned int& numViews, CRenderTarget* renderTargets[MRT_MAX])
		{
			memcpy(renderTargets, m_renderTargetViews, sizeof(CRenderTarget*)*m_numRenderTargetView);
			numViews = m_numRenderTargetView;
		}
		/*!
		* @brief	�r���[�|�[�g��ݒ�B
		*@param[in]	topLeftX	�r���[�|�[�g�̍����X���W�B
		*@param[in]	topLeftY	�r���[�|�[�g�̍����Y���W�B
		*@param[in]	width		�r���[�|�[�g�̕��B
		*@param[in]	height		�r���[�|�[�g�̍����B
		*/
		void RSSetViewport(float topLeftX, float topLeftY, float width, float height)
		{
			m_viewport.Width = width;
			m_viewport.Height = height;
			m_viewport.TopLeftX = topLeftX;
			m_viewport.TopLeftY = topLeftY;
			m_viewport.MinDepth = 0.0f;
			m_viewport.MaxDepth = 1.0f;
			m_pD3DDeviceContext->RSSetViewports(1, &m_viewport);
		}
		/*!
		* @brief	���X�^���C�U�̃X�e�[�g��ݒ�B
		*/
		void RSSetState(ID3D11RasterizerState *pRasterizerState)
		{
			m_currentRenderState.rasterrizerState = pRasterizerState;
			m_pD3DDeviceContext->RSSetState(pRasterizerState);	
		}
		/*!
		*@brief	���݂̃��X�^���C�U�X�e�[�g���擾�B
		*/
		ID3D11RasterizerState* GetRSState() const
		{
			return m_currentRenderState.rasterrizerState;
		}
		/*!
		* @brief	�����_�����O�^�[�Q�b�g���N���A�B
		*@param[in]	rtNo	�����_�����O�^�[�Q�b�g�̔ԍ��B
		*@param[in]	clearColor	�N���A�J���[�B
		*@param[in]	isClearDepthStencil	�f�v�X�X�e���V���o�b�t�@���N���A����H
		*/
		void ClearRenderTargetView(unsigned int rtNo, float* clearColor, bool isClearDepthStencil = true)
		{
			if (rtNo < m_numRenderTargetView
				&& m_renderTargetViews != nullptr) {
				m_pD3DDeviceContext->ClearRenderTargetView(m_renderTargetViews[rtNo]->GetRenderTargetView(), clearColor);
				if (m_renderTargetViews[0]->GetDepthStencilView() != nullptr && isClearDepthStencil) {
					m_pD3DDeviceContext->ClearDepthStencilView(m_renderTargetViews[0]->GetDepthStencilView(), D3D11_CLEAR_DEPTH, 1.0f, 0);
				}
			}
		}
		/*!
		* @brief	���_�o�b�t�@��ݒ�B
		*/
		void IASetVertexBuffer(CVertexBuffer& vertexBuffer)
		{
			UINT offset = 0;
			UINT stride = vertexBuffer.GetStride();
			m_pD3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer.GetBody(), &stride, &offset);
		}
		/*!
		* @brief	�C���f�b�N�X�o�b�t�@��ݒ�
		*/
		void IASetIndexBuffer(CIndexBuffer& indexBuffer)
		{
			CIndexBuffer::EnIndexType type = indexBuffer.GetIndexType();
			m_pD3DDeviceContext->IASetIndexBuffer(
				indexBuffer.GetBody(),
				type == CIndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
				0
			);
		}
		/*!
		* @brief	�v���~�e�B�u�̃g�|���W�[��ݒ�B
		*@param[in]	topology	�g�|���W�[�B
		*/
		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			m_pD3DDeviceContext->IASetPrimitiveTopology(topology);
		}
		/*!
		* @brief	VS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	cb			�萔�o�b�t�@�B
		*/
		void VSSetConstantBuffer(
			UINT slotNo,
			CConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*!
		* @brief	VS�X�e�[�W��SRV��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	srv			SRV�B
		*/
		void VSSetShaderResource(int slotNo, CShaderResourceView& srv)
		{
			m_pD3DDeviceContext->VSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/*!
		* @brief	VS�X�e�[�W��SRV���O���B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	srv			SRV�B
		*/
		void VSUnsetShaderResource(int slotNo)
		{
			ID3D11ShaderResourceView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->VSSetShaderResources(slotNo, 1, view);
		}
		/*!
		* @brief	PS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	cb			�萔�o�b�t�@�B
		*/
		void PSSetConstantBuffer(
			UINT slotNo,
			CConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*!
		* @brief	PS�X�e�[�W��SRV��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	srv			SRV�B
		*/
		void PSSetShaderResource(int slotNo, CShaderResourceView& srv)
		{
			m_pD3DDeviceContext->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		/*!
		* @brief	PS�X�e�[�W��SRV���O���B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	srv			SRV�B
		*/
		void PSUnsetShaderResource(int slotNo)
		{
			ID3D11ShaderResourceView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->PSSetShaderResources(slotNo, 1, view);
		}
		/*!
		* @brief	PS�X�e�[�W�ɃT���v���X�e�[�g��ݒ�B
		*@param[in]	slotNo			�X���b�g�ԍ��B
		*@param[in]	samplerState	�T���v���X�e�[�g�B
		*/
		void PSSetSampler(int slotNo, CSamplerState& samplerState)
		{
			m_pD3DDeviceContext->PSSetSamplers(slotNo, 1, &samplerState.GetBody());
		}
		/*!
		* @brief	���_�V�F�[�_�[��ݒ�B
		*@param[in]	shader		���_�V�F�[�_�[�B
		*/
		void VSSetShader(CShader& shader)
		{
			IASetInputLayout(shader.GetInputLayout());
			m_pD3DDeviceContext->VSSetShader((ID3D11VertexShader*)shader.GetBody(), NULL, 0);
		}
		/*!
		* @brief	�s�N�Z���V�F�[�_�[��ݒ�B
		*@param[in]	shader		���_�V�F�[�_�[�B
		*/
		void PSSetShader(CShader& shader)
		{
			m_pD3DDeviceContext->PSSetShader((ID3D11PixelShader*)shader.GetBody(), NULL, 0);
		}
		/*!
		* @brief	�R���s���[�g�V�F�[�_�[��ݒ�B
		*@param[in]	shader		�R���s���[�g�V�F�[�_�[�B
		*/
		void CSSetShader(CShader& shader)
		{
			m_pD3DDeviceContext->CSSetShader((ID3D11ComputeShader*)shader.GetBody(), NULL, 0);
		}
		/*!
		* @brief	CS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ��B
		*@param[in]	cb			�萔�o�b�t�@�B
		*/
		void CSSetConstantBuffer(
			UINT slotNo,
			CConstantBuffer& cb
		)
		{
			m_pD3DDeviceContext->CSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}
		/*!
		* @brief	�R���s���[�g�V�F�[�_�[��SRV��ݒ�B�B
		*@param[in]	slotNo		�X���b�g�ԍ�
		*@param[in]	srv			�V�F�[�_�[���\�[�X�r���[�B
		*/
		void CSSetShaderResource(int slotNo, CShaderResourceView& srv)
		{
			m_pD3DDeviceContext->CSSetShaderResources(slotNo, 1, &srv.GetBody());
		}
		void CSUnsetShaderResource(int slotNo)
		{
			ID3D11ShaderResourceView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->CSSetShaderResources(slotNo, 1, view);
		}
		/*!
		* @brief	�R���s���[�g�V�F�[�_�[��UAV��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ�
		*@param[in]	uav			UAV�B
		*/
		void CSSetUnorderedAccessView(int slotNo, CUnorderedAccessView& uav)
		{
			m_pD3DDeviceContext->CSSetUnorderedAccessViews(slotNo, 1, &uav.GetBody(), NULL);
		}
		/*!
		* @brief	�R���s���[�g�V�F�[�_�[��UAV��ݒ�B
		*@param[in]	slotNo		�X���b�g�ԍ�
		*@param[in]	uav			UAV�B
		*/
		void CSUnsetUnorderedAccessView(int slotNo)
		{
			ID3D11UnorderedAccessView* view[] = {
				NULL
			};
			m_pD3DDeviceContext->CSSetUnorderedAccessViews(slotNo, 1, view, NULL);
		}
		/*!
		* @brief	�`��B
		* @param[in]	vertexCount			���_���B
		* @param[in]	startVertexLocation	�`����J�n���钸�_�̈ʒu�B���0�ő��v�B
		*/
		void Draw(
			unsigned int vertexCount,
			unsigned int startVertexLocation
		)
		{
			m_pD3DDeviceContext->Draw(vertexCount, startVertexLocation);
		}
		/*!
		* @brief	�C���f�b�N�X�t���`��B
		* @param[in]	indexCount			�C���f�b�N�X�̐��B
		* @param[in]	StartIndexLocation	�`����J�n����C���f�b�N�X�̈ʒu�B���0�ő��v�B
		* @param[in]	BaseVertexLocation	�x�[�X���_�C���f�b�N�X�B���0�ő��v�B
		*/
		void DrawIndexed(
			_In_  UINT IndexCount,
			_In_  UINT StartIndexLocation,
			_In_  INT BaseVertexLocation)
		{
			m_pD3DDeviceContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);

		}
		/*!
		* @brief	�f�B�X�p�b�`�B
		* @details
		*  �R���s���[�g�V�F�[�_�[�����s�B
		* @param[in]	threadGroupCountX	x �����Ƀf�B�X�p�b�`�����O���[�v�̐��B
		* @param[in]	threadGroupCountY	y �����Ƀf�B�X�p�b�`�����O���[�v�̐��B
		* @param[in]	thredGroupCountZ	�� �����Ƀf�B�X�p�b�`�����O���[�v�̐��B
		*/
		void Dispatch(UINT threadGroupCountX, UINT threadGroupCountY, UINT thredGroupCountZ)
		{
			m_pD3DDeviceContext->Dispatch(threadGroupCountX, threadGroupCountY, thredGroupCountZ);
		}
		private:
		/*!
		* @brief	���̓��C�A�E�g��ݒ�B
		*/
		void IASetInputLayout(ID3D11InputLayout* inputLayout)
		{
			m_pD3DDeviceContext->IASetInputLayout(inputLayout);
		}
		public:
		/*!
		* @brief	���\�[�X���R�s�[�B
		*@param[out]	destRes		�R�s�[��B
		*@param[in]		srcRes		�R�s�[���B
		*/
		template<class TResource>
		void CopyResource(TResource& destRes, TResource& srcRes)
		{
			if (destRes.GetBody() != nullptr
				&& srcRes.GetBody() != nullptr
				) {
				m_pD3DDeviceContext->CopyResource(destRes.GetBody(), srcRes.GetBody());
			}
		}

		void CopyResource(ID3D11Resource* destRes, ID3D11Resource* srcRes)
		{
			if (destRes != nullptr
				&& srcRes != nullptr
				) {
				m_pD3DDeviceContext->CopyResource(destRes, srcRes);
			}
		}
		/*!
		* @brief	�}�b�v�B
		*@param[out]	destRes		�R�s�[��B
		*@param[in]		srcRes		�R�s�[���B
		*/
		template<class TBuffer>
		void Map(TBuffer& buffer, UINT subresource, D3D11_MAP mapType, UINT mapFlags, D3D11_MAPPED_SUBRESOURCE& mappedResource)
		{
			if (buffer.GetBody() != nullptr) {
				m_pD3DImmidiateDeviceContext->Map(buffer.GetBody(), subresource, mapType, mapFlags, &mappedResource);
			}
		}
		template<class TBuffer>
		void Unmap(TBuffer& buffer, UINT subresource)
		{
			if (buffer.GetBody() != nullptr) {
				m_pD3DImmidiateDeviceContext->Unmap(buffer.GetBody(), subresource);
			}
		}
		/*!
		* @brief	�T�u���\�[�X���X�V�B
		*@param[out]	destRes		�R�s�[��B
		*@param[in]		srcRes		�R�s�[���B
		*/
		template<class TBuffer, class SrcBuffer>
		void UpdateSubresource(TBuffer& gpuBuffer, const SrcBuffer* buffer)
		{
			if (gpuBuffer.GetBody() != nullptr) {
				m_pD3DDeviceContext->UpdateSubresource(gpuBuffer.GetBody(), 0, NULL, buffer, 0, 0);
			}
		}
		/*!
		* @brief	���݂̃����_�����O�X�e�b�v���擾�B
		*@return �����_�����O�X�e�b�v�B
		*/
		EnRenderStep GetRenderStep() const
		{
			return m_renderStep;
		}
		/*!
		* @brief	���݂̃����_�����O�X�e�b�v��ݒ�B
		*@details
		* �G���W�������ł̂ݎg�p����܂��B���[�U�[�͎g�p���Ȃ��悤�ɁB
		*/
		void SetRenderStep(EnRenderStep step)
		{
			m_renderStep = step;
		}
		/*!
		* @brief	ID3D11DeviceContext::ResolveSubresource�Ɠ����B
		*/
		void ResolveSubresource(
			ID3D11Resource* dstResource,
			UINT DstSubresource,
			ID3D11Resource *pSrcResource,
			UINT SrcSubresource,
			DXGI_FORMAT Format)
		{
			m_pD3DDeviceContext->ResolveSubresource(
				dstResource,
				DstSubresource,
				pSrcResource,
				SrcSubresource,
				Format
			);
		}
		/// <summary>
		/// �`��R�}���h�̐����Ŏg�p���Ă���f�o�C�X�R���e�L�X�g���擾����B
		/// </summary>
		/// <returns></returns>
		ID3D11DeviceContext* GetD3DDeviceContext() const
		{
			return m_pD3DDeviceContext;
		}
	private:
		/// <summary>
		/// �e�탌���_�����O�X�e�[�g�B
		/// </summary>
		struct SRenderState {
			ID3D11DepthStencilState*	depthStencilState = nullptr;	//!<���݂̃f�v�X�X�e���V���X�e�[�g�B
			ID3D11RasterizerState*		rasterrizerState = nullptr;		//!<���݂̃��X�^���C�U�X�e�[�g�B
			ID3D11BlendState*			blendState = nullptr;			//!<���݂̃u�����h�X�e�[�g�B

		};
		/// <summary>
		/// �����_�����O�^�[�Q�b�g�B
		/// </summary>
		struct SRenderTarget {
			CRenderTarget* renderTargets[MRT_MAX] = { nullptr };
			unsigned int numRenderTargetViews = 0;
		};
		SRenderState m_currentRenderState;	//���݂̃����_�����O�X�e�[�g�B
		std::stack< SRenderState> m_renderStateStack;	//�����_�����O�X�e�[�g�̃X�^�b�N�B
		std::stack<SRenderTarget> m_renderTargetStack;	//�����_�����O�^�[�Q�b�g�̃X�^�b�N�B
		ID3D11DeviceContext*			m_pD3DImmidiateDeviceContext = nullptr;	//!<D3D�����f�o�C�X�R���e�L�X�g�BMap��Unmap�ł͑����f�o�C�X�R���e�L�X�g���K�v�Ȃ̂ŁA�������B
		ID3D11DeviceContext*			m_pD3DDeviceContext = nullptr;			//!<�`��R�}���h��ς�ł����R���e�L�X�g�B
		D3D11_VIEWPORT 					m_viewport;								//!<�r���[�|�[�g�B
		CRenderTarget*					m_renderTargetViews[MRT_MAX] = { nullptr };
		unsigned int 					m_numRenderTargetView = 0;		//!<�����_�����O�^�[�Q�b�g�r���[�̐��B
		EnRenderStep					m_renderStep = enRenderStep_LightCulling;	//!<�����_�����O�X�e�b�v�B
	};
}