/*!
 * @brief	�R���C�_�[�B
 */

#pragma once

class btCollisionShape;
namespace tkEngine{
	/*!
	 * @brief	�R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
	 */
	class ICollider {
	public:
		virtual btCollisionShape* GetBody() const = 0;
	};
}