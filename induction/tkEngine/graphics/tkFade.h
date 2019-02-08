#pragma once
namespace tkEngine{
	namespace prefab{
		class CFade : public IGameObject
		{
		public:
			CFade();
			~CFade();
			bool Start() override;
			/// <summary>
			/// �t�F�[�h���J�n����B
			/// </summary>
			/// <param name="targetColor">�^�[�Q�b�g�J���[</param>
			/// <param name="fadeTime">�t�F�[�h����(�P��:�b)</param>
			void Start(CVector4 targetColor, float fadeTime)
			{
				m_startColor = m_currentColor;
				m_targetColor = targetColor;
				m_fadeTime = fadeTime;
				m_timer = 0.0f;
				m_isFade = true;
			}
			/// <summary>
			/// �t�F�[�h��������
			/// </summary>
			/// <returns></returns>
			bool IsFade() const
			{
				return m_isFade;
			}
			void Update() override;
		private:
			CVector4 m_targetColor = {0.0f, 0.0f, 0.0f, 0.0f};
			CVector4 m_currentColor = { 0.0f, 0.0f, 0.0f, 0.0f };
			CVector4 m_startColor = { 0.0f, 0.0f, 0.0f, 0.0f };
			float m_timer = 0.0f;
			float m_fadeTime = 0.0f;
			bool m_isFade = false;
			prefab::CSpriteRender* m_spriteRender = nullptr;	//�X�v���C�g�����_���[�B
		};
	}
}
