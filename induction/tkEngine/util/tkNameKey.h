#pragma once

#include "tkEngine/Util/tkUtil.h"

namespace tkEngine {
	
	template<class T>
	class TNameKey {
		using MyString = std::basic_string<T, std::char_traits<T>, std::allocator<T>>;
		MyString m_name;			//!<���O
		unsigned int m_hashCode = 0;	//!<�n�b�V���l�B
	public:
		TNameKey(){}
		TNameKey( const T* name )
		{
			Init(name);
		}
		//�������B
		void Init(const T* name)
		{
			if (name != nullptr) {
				m_name = name;
				//���O���n�b�V���l�ɕϊ��B
				m_hashCode = CUtil::MakeHash(name);
			}
		}
		//�n�b�V���R�[�h���擾�B
		unsigned int GetHashCode() const
		{
			return m_hashCode;
		}
		//���O���擾�B
		const T* GetName() const
		{
			return m_name.c_str();
		}
	};

	using NameKey = TNameKey<char>;
	using WNameKey = TNameKey<wchar_t>;
}
