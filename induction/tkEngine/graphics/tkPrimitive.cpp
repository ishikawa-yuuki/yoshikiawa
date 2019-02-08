/*!
 *@brief	�v���~�e�B�u�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkPrimitive.h"

namespace tkEngine{
	CPrimitive::CPrimitive()
	{
	}
	CPrimitive::~CPrimitive()
	{
		Release();
	}
	void CPrimitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
	bool CPrimitive::Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		CIndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer)
	{
		Release();
		m_topology = topology;
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer );
		if (!result) {
			TK_WARNING("�v���~�e�B�u�̍쐬�Ɏ��s���܂����B");
			return false;
		}
		if (pSrcIndexBuffer) {
			result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
			if (!result) {
				TK_WARNING("�v���~�e�B�u�̍쐬�Ɏ��s���܂����B");
				return false;
			}
		}

		return true;
	}
	void CPrimitive::Draw(CRenderContext& rc)
	{
		//���_�o�b�t�@��ݒ�B
		rc.IASetVertexBuffer(m_vertexBuffer);
		rc.IASetIndexBuffer(m_indexBuffer);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		rc.IASetPrimitiveTopology(m_topology);
		//�`��B
		rc.DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);
	}
	
	void CPrimitive::Draw(CRenderContext& rc, int numVertex)
	{
		rc.IASetVertexBuffer(m_vertexBuffer);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		rc.IASetPrimitiveTopology(m_topology);
		//�`��B
		rc.Draw(numVertex, 0);
	}
}