#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/resource/tkDirectXModelResource.h"
#include "tkEngine/graphics/tkSkinModelData.h"

namespace tkEngine {
	/*!
	*@brief
	*  �G�t�F�N�g�t�@�N�g���B
	*/
	class CSkinModelEffectFactory : public DirectX::EffectFactory {
	public:
		CSkinModelEffectFactory(ID3D11Device* device) :
			EffectFactory(device) {}
		std::shared_ptr<DirectX::IEffect> __cdecl CreateEffect(const EffectInfo& info, ID3D11DeviceContext* deviceContext)override
		{
			std::shared_ptr<CModelEffect> effect;
			if (info.enableSkinning) {
				//�X�L�j���O����B
				effect = std::make_shared<CSkinModelEffect>();
			}
			else {
				//�X�L�j���O�Ȃ��B
				effect = std::make_shared<CNonSkinModelEffect>();
			}
			effect->SetMatrialName(info.name);
			if (info.diffuseTexture && *info.diffuseTexture)
			{
				ID3D11ShaderResourceView* texSRV;
				DirectX::EffectFactory::CreateTexture(info.diffuseTexture, deviceContext, &texSRV);
				effect->SetDiffuseTexture(texSRV);
			}
			return effect;
		}

		void __cdecl CreateTexture(const wchar_t* name, ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView** textureView) override
		{
			return DirectX::EffectFactory::CreateTexture(name, deviceContext, textureView);
		}
	};

	bool CDirectXModelResource::m_isInstanced = false;
	CDirectXModelResource::CDirectXModelResource()
	{
		TK_ASSERT(m_isInstanced == false, "CDirectXModelDataManager�̃C���X�^���X�𕡐���邱�Ƃ͂ł��܂���B");
		m_isInstanced = true;
	}
	CDirectXModelResource::~CDirectXModelResource()
	{
		m_isInstanced = false;
	}
	DirectX::Model* CDirectXModelResource::Load(const wchar_t* filePath, CSkeleton& skeleton)
	{
		auto nameKey = CUtil::MakeHash(filePath);
		auto it = m_resourceMap.find(nameKey);
		if (it != m_resourceMap.end()) {
			//�g���܂킷�B
			return it->second.get();
		}
		//�V�K�B
		auto effectFactory = CSkinModelEffectFactory(GraphicsEngine().GetD3DDevice());

		//�{�[���𔭌������Ƃ��̃R�[���o�b�N�B
		auto onFindBone = [&](
			const wchar_t* boneName,
			const VSD3DStarter::Bone* bone,
			std::vector<int>& localBoneIDtoGlobalBoneIDTbl
			) {
			int globalBoneID = skeleton.FindBoneID(boneName);
			if (globalBoneID == -1) {
				TK_WARNING("BoneID wasn't found!!!!");
				return;
			}
			localBoneIDtoGlobalBoneIDTbl.push_back(globalBoneID);
		};
		try {
			auto model = DirectX::Model::CreateFromCMO(
				GraphicsEngine().GetD3DDevice(),
				filePath,
				effectFactory,
				false,
				false,
				onFindBone
			);
			auto pRawModel = model.get();
			m_resourceMap.insert(std::pair<int, DirectXModelPtr>(nameKey, std::move(model)));
			return pRawModel;
		}
		catch (std::exception& exception) {
			if (strcmp(exception.what(), DirectX::Model::NOT_BUILD_SKELETON_EXCEPTION_MESSAGE) == 0) {
				//�X�P���g�����\�z����Ă��Ȃ��G���[���N�����B
				char cFilePath[256];
				wcstombs(cFilePath, filePath, 255);
				char cTksFilePath[256];
				strcpy(cTksFilePath, cFilePath);
				auto ext = strstr(cTksFilePath, ".cmo");
				ext[1] = 't';
				ext[2] = 'k';
				ext[3] = 's';
				TK_WARNING_MESSAGE_BOX("%s\n"
					"�X�P���g���f�[�^�̃��[�h�Ɏ��s���܂����B\n"
					"Assets�t�H���_���m�F���āA%s�Ɠ����ꏊ��%s�����݂��邩�m�F���Ă��������B\n"
					"�������݂��Ă���ꍇ�́Atks�t�@�C���̏o�̓~�X���l�����܂��B\n", exception.what(), cFilePath, cTksFilePath);
			}
			else if (strcmp(exception.what(), DirectX::Model::NOT_LOADED_CMO_EXCEPTION_ESSAGE) == 0) {
				//CMO�t�@�C���̓ǂݍ��݃G���[���N�����B
				char cFilePath[256];
				wcstombs(cFilePath, filePath, 255);
				TK_WARNING_MESSAGE_BOX("%s\n"
					"cmo�t�@�C���̃��[�h�Ɏ��s���܂����B\n"
					"Assets�t�H���_���m�F���āA�t�@�C�������Ԉ���Ă��Ȃ����m�F�����肢���܂��B\n"
					"���[�h���悤�Ƃ����t�@�C�� ���@%s\n"
					, exception.what(), cFilePath);
			}
			else if (strcmp(exception.what(), DirectX::Model::NOT_ASSIGN_MATERIAL_TO_MESH) == 0) {
				//CMO�t�@�C���̓ǂݍ��݃G���[���N�����B
				char cFilePath[256];
				wcstombs(cFilePath, filePath, 255);
				TK_WARNING_MESSAGE_BOX("%s\n"
					"cmo�t�@�C���̃��[�h�Ɏ��s���܂����B\n"
					"�}�e���A�������蓖�Ă��Ă��Ȃ��|���S�������݂��܂��B\n"
					"���f���f�[�^�̊m�F�����肢���܂��B\n"
					"���[�h���悤�Ƃ����t�@�C�� ���@%s\n"
					, exception.what(), cFilePath);
			}
			else {
				//����ȊO
				TK_WARNING_MESSAGE_BOX("%s\n", exception.what());
			}
		}
		return nullptr;
		
	}
}