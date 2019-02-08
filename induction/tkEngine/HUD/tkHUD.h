/*!
*@brief	HUD
*@details
* HUD�AHead up display�̗��BHP�o�[�⑕���i�ȂǁA�C���Q�[������
* �\�������2D�̂��Ƃ�HUD�ƌĂԁB
*/
#pragma once

#include "tkEngine/HUD/tkIHUDNode.h"
#include "tkEngine/util/tkUtil.h"

namespace tkEngine {
	static const wchar_t* HUD_FONT_NODE_NAME_PREFIX = L"font_";										//HUD�V�X�e����font�m�[�h�̖��O�̃v���t�B�b�N�X�B
	static const size_t HUD_FONT_NODE_NAME_PREFIX_LENGTH = wcslen(HUD_FONT_NODE_NAME_PREFIX);		//HUD�V�X�e����font�m�[�h�̖��O�̃v���t�B�b�N�X�̒����B
	static const wchar_t* HUD_SPRITE_NODE_NAME_PREFIX = L"sprite_";									//HUD�V�X�e����sprite�m�[�h�̖��O�̃v���t�B�b�N�X�B
	static const size_t HUD_SPRITE_NODE_NAME_PREFIX_LENGTH = wcslen(HUD_SPRITE_NODE_NAME_PREFIX);	//HUD�V�X�e����sprite�m�[�h�̖��O�̃v���t�B�b�N�X�̒����B
	class CHUDNode_Font;
	namespace prefab {
		/*!
		*@brief	HUD
		*@details
		* HUD�AHead up display�̗��BHP�o�[�⑕���i�ȂǁA�C���Q�[������
		* �\�������2D�̂��Ƃ�HUD�ƌĂԁB
		*/
		class CHud : public IGameObject {
		public:
			/*!
			 *@brief	�������B
			 *@param[in]	filePath	HUD�f�[�^�̃t�@�C���p�X�B
			 */
			void Init(const wchar_t* filePath);
			/*!
			 *@brief	Update���Ă΂�钼�O�ň�񂾂��Ă΂��֐��B
			 *			GameObjectManager���玩���I�ɌĂ΂��̂ŁA
			 *			�����I�ɌĂяo���K�v�͂Ȃ��B
			 */
			bool Start() override;
			/*!
			 *@brief	���t���[���Ă΂��֐��B
			 *			GameObjectManager���玩���I�ɌĂ΂��̂ŁA
			 *			�����I�ɌĂяo���K�v�͂Ȃ��B
			 */
			void Update() override;
			/*!
			*@brief	Render�֐������s���ꂽ��ŌĂ΂��x���`�揈��
			*			GameObjectManager���玩���I�ɌĂ΂��̂ŁA
			*			�����I�ɌĂяo���K�v�͂Ȃ��B
			*/
			void PostRender(CRenderContext& rc) override;
			/*!
			*@brief	�m�[�h�������B
			*@param[in]		name		�����������m�[�h�̖��O�B
			*@return	���������m�[�h�̎�Q�ƁB
			*/
			IHUDNode* FindNode(const wchar_t* name);
			/*!
			*@brief	�m�[�h�������B
			*@param[in]		nameKey		�����������m�[�h�̖��O�L�[�B
			*@return	���������m�[�h�̎�Q�ƁB
			*/
			IHUDNode* FindNode(int nameKey);
			/*!
			*@brief	�t�H���g�m�[�h�ɑ΂��ăN�G�������s�B
			*@param[in]		queryFunc	�t�H���g�m�[�h�ւ̖₢���킹�֐��B
			*/
			void QueryFontNode(std::function< void(CHUDNode_Font& font) > queryFunc);
		private:
			
			IHUDNodeSharedPtr m_rootNode;	//���[�g�m�[�h�B
			std::vector<IHUDNodeSharedPtr>	m_nodes;		//�m�[�h�̃��X�g�B
		};
	}
}