/*!
 *@brief	�����_�����O�^�[�Q�b�g�؂�ւ��̃w���p�[�N���X�B
 */

#pragma once

namespace tkEngine{
	/// <summary>
	/// �����_�����O�^�[�Q�b�g�؂�ւ��N���X�B
	/// </summary>
	class CChangeRenderTarget {
		bool m_isRestoreRenderTarget = false;	//�����_�����O�^�[�Q�b�g�����ɖ߂��H
		CRenderTarget* m_oldRenderTargets[MRT_MAX] = { nullptr };
		unsigned int m_numRenderTargetViews = 0;
		CRenderContext* m_renderContext = nullptr;
	public:
		CChangeRenderTarget(CRenderContext& rc, CRenderTarget& rt, bool isRestoreRenderTarget = false)
		{
			CRenderTarget* rts[] = {
				&rt
			};
			Init(rc, 1, rts, isRestoreRenderTarget);
		}
		CChangeRenderTarget(CRenderContext& rc, int numRenderTargets, CRenderTarget* rts[], bool isRestoreRenderTarget = false)
		{
			Init(rc, numRenderTargets, rts, isRestoreRenderTarget);
		}
		~CChangeRenderTarget()
		{
			if (m_isRestoreRenderTarget == true) {
				//�����_�����O�^�[�Q�b�g�����ɖ߂��B
				//�����_�����O�^�[�Q�b�g��߂��B
				m_renderContext->OMSetRenderTargets(m_numRenderTargetViews, m_oldRenderTargets);
				if (m_oldRenderTargets[0] != nullptr) {
					m_renderContext->RSSetViewport(
						0.0f, 0.0f, (float)m_oldRenderTargets[0]->GetWidth(), (float)m_oldRenderTargets[0]->GetHeight());
				}
			}
		}
	private:
		void Init(CRenderContext& rc, int numRenderTargets, CRenderTarget* rts[], bool isRestoreRenderTarget)
		{
			m_renderContext = &rc;
			m_isRestoreRenderTarget = isRestoreRenderTarget;
			if (m_isRestoreRenderTarget == true) {
				//�����_�����O�^�[�Q�b�g�����ɖ߂��̂Ńo�b�N�A�b�v������Ă����B
				rc.OMGetRenderTargets(m_numRenderTargetViews, m_oldRenderTargets);
			}
			
			rc.OMSetRenderTargets(numRenderTargets, rts);
			if (rts[0] != nullptr) {
				rc.RSSetViewport(0.0f, 0.0f, (float)rts[0]->GetWidth(), (float)rts[0]->GetHeight());
			}
		}
	};
}