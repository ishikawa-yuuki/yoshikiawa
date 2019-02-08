#pragma once

namespace tkEngine{
namespace prefab{
	/// <summary>
	/// ���`��ł���Q�[���I�u�W�F�N�g
	/// </summary>
	/// <remarks>
	/// �L���[�u�}�b�v�𗘗p������̕`��s���܂�(SkyCubeMap)�B
	/// SkyCubeMap�𗘗p����ƁA���𑜓x�̋�̃����_�����O���\�ɂȂ�܂��B
	/// </remarks>
	class CSky final : public IGameObject
	{
	public:
		/// <summary>
		/// �R���X�g���N�^�B
		/// </summary>
		CSky();
		/// <summary>
		/// �f�X�g���N�^�B
		/// </summary>
		~CSky();
		/// <summary>
		/// �J�n�����B
		/// </summary>
		/// <returns>true��Ԃ����珉���������B</returns>
		bool Start() override ;
		/// <summary>
		/// ��̑傫����ݒ�B
		/// </summary>
		/// <param name="scale">��̑傫��</param>
		void SetScale(float scale)
		{
			m_scale = { scale, scale, scale };
			m_isDirty = true;
		}
		/// <summary>
		/// ��̑傫����ݒ�(�x�N�g����)
		/// </summary>
		/// <param name="scale">��̑傫��</param>
		void SetScale(CVector3 scale)
		{
			m_scale = scale;
			m_isDirty = true;
		}
		/// <summary>
		/// ���Ȕ����J���[��ݒ�B
		/// </summary>
		/// <param name="emissionColor">���Ȕ����J���[</param>
		void SetEmissionColor(CVector3 emissionColor)
		{
			m_emissionColor = emissionColor;
			m_isDirty = true;
		}
		/// <summary>
		/// ��̈ʒu�����߂�B
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(CVector3 pos)
		{
			m_position = pos;
			m_isDirty = true;
		}
		/// <summary>
		/// �X�V�����B
		/// </summary>
		void Update() override;
		/// <summary>
		/// ��̃L���[�u�}�b�v�̃t�@�C���p�X��ݒ�B
		/// </summary>
		/// <param name="filepath">�t�@�C���p�X</param>
		/// <remarks>
		/// �C�ӂ̃L���[�u�}�b�v�ɕύX�������ꍇ�ɁA�g�p���Ă��������B
		/// �ύX���Ȃ���΁A�f�t�H���g�̃L���[�u�}�b�v�����[�h����܂��B
		/// ���̊֐��𗘗p����ꍇ�́A�C���X�^���X���쐬��������ɗ��p���Ă��������B
		/// ����ȊO�̃^�C�~���O�ŗ��p����ƁA���łɃL���[�u�}�b�v�����[�h�ς݂ƂȂ��Ă��邽��
		/// �ύX���邱�Ƃ͂ł��܂���B
		/// </remarks>
		/// <example>
		/// �L���[�u�}�b�v��ύX����T���v���R�[�h
		/// </example>
		/// <code>
		/// auto sky = NewGO<prefab::CSky>(0);							//��̃C���X�^���X���쐬�B
		/// sky->SetSkyCubeMapFilePath(L"modelData/mySkyCubeMap.dds");	//�L���[�u�}�b�v�������ւ��B
		/// </code>
		void SetSkyCubeMapFilePath(const wchar_t* filepath)
		{
#ifndef TK_MASTER
			if (m_isStart == true) {
				TK_WARNING("SkyCubeMap�̃��[�h���������Ă��邽��"
					"�L���[�u�}�b�v�̍����ւ��͂ł��܂���B"
					"SetSkyCubeMapFilePath�֐��̃R�����g���Q�Ƃ��āA�K�؂ȃ^�C�~���O�Ŗ{�֐��𗘗p���Ă��������B");
			}
#endif
			m_skyCubeMapFilePath = filepath;
		}
		/// <summary>
		/// ��̃��f���̃t�@�C���p�X��ݒ�B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// /// <remarks>
		/// �C�ӂ̋�̃��f���ɕύX�������ꍇ�ɁA�g�p���Ă��������B
		/// �ύX���Ȃ���΁A�f�t�H���g�̋󂪃��[�h����܂��B
		/// ���̊֐��𗘗p����ꍇ�́A�C���X�^���X���쐬��������ɗ��p���Ă��������B
		/// ����ȊO�̃^�C�~���O�ŗ��p����ƁA���łɋ�̃��f�������[�h�ς݂ƂȂ��Ă��邽��
		/// �ύX���邱�Ƃ͂ł��܂���B
		/// </remarks>
		/// <example>
		/// ���f����ύX����T���v���R�[�h
		/// </example>
		/// <code>
		/// auto sky = NewGO<prefab::CSky>(0);					//��̃C���X�^���X���쐬�B
		/// sky->SetSkyModelFilePath(L"modelData/mySky.cmo");	//���f���������ւ��B
		/// </code>
		void SetSkyModelFilePath(const wchar_t* filePath)
		{
#ifndef TK_MASTER
			if (m_isStart == true) {
				TK_WARNING("��̃��f���̃��[�h���������Ă��邽��"
					"��̃��f���̍����ւ��͂ł��܂���B"
					"SetSkyModelFilePath�֐��̃R�����g���Q�Ƃ��āA�K�؂ȃ^�C�~���O�Ŗ{�֐��𗘗p���Ă��������B");
			}
#endif
			m_skyModelFilePath = filePath;
		}
	private:
		prefab::CSkinModelRender* m_skinModelRender = nullptr;	//���f���`��̃Q�[���I�u�W�F�N�g�B
		CShaderResourceView m_skyCube;							//�X�J�C�L���[�u�}�b�v��SRV
		CShader m_psSkyShader;									//��p�̃V�F�[�_�[�B
		CVector3 m_scale = { 8000.0f, 8000.0f, 8000.0f };		//��̊g�嗦�B
		CVector3 m_position = CVector3::Zero;					//���W�B
		CVector3 m_emissionColor = CVector3::Zero;				//���Ȕ����J���[�B
		bool m_isDirty = false;									//�_�[�e�B�t���O�B
		std::wstring m_skyCubeMapFilePath = L"modelData/preset/skyCubeMap.dds";		//��̃L���[�u�}�b�v�̃t�@�C���p�X�B
		std::wstring m_skyModelFilePath = L"modelData/preset/sky.cmo";				//���cmo�t�@�C���̃t�@�C���p�X�B
	};
}
}
