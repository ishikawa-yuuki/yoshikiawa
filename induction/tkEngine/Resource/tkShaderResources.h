/*!
 *@brief	�V�F�[�_�[���\�[�X�B
 */

#pragma once

namespace tkEngine{
	/*!
	 *@brief	�V�F�[�_�[���\�[�X�B
	 */
	class CShaderResources : Noncopyable{
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CShaderResources();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CShaderResources();
		/*!
		 *@brief	���[�h
		 *@param[out]	shader			���[�h�����V�F�[�_�[�̊i�[��B
		 *@param[out]	inputLayout		���̓��C�A�E�g�̊i�[��B
		 *@param[out]	blob
		 *@param[in]	filePath		���[�h����V�F�[�_�[�̃t�@�C���p�X�B
		 *@param[in]	entryFuncName	�G���g���[�|�C���g�̊֐����B
		 *@param[in]	shaderType		�V�F�[�_�[�^�C�v�B
		 */
		bool Load(
			void*& shader, 
			ID3D11InputLayout*& inputLayout, 
			ID3DBlob*& blob,
			const char* filePath, 
			const char* entryFuncName,
			CShader::EnType shaderType
		);
		/*!
		*@brief	�J���B
		*@details
		* �����I�ȃ^�C�~���O�ŊJ���������ꍇ�Ɏg�p���Ă��������B
		*/
		void Release();	
	private:
		struct SShaderProgram {
			std::unique_ptr<char[]> program;
			int programSize;
		};
		struct SShaderResource{
			void* shader;					//!<�V�F�[�_�[�B
			ID3D11InputLayout* inputLayout;	//!<���̓��C�A�E�g�B
			CShader::EnType type;			//!<�V�F�[�_�[�^�C�v�B
			TScopedResource<ID3DBlob> blobOut;
		};
		typedef std::unique_ptr<SShaderResource>	SShaderResourcePtr;
		typedef std::unique_ptr<SShaderProgram>	SShaderProgramPtr;
		std::map<int, SShaderProgramPtr>		m_shaderProgramMap;		//!<�ǂݍ��ݍς݂̃V�F�[�_�[�v���O�����̃}�b�v�B
		std::map<int, SShaderResourcePtr>	m_shaderResourceMap;	//!<�V�F�[�_�[���\�[�X�̃}�b�v�B
	};
}