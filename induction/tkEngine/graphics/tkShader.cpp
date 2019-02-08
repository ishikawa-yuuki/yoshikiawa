/*!
 * @brief	�V�F�[�_�[�B
 */
#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/tkShader.h"
#include "tkEngine/tkEngine.h"

namespace tkEngine{
	namespace {
		void ReadFile(const char* filePath, char* readBuff, int& fileSize)
		{
			FILE* fp = fopen(filePath, "rb");
			fseek(fp, 0, SEEK_END);
			fpos_t fPos;
			fgetpos(fp, &fPos);
			fseek(fp, 0, SEEK_SET);
			fileSize = (int)fPos;
			fread(readBuff, fileSize, 1, fp);
			fclose(fp);
		}
		/*!
		 *@brief	���_�V�F�[�_�[���璸�_���C�A�E�g�𐶐��B
		 */
		HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
		{
			// �V�F�[�_�[��񂩂烊�t���N�V�������s���B
			ID3D11ShaderReflection* pVertexShaderReflection = NULL;
			if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
			{
				return S_FALSE;
			}

			// �V�F�[�_�[�����擾�B
			D3D11_SHADER_DESC shaderDesc;
			pVertexShaderReflection->GetDesc(&shaderDesc);

			// ���͏���`��ǂݍ���
			std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
			for (unsigned int i = 0; i< shaderDesc.InputParameters; i++)
			{
				D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
				pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

				// �G�������g��`��ݒ�B
				D3D11_INPUT_ELEMENT_DESC elementDesc;
				elementDesc.SemanticName = paramDesc.SemanticName;
				elementDesc.SemanticIndex = paramDesc.SemanticIndex;
				elementDesc.InputSlot = 0;
				elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				elementDesc.InstanceDataStepRate = 0;

				// determine DXGI format
				if (paramDesc.Mask == 1)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
				}
				else if (paramDesc.Mask <= 3)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
				}
				else if (paramDesc.Mask <= 7)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				}
				else if (paramDesc.Mask <= 15)
				{
					if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
					else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				}

				//�G�������g�̒�`��ۑ��B
				inputLayoutDesc.push_back(elementDesc);
			}

			// ���̓��C�A�E�g���쐬�B
			HRESULT hr = pD3DDevice->CreateInputLayout(
				&inputLayoutDesc[0], 
				static_cast<UINT>(inputLayoutDesc.size()), 
				pShaderBlob->GetBufferPointer(), 
				pShaderBlob->GetBufferSize(), 
				pInputLayout);

			//���t���N�V�����p�Ɋm�ۂ���������������B
			pVertexShaderReflection->Release();
			return hr;
		}
	}
	CShader::CShader()
	{
	}
	CShader::~CShader()
	{
		Release();
	}
	
	void CShader::Release()
	{
	}
	
	bool CShader::Load(const char* filePath, const char* entryFuncName, EnType shaderType)
	{
		Release();
		auto& ge = Engine().GetGraphicsEngine();
		bool result = ge.GetShaderResources().Load(
			m_shader,
			m_inputLayout,
			m_blobOut,
			filePath,
			entryFuncName,
			shaderType
		);
	    return result;
	}
}