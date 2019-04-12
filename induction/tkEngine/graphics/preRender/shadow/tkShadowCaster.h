/*!
 * @brief	�V���h�E�L���X�^�[�B
 */
 
#pragma once

namespace tkEngine{
	class CSkinModel;
	/*!
	 * @brief	�V���h�E�L���X�^�[�̃C���^�[�t�F�[�X�N���X�B
	 */
	class IShadowCaster{
	public:
		/*!
		 * @brief	�R���X�g���N�^�B
		 */
		IShadowCaster()
		{
		}
		/*!
		 * @brief	�f�X�g���N�^�B
		 */
		virtual ~IShadowCaster()
		{
		}
		/*!
		* @brief	�`��B
		*/
		virtual void Render(CRenderContext& renderContext, const CMatrix& mLVP) = 0;
	};
	/*!
	* @brief	�V���h�E�L���X�^�[(CSkinModel��)
	*/
	class CShadowCaster_SkinModel : public IShadowCaster {
	public:
		CShadowCaster_SkinModel();
		~CShadowCaster_SkinModel();
		/*!
		* @brief	�X�L�����f������쐬�B
		*/
		void Create(CSkinModel* model);
		/*!
		* @brief	�`��B
		*/
		void Render(CRenderContext& renderContext, const CMatrix& mLVP) override final;
		
	private:
		CSkinModel*		m_skinModel;	//!<�X�L�����f���B
	};
}
