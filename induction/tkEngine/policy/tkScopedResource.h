/*!
 * @brief	�X�R�[�v�𔲂����玩���I�ɊJ������郊�\�[�X�B
 */

#pragma once

namespace tkEngine{
	template<class T>
	class TScopedResource{
	private:
		
	public:
		
		T* res = nullptr;
		TScopedResource()
		{
		}
		//Move�R���X�g���N�^�B
		TScopedResource(TScopedResource&& a) :
			res(a.res)
		{
			a.res = nullptr;
		}
		//Move������Z�q�B
		TScopedResource& operator=(TScopedResource&& a)
		{
			if (this != &a) {
				res = a.res;
				a.res = nullptr;
			}
			return *this;
		}
		~TScopedResource()
		{
			if (res) {
				res->Release();
			}
		}
		
	};
}