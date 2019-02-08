/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#include "tkEngine/tkEnginePrecompile.h"
#include "tkEngine/graphics/animation/tkAnimationClip.h"

namespace tkEngine {
	/*!
	*@brief
	*/
	CAnimationClip::~CAnimationClip()
	{
	}
	/*!
	*@brief	�A�j���[�V�����N���b�v�����[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*@param[in]	clipName	�N���b�v���B
	*/
	void CAnimationClip::Load(const wchar_t* filePath, const wchar_t* clipName)
	{
		auto fp = _wfopen(filePath, L"rb");
		if (fp == nullptr) {
			TK_WARNING_MESSAGE_BOX_W(L"�A�j���[�V�����N���b�v�̃I�[�v���Ɏ��s���܂����B�t�@�C���p�X : %s\n"
									 L"�����Ƃ��āA���L�̂Q�_���l�����܂��B\n"
									 L"�@ �t�@�C���p�X���ԈႦ�Ă���B\n"
									 L"�A Assets�t�H���_�̒��Ƀt�@�C�������݂��Ȃ��B\n"
									 L"���̂Q�_���m�F���āA��肪���݂��Ȃ��ꍇ�́A��xVisualStudio�̃r���h/���r���h���s���Ă݂Ă��������B\n", filePath);
			
			return;
		}
		if (clipName != nullptr) {
			m_clipName = clipName;
		}
		//�A�j���[�V�����N���b�v�̃w�b�_�[�����[�h�B
		AnimClipHeader header;
		fread(&header, sizeof(header), 1, fp);
		
		if (header.numAnimationEvent > 0) {
			m_animationEvent = std::make_unique<CAnimationEvent[]>(header.numAnimationEvent);
			//�A�j���[�V�����C�x���g������Ȃ�A�C�x���g�������[�h����B
			for (auto i = 0; i < (int)header.numAnimationEvent; i++) {
				AnimationEvent animEvent;
				fread(&animEvent, sizeof(animEvent), 1, fp);
				//�C�x���g�������[�h����B
				static char eventName[256]; 
				static wchar_t wEventName[256];
				fread(eventName, animEvent.eventNameLength+1, 1, fp);
				mbstowcs(wEventName, eventName, 255);
				m_animationEvent[i].SetInvokeTime(animEvent.invokeTime);
				m_animationEvent[i].SetEventName(wEventName);
			}
		}
		m_numAnimationEvent = header.numAnimationEvent;

		//���g���������ƃ��[�h�B
		auto keyframes = std::make_unique<KeyframeRow[]>(header.numKey);
		fread(keyframes.get(), sizeof(KeyframeRow), header.numKey, fp);
		fclose(fp);
		for (auto i = 0; i < (int)header.numKey; i++) {
			auto keyframe = std::make_unique<Keyframe>();
			keyframe->boneIndex = keyframes[i].boneIndex;
			keyframe->transform = CMatrix::Identity;
			keyframe->time = keyframes[i].time;
			for (auto j = 0; j < 4; j++) {
				keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
				keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
				keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
			}
			m_keyframes.push_back(std::move(keyframe));
		}

		//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����B
		m_keyFramePtrListArray.resize(MAX_BONE);
		for (auto& keyframe : m_keyframes) {
			m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
			if (m_topBoneKeyFramList == nullptr) {
				m_topBoneKeyFramList = &m_keyFramePtrListArray[keyframe->boneIndex];
			}
		}
		m_loaded = true;
	}

#if BUILD_LEVEL!=BUILD_LEVEL_MASTER
	void CAnimationClip::Upconverte(const wchar_t* filePath)
	{
		auto fp = _wfopen(filePath, L"rb");
		//�t�@�C���T�C�Y�𒲂ׂ�B
		fseek(fp, 0, SEEK_END);
		auto file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		//�S���h�J�b�ƃR�s�[�B
		auto data = std::make_unique<char[]>(file_size);
		fread(&data[0], file_size, 1, fp);
		fclose(fp);

		//�������݃��[�h�ŊJ���B
		fp = _wfopen(filePath, L"wb");
		auto numKey = reinterpret_cast<int*>(&data[0]);
		//�擪4�o�C�g��`�����ށB
		fwrite(&data[0], 4, 1, fp);
		//�����ăA�j���[�V�����C�x���g����`�����ށB
		int numAnimEvent = 0;
		fwrite(&numAnimEvent, 4, 1, fp);
		//�c����������Ə������ށB
		fwrite(&data[4], file_size - 4, 1, fp);
		fclose(fp);
	}
#endif
}

