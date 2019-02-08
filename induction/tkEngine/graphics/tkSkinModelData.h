/*!
 *@brief	�X�L�����f���f�[�^�B
 */

#pragma once

#include "tkEngine/graphics/tkSkeleton.h"

namespace tkEngine{
	class CAnimationClip;
	typedef std::unique_ptr<CAnimationClip>	CAnimationClipPtr;
	/*!
	*@brief	���f���G�t�F�N�g�B
	*/
	class CModelEffect : public DirectX::IEffect {
	protected:
		std::wstring m_materialName;	//!<�}�e���A�����B
		CShader* m_pVSShader = nullptr;
		CShader* m_pPSShader = nullptr;
		CShader m_vsShader;
		CShader m_psShader;
		CShader m_vsShaderInstancing;		//!<���_�V�F�[�_�[�B�C���X�^���V���O�p�B
		CShader m_vsRenderToDepthShader;	//!<Z�l�������ݗp�̒��_�V�F�[�_�[�B
		CShader m_vsRenderToDepthShaderInstancing;	//!<Z�l�������ݗp�̒��_�V�F�[�_�[�B�C���X�^���V���O�p�B
		CShader m_psRenderToDepthShader;	//!<Z�l�������ݗp�̃s�N�Z���V�F�[�_�[�B
		CShader m_psRenderToGBufferShader;	//!<G-Buffer�������ݗp�̃s�N�Z���V�F�[�_�[�B
		
		ID3D11ShaderResourceView* m_diffuseTex = nullptr;
		ID3D11ShaderResourceView* m_normalMap = nullptr;
		ID3D11ShaderResourceView* m_specularMap = nullptr;
		ID3D11ShaderResourceView* m_skyCubeMap = nullptr;
		bool isSkining;
		/*!
		* @brief	�}�e���A���p�����[�^�B
		* @details 
		* ������ύX����ꍇ�́AmodelCB.h��MaterialParamCb���ύX����悤�ɁB
		*/
		struct MaterialParam {
			int hasNormalMap;				//!<�@���}�b�v����H
			int hasSpecularMap;				//!<�X�y�L�����}�b�v����H
			float anisotropic;				//!<�ٕ������ˁB
			unsigned int materialID = 0;	//!<�}�e���A��ID�B
		};
		static const int NUM_POINT_LIGHT = 1024;
		MaterialParam m_materialParam;				//�}�e���A���p�����[�^�B
		CConstantBuffer m_materialParamCB;			//�}�e���A���p�����[�^�p�̒萔�o�b�t�@�B
		CRenderContext* m_renderContext = nullptr;	//�����_�����O�R���e�L�X�g�B
		int m_numInstance = 1;						//�`�悷��C���X�^���X�̐��B
	public:
		CModelEffect()
		{
			m_materialParam.anisotropic = 0.5f;
			m_materialParamCB.Create(&m_materialParam, sizeof(m_materialParam));
			m_psShader.Load("shader/model.fx", "PSMain", CShader::EnType::PS);
			m_psRenderToDepthShader.Load("shader/model.fx", "PSMain_RenderDepth", CShader::EnType::PS);
			m_psRenderToGBufferShader.Load("shader/model.fx", "PSMain_RenderGBuffer", CShader::EnType::PS);
			m_pPSShader = &m_psShader;
		}
		virtual ~CModelEffect()
		{
			if (m_diffuseTex) {
				m_diffuseTex->Release();
			}
			if (m_normalMap) {
				m_normalMap->Release();
			}
			if (m_specularMap) {
				m_specularMap->Release();
			}
			if (m_skyCubeMap) {
				m_skyCubeMap->Release();
			}
		}
		void __cdecl Apply(ID3D11DeviceContext* deviceContext) override;
		
		void __cdecl GetVertexShaderBytecode(void const** pShaderByteCode, size_t* pByteCodeLength) override
		{
			*pShaderByteCode = m_vsShader.GetByteCode();
			*pByteCodeLength = m_vsShader.GetByteCodeSize();
		}
		void SetDiffuseTexture(ID3D11ShaderResourceView* tex)
		{
			m_diffuseTex = tex;
		}
		void SetNormalMap(CShaderResourceView& srv)
		{
			SetNormalMap(srv.GetBody());
		}
		void SetNormalMap(ID3D11ShaderResourceView* tex)
		{
			m_normalMap = tex;
			m_normalMap->AddRef();
		}
		void SetSpecularMap(CShaderResourceView& srv)
		{
			SetSpecularMap(srv.GetBody());
		}
		void SetSpecularMap(ID3D11ShaderResourceView* tex)
		{
			m_specularMap = tex;
			m_specularMap->AddRef();
		}
		void SetSkyCubeMap(ID3D11ShaderResourceView* tex)
		{
			m_skyCubeMap = tex;
			m_skyCubeMap->AddRef();
		}
		void SetMatrialName(const wchar_t* matName)
		{
			m_materialName = matName;
		}
		void SetRenderContext(CRenderContext& rc)
		{
			m_renderContext = &rc;
		}
		void SetNumInstance(int numInstance)
		{
			m_numInstance = numInstance;
		}
		//�f�t�H���g�̃}�e���A���h�c��0
		void SetMaterialID(unsigned int materialID)
		{
			m_materialParam.materialID = materialID;
		}
		bool EqualMaterialName(const wchar_t* name) const
		{
			return wcscmp(name, m_materialName.c_str()) == 0;
		}
		/*!
		*@brief	enRenderStep_Render3DModelToScene�̎��Ɏg�p����钸�_�V�F�[�_�[��ݒ�B
		*  
		*/
		void SetRender3DModelVSShader(CShader& vsShader)
		{
			m_pVSShader = &vsShader;
		}
		/*!
		*@brief	enRenderStep_Render3DModelToScene�̎��Ɏg�p�����s�N�Z���V�F�[�_�[��ݒ�B
		*
		*/
		void SetRender3DModelPSShader(CShader& psShader)
		{
			m_pPSShader = &psShader;
		}
		/*!
		*@brief	enRenderStep_Render3DModelToScene�̎��Ɏg�p�����V�F�[�_�[���f�t�H���g�V�F�[�_�[�ɂ���B
		*
		*/
		void SetRender3DModelDefaultShader()
		{
			m_pVSShader = &m_vsShader;
			m_pPSShader = &m_psShader;
		}
	};
	/*!
	*@brief
	*  �X�L���Ȃ����f���G�t�F�N�g�B
	*/
	class CNonSkinModelEffect : public CModelEffect {
	public:
		CNonSkinModelEffect()
		{
			m_vsShader.Load("shader/model.fx", "VSMain", CShader::EnType::VS);
			m_vsRenderToDepthShader.Load("shader/model.fx", "VSMain_RenderDepth", CShader::EnType::VS);
			m_vsRenderToDepthShaderInstancing.Load("shader/model.fx", "VSMainInstancing_RenderDepth", CShader::EnType::VS);
			m_vsShaderInstancing.Load("shader/model.fx", "VSMainInstancing", CShader::EnType::VS);
			m_pVSShader = &m_vsShader;
			isSkining = false;
		}
	};
	/*!
	*@brief
	*  �X�L�����f���G�t�F�N�g�B
	*/
	class CSkinModelEffect : public CModelEffect {
	public:
		CSkinModelEffect()
		{
			m_vsShader.Load("shader/model.fx", "VSMainSkin", CShader::EnType::VS);
			m_vsRenderToDepthShader.Load("shader/model.fx", "VSMainSkin_RenderDepth", CShader::EnType::VS);
			m_pVSShader = &m_vsShader;
			isSkining = true;
		}
	};

	/*!
	 *@brief	�X�L�����f���f�[�^�B
	 */
	class CSkinModelData : Noncopyable{
	public:
		
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CSkinModelData();
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		~CSkinModelData();
		/*!
		 *@brief	���[�h�B
		 *@param[in]	filePath	�t�@�C���p�X�B
		 *@return	true���Ԃ��Ă����烍�[�h�����B
		 */
		bool Load( const wchar_t* filePath );
		/*!
		*@brief	�C���X�^���X�����p�\���ǂ������ׂ�B
		*/
		bool IsAvailable() const
		{
			return m_isAvailable;
		}
		DirectX::Model& GetBody()
		{
			return *m_modelDx;
		}
		/*!
		 *@brief	�X�P���g�����擾�B
		 */
		CSkeleton& GetSkeleton()
		{
			return m_skeleton;
		}
		/*!
		*@brief	�X�P���g�����擾�B
		*/
		const CSkeleton& GetSkeleton() const
		{
			return m_skeleton;
		}
		typedef std::function<void(std::unique_ptr<DirectX::ModelMeshPart>&)>		OnFindMesh;
		/*!
		 *@brief	���b�V���̌����B
		 *@param[in]	findMesh		���b�V�������������ɌĂ΂��R�[���o�b�N�֐�
		 */
		void FindMesh(OnFindMesh findMesh) const;
	private:
		std::wstring m_filePath;
		DirectX::Model* m_modelDx = nullptr;
		CSkeleton	m_skeleton;
		bool m_isAvailable = false;	//�C���X�^���X�����p�\���ǂ����̃t���O�B
	};
}