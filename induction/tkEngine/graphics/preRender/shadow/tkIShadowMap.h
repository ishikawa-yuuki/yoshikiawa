/// <summary>
/// �V���h�E�}�b�v�̊��N���X�B
/// </summary>
#pragma once

namespace tkEngine{
	class IShadowCaster;
	/// <summary>
	/// �V���h�E�}�b�v�̊��N���X�B
	/// </summary>
	class IShadowMap : Noncopyable{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		IShadowMap() {}
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		virtual ~IShadowMap() {}
		/// <summary>
		/// �V���h�E�L���X�^�[�̓o�^�B
		/// </summary>
		/// <param name="caster">�L���X�^�[</param>
		void Entry(IShadowCaster* caster)
		{
			if (!m_isEnable) {
				return;
			}
			m_shadowCaster.push_back(caster);
		}
		/// <summary>
		/// 
		/// </summary>
		/// <param name="caster">�L���X�^�[</param>
		void Remove(IShadowCaster* caster)
		{
			auto it = std::find(m_shadowCaster.begin(), m_shadowCaster.end(), caster);
			if (it != m_shadowCaster.end()) {
				//�������̂ō폜�B
				m_shadowCaster.erase(it);
			}
		}
		/// <summary>
		/// �`�揈���B
		/// </summary>
		void RenderToShadowMap(CRenderContext& rc);
		/// <summary>
		/// �e���������𖳌��ɂ���B
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}
		/// <summary>
		/// �e����������L���ɂ���B
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}
	protected:
		/// <summary>
		/// �e�������L�������肷��B
		/// </summary>
		/// <remark>
		/// 
		/// </remark>
		bool IsEnable() const
		{
			return m_isInited && m_isEnable;
		}
	private:
		/// <summary>
		/// �h���N���X�Ŏ�������`�揈���B
		/// </summary>
		virtual void RenderToShadowMapImp(CRenderContext& rc) = 0;
	protected:
		bool m_isEnable = false;
		bool m_isInited = false;
		std::vector<IShadowCaster*> m_shadowCaster;			//!<�V���h�E�L���X�^�[�B

	};
}
