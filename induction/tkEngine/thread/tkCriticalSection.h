/*!
 * @brief	�N���e�B�J���Z�N�V�����B
 */

#pragma once

#include <mutex>

namespace tkEngine{
	/*!
	 * @brief	�N���e�B�J���Z�N�V�����B
	 * @details
	 *  �ē��\�N���e�B�J���Z�N�V�����ł��B
	 */
	class CCriticalSection{
	public:
		bool TryLock()
		{
			bool isLock = true;
			std::thread::id thisThreadID = std::this_thread::get_id();
			if (thisThreadID != m_lockThreadId) {
				//���b�N���s���Ă���X���b�h�ƌ��݂̃X���b�h���Ⴄ�B
				//���b�N�o���邩�����B
				if (m_mutex.try_lock()) {
					isLock = true;
				}
			}
			else {
				//�ē����b�N�B
				isLock = true;
			}
			if (isLock) {
				//���b�N�ł����B
				m_lockThreadId = std::this_thread::get_id();
				m_lockCount++;
			}
			return isLock;
		}
		void Lock()
		{
			//���b�N�����Ȃ������B
			std::thread::id thisThreadID = std::this_thread::get_id();
			if (thisThreadID != m_lockThreadId) {
				//���b�N���s���Ă���X���b�h�ƌ��݂̃X���b�h���Ⴄ�B
				//���b�N������܂ŐQ��B
				m_mutex.lock();
			}
			//���b�N�擾�ł����B
			m_lockThreadId = std::this_thread::get_id();
			m_lockCount++;
		}

		void Unlock()
		{
			m_lockCount--;
			if (m_lockCount == 0) {
				//�A�����b�N�B
				m_lockThreadId = std::thread::id();
				m_mutex.unlock();
			}
		}
	private:
		std::mutex		m_mutex;
		std::mutex		m_lockThreadIdMutex;	//lockThreadId��r���������邽�߂̃~���[�e�b�N�X
		std::thread::id m_lockThreadId;			//���b�N���Ă���X���b�h��ID
		int				m_lockCount = 0;		//���b�N�J�E���g�B
	};
}