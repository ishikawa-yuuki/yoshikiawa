
#pragma once

namespace tkEngine{
	class IHUDNode;
	using IHUDNodeWeakPtr = std::weak_ptr<IHUDNode>;
	using IHUDNodeSharedPtr = std::shared_ptr<IHUDNode>;
	/*!
	*@brief	HUD�̃m�[�h�̊��N���X�B
	*/
	class IHUDNode : Noncopyable{
	public:
		/*!
		 *@brief	�q����ǉ��B
		 */
		void AddChildren(IHUDNodeWeakPtr weakNode)
		{
			m_childrenNode.push_back(std::move(weakNode));
		}
		
		/*!
		*@brief	�m�[�h�̖��O��ǉ��B
		*/
		const wchar_t* GetName() const
		{
			return m_nameKey.GetName();
		}
		/*!
		*@brief	�m�[�h�̖��O�L�[��ǉ��B
		*/
		int GetNameKey() const
		{
			return m_nameKey.GetHashCode();
		}
		/*!
		* @brief	�q���ɑ΂��Ė₢���킹�B
		*@param[in]	func	�₢���킹�֐��B
		*/
		void QueryChildren(std::function< void(IHUDNode* node)> func) 
		{
			for (auto& child : m_childrenNode) {
				func(child.lock().get());
			}
		}
		/*!
		* @brief	�����œn�����m�[�h���̃I�u�W�F�N�g�����ׂ�B
		*@param[in]	objName		���ׂ閼�O�B
		*@return	���O�������ꍇ��true��Ԃ��܂��B
		*/
		bool EqualNodeName(const wchar_t* nodeName)
		{
			return wcscmp(m_nameKey.GetName(), nodeName) == 0;
		}
	public:
		IHUDNode(CBone* bone)  
		{
			m_nameKey.Init(bone->GetName());
		}
		virtual ~IHUDNode()
		{
		}
		virtual void Update() = 0;
		virtual void PostRender( CRenderContext& rc ) = 0;
		void UpdateWrapper()
		{
			//���[���h�s��̍X�V����������ׂ����ȁE�E�E�B
			Update();
			for (auto& child : m_childrenNode) {
				child.lock()->UpdateWrapper();
			}
		}
		void PostRenderWrapper(CRenderContext& rc)
		{
			PostRender(rc);
			for (auto& child : m_childrenNode) {
				child.lock()->PostRenderWrapper(rc);
			}
		}
		
	protected:
		IHUDNodeWeakPtr m_parentNode;
		std::vector<IHUDNodeWeakPtr>	m_childrenNode;		//�q���̃m�[�h�B
		WNameKey m_nameKey;									//���O�L�[�B
	};
	
}