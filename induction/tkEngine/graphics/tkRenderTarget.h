/*!
 * @brief	�����_�����O�^�[�Q�b�g�B
 */

#pragma once

namespace tkEngine{

	class CRenderContext;
	/*!
	 * @brief	�����_�����O�^�[�Q�b�g�B
	 */
	class CRenderTarget {
	public:
		CRenderTarget();
		~CRenderTarget();
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̍쐬�B
		 *@param[in]	w					�����_�����O�^�[�Q�b�g�̕��B
		 *@param[in]	h					�����_�����O�^�[�Q�b�g�̍����B
		 *@param[in]	mipLevel			�~�b�v�}�b�v���x���B0���w�肵���ꍇ�̓~�b�v�}�b�v���T�|�[�g����Ă���GPU�ł�1*1�s�N�Z���܂ł̃~�b�v�}�b�v���쐬�����B
		 *@param[in]	arraySize			�e�N�X�`���z��̃T�C�Y�B
		 *@param[in]	colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g�B
		 *@param[in]	depthStencilFormat	�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		 *@param[in]	multiSampleDesc		�}���`�T���v�����O�̒�`�B
		 *@param[in]	renderTarget		�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���Bnullptr���w�肳��Ă�����A�����Ńe�N�X�`���𐶐�����B
		 *@param[in]	depthStencil		�f�v�X�X�e���V���ƂȂ�e�N�X�`���Bnullptr���w�肳��Ă�����A�����Ńe�N�X�`���𐶐�����B
		 *@return	true���Ԃ��Ă�����쐬�����B
		 */
		bool Create(
			int w,
			int h,
			int mipLevel,
			int arraySize,
			DXGI_FORMAT colorFormat,
			DXGI_FORMAT depthStencilFormat,
			DXGI_SAMPLE_DESC multiSampleDesc,
			ID3D11Texture2D* renderTarget = nullptr,
			ID3D11Texture2D* depthStencil = nullptr,
			bool isResolveTexture = false
		);
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̔j���B
		 */
		void Release();
		/*!
		*@brief	�����_�����O�^�[�Q�b�g���擾�B
		*/
		ID3D11Texture2D* GetRenderTarget()
		{
			return m_renderTarget;
		}
		/*!
		*@brief	�����_�����O�^�[�Q�b�g�r���[�̎擾�B
		*/
		ID3D11RenderTargetView* GetRenderTargetView()
		{
			return m_renderTargetView;
		}
		/*!
		*@brief	�����_�����O�^�[�Q�b�g��SRV���擾�B
		*/
		CShaderResourceView& GetRenderTargetSRV()
		{
			return m_renderTargetSRV;
		}
		/*!
		*@brief	�����_�����O�^�[�Q�b�g��UAV���擾�B
		*/
		CUnorderedAccessView& GetRenderTargetUAV()
		{
			return m_renderTargetUAV;
		}
		/*!
		*@brief	�f�v�X�X�e���V���̎擾�B
		*/
		ID3D11Texture2D* GetDepthStencil()
		{
			return m_depthStencil;
		}
		/*!
		*@brief	�f�v�X�X�e���V���r���[�̎擾�B
		*/
		ID3D11DepthStencilView* GetDepthStencilView()
		{
			return m_depthStencilView;
		}
		/*!
		*@brief	�f�v�X�X�e���V���r���[��ݒ�B
		*/
		void SetDepthStencilView(ID3D11DepthStencilView* view)
		{
			if (m_depthStencilView != nullptr) {
				//���݂̃f�v�X�X�e���V���r���[�������[�X�B
				m_depthStencilView->Release();
			}
			m_depthStencilView = view;
			m_depthStencilView->AddRef();
		}
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̕����擾�B
		 */
		int GetWidth() const
		{
			return m_width;
		}
		int GetHeight() const
		{
			return m_height;
		}
		/*!
		 *@brief	�����_�����O�^�[�Q�b�g�̃e�N�X�`���̃t�H�[�}�b�g���擾�B
		 */
		DXGI_FORMAT GetRenderTargetTextureFormat() const
		{
			return m_textureFormat;
		}
		/*!
		 *@brief	�f�v�X�X�e���V���̃t�H�[�}�b�g���擾�B
		 */
		DXGI_FORMAT GetDepthStencilFormat() const
		{
			return m_depthStencliFormat;
		}
		/*!
		*@brief	MSAA�e�N�X�`���̃��]���u�B
		*@details 
		* MSAA���L���ɂȂ��Ă��郌���_�����O�^�[�Q�b�g�̃e�N�X�`����SRV�Ƃ��Ďg�p�������ꍇ�ɌĂяo���Ă��������B�B
		*/
		inline void ResovleMSAATexture(CRenderContext& rc);
		
	private:
		ID3D11Texture2D*			m_renderTarget = nullptr;			//!<�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`���B
		ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<�����_�[�^�[�Q�b�g�r���[�B
		ID3D11Texture2D*			m_depthStencil = nullptr;			//!<�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
		ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<�f�v�X�X�e���V���r���[�B
		CShaderResourceView			m_renderTargetSRV;					//!<�����_�����O�^�[�Q�b�g��SRV�B
		CUnorderedAccessView		m_renderTargetUAV;					//!<�����_�����O�^�[�Q�b�g��UAV�B
		ID3D11Texture2D*			m_resolveTextureMSAA = nullptr;		//!<MSAA���L���̎��Ƀ��]���u���ꂽ�e�N�X�`���B
		bool						m_isMSAA = false;					//!<MSAA���L���H
		DXGI_FORMAT					m_textureFormat = DXGI_FORMAT_UNKNOWN;	//!<�e�N�X�`���̃t�H�[�}�b�g�B
		DXGI_FORMAT					m_depthStencliFormat = DXGI_FORMAT_UNKNOWN;	//!<�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		bool m_isResolveTexture = false;
		int m_width = 0;
		int m_height = 0;
	};
}