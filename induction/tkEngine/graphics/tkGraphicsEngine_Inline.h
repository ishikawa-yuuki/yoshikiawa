#pragma once


namespace tkEngine{
	/*!
	*@brief	MSAA�e�N�X�`���̃��]���u�B
	*@details 
	* MSAA���L���ɂȂ��Ă��郌���_�����O�^�[�Q�b�g�̃e�N�X�`����SRV�Ƃ��Ďg�p�������ꍇ�ɌĂяo���Ă��������B�B
	*/
	inline void CRenderTarget::ResovleMSAATexture(CRenderContext& rc)
	{
		if (m_isMSAA || m_isResolveTexture) {
			//MSAA���L���łȂ���Ή������Ȃ��B
			rc.ResolveSubresource(m_resolveTextureMSAA, 0, m_renderTarget, 0, m_textureFormat);
		}
	}
}