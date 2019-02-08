/*!
 *@brief	�Z�p�`�u���[�B
 */

#pragma once

namespace tkEngine{
	/// <summary>
	/// �Z�p�`�u���[�B
	/// </summary>
	/// <remarks>
	/// �Q�lURL
	/// https://colinbarrebrisebois.com/2017/04/18/hexagonal-bokeh-blur-revisited/
	/// http://hikita12312.hatenablog.com/entry/2017/09/26/225828
	/// </remarks>
	class CHexaBlur final : Noncopyable {
	public:
		/// <summary>
		/// �`��p�X�B
		/// </summary>
		enum EnRenderPass {
			enRenderPass_VerticalDiagonalBlur,			//�����A�΂߃u���[
			enRenderPass_CombineVerticalDiagonalBlur,	//�����u���[�Ǝ΂߃u���[����������B
			enRenderPass_RhomboidBlur,					//�Z�p�`�u���[���쐬����B
			enRenderPass_Num,
		};
		/// <summary>
		/// �������B
		/// </summary>
		/// <param name="srcTexture">�\�[�X�ƂȂ�e�N�X�`��</param>
		/// <param name="isScaleup">�g��u���[��������H</param>
		void Init(CShaderResourceView& srcTexture, bool isScaleup = false);
		/// <summary>
		/// �u���[�����s�B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void Execute(CRenderContext& rc, std::function<void(CRenderContext& rc, EnRenderPass)> onPreDraw);
		/// <summary>
		/// �\�[�X�e�N�X�`����ύX�B
		/// </summary>
		/// <param name="srcTexture">�\�[�X�e�N�X�`��</param>
		void ChangeSrcTexture(CShaderResourceView& srcTexture)
		{
			m_srcTexture = &srcTexture;
		}
		/// <summary>
		/// �u���[�̔��a��ݒ�B
		/// </summary>
		/// <param name="radius">�u���[�̔��a(�P�ʁF�e�N�Z��)</param>
		void SetRadius(float radius)
		{
			m_radius = radius;
		}
		/// <summary>
		/// �u���[�̔��a���擾�B
		/// </summary>
		float GetRadius() const
		{
			return m_radius;
		}
		/// <summary>
		/// ���ʂ��擾�B
		/// </summary>
		/// <returns></returns>
		CShaderResourceView& GetResultSRV()
		{
			return m_renderTarget[enRenderTarget_RhomboidBlur].GetRenderTargetSRV();
		}
	private:
		
		enum EnRenderTarget {
			enRenderTarget_VerticalBlur,			//�����u���[�B
			enRenderTarget_DiagonalBlur,			//�΂߃u���[�B
			enRenderTarget_VerticalDiagonalBlur,	//�����A�΂߃u���[�B
			enRenderTarget_RhomboidBlur,			//�Z�p�`�u���[�B
			enRenderTarget_Num,
		};
		/// <summary>
		/// ���̍\���̂̒��g��ύX������AhexaBlur.fx��cbParam���ύX����悤�ɁB
		/// </summary>
		struct SCBParam {
			CVector2 texSize;		//�u���[��������e�N�X�`���̃T�C�Y�B
			float radius;			//�u���[�̔��a�B
		};
		CShaderResourceView* m_srcTexture = nullptr;		//�u���[���̃e�N�X�`���B
		CRenderTarget m_renderTarget[enRenderTarget_Num];	//�����_�����O�^�[�Q�b�g�B
		CShader m_vs;										//���_�V�F�[�_�B
		CShader m_psVerticalDiagonalBlur;					//�����A�΂߃u���[�̃s�N�Z���V�F�[�_�[�B
		CShader m_psCombineVerticalDiagonalBlur;			//�����A�΂߃u���[�̍����p�̃s�N�Z���V�F�[�_�[�B
		CShader m_psRhomboidBlur;							//�Z�p�`�u���[���쐬����B
		CConstantBuffer m_cb;								//�萔�o�b�t�@�B
		float m_radius = 4.0f;								//�u���[���a�B
	};
}
