/*!
 * @brief	�s��B
 */

#ifndef _TKMATRIX_H_
#define _TKMATRIX_H_

#include "tkEngine/math/tkVector.h"

namespace tkEngine{
	/*!
	 * @brief	�s��B
	 */
	class CMatrix {
	public:

		union {
			DirectX::XMFLOAT4X4 mat;
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			CVector4 v[4];
			float m[4][4];
		};
		static const CMatrix Identity;	//!<�P�ʍs��B
	public:
		operator DirectX::XMMATRIX() const
		{
			return DirectX::XMLoadFloat4x4(&mat);
		}
		operator Effekseer::Matrix44() const
		{
			Effekseer::Matrix44 eMat = *((Effekseer::Matrix44*)&mat);
			return eMat;
		}
		operator Effekseer::Matrix43() const
		{
			Effekseer::Matrix43 eMat;
			eMat.Value[0][0] = mat.m[0][0];
			eMat.Value[0][1] = mat.m[0][1];
			eMat.Value[0][2] = mat.m[0][2];

			eMat.Value[1][0] = mat.m[1][0];
			eMat.Value[1][1] = mat.m[1][1];
			eMat.Value[1][2] = mat.m[1][2];

			eMat.Value[2][0] = mat.m[2][0];
			eMat.Value[2][1] = mat.m[2][1];
			eMat.Value[2][2] = mat.m[2][2];

			eMat.Value[3][0] = mat.m[3][0];
			eMat.Value[3][1] = mat.m[3][1];
			eMat.Value[3][2] = mat.m[3][2];

			return eMat;
		}
		CMatrix() {}
		CMatrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33) :
			mat(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33)
		{

		}
		CMatrix(const DirectX::XMFLOAT4X4& m)
		{
			mat = m;
		}
		/*!
		*@brief	������Z�q�B
		*/
		CMatrix& operator=(const CMatrix& _m)
		{
			mat = _m.mat;
			return *this;
		}
		/*!
		*@brief	�x�N�g����3x3�s��̏�Z
		*@param[in,out]		v	��Z�����x�N�g���B
		*/
		void Apply3x3(CVector3& vOut) const
		{
			CVector3 vTmp = vOut;
			vOut.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0];
			vOut.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1];
			vOut.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2];
		}
		/*!
		*@brief	�x�N�g���ɍs�����Z
		*@param[in,out]		v	��Z�����x�N�g���B
		*/
		void Apply(CVector3& vOut) const
		{
			DirectX::XMStoreFloat3(
				&vOut.vec,
				DirectX::XMVector3Transform(vOut, *this)
			);
		}
		void Apply(CVector4& vOut) const
		{
			DirectX::XMStoreFloat4(
				&vOut.vec,
				DirectX::XMVector4Transform(vOut, *this)
			);
		}
		[[deprecated("This function will be delete. please use Apply() function.")]]
		void Mul(CVector3& vOut) const
		{
			Apply(vOut);
		}
		[[deprecated("This function will be delete. please use Apply() function.")]]
		void Mul(CVector4& vOut) const
		{
			Apply(vOut);
		}
		/*!
		 *@brief	���s�ړ��s����쐬�B
		 */
		void MakeTranslation(const CVector3& trans)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixTranslationFromVector(trans)
			);
		}
		/*!
		*@brief	Y������̉�]�s����쐬�B
		*@param[in]	angle	��]�p�x(�P�ʃ��W�A��)
		*/
		void MakeRotationY(float angle)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixRotationY(angle)
			);
		}
		/*!
		*@brief	Z������̉�]�s����쐬�B
		*@param[in]	angle	��]�p�x(�P�ʃ��W�A��)
		*/
		void MakeRotationZ(float angle)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixRotationZ(angle)
			);
		}
		/*!
		*@brief	X������̉�]�s����쐬�B
		*@param[in]	angle	��]�p�x(�P�ʃ��W�A��)
		*/
		void MakeRotationX(float angle)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixRotationX(angle)
			);
		}
		/*!
		 *@brief	�N�H�[�^�j�I�������]�s����쐬�B
		 *@param[in]	q		�N�H�[�^�j�I��
		 */
		void MakeRotationFromQuaternion(const CQuaternion& q)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixRotationQuaternion(q)
			);
		}
		/*!
		*@brief	�C�ӂ̎�����̉�]�s����쐬�B
		*@param[in]	axis	��]���B
		*@param[in]	angle	��]�p�x
		*/
		void MakeRotationAxis(const CVector3& axis, float angle)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixRotationAxis(axis, angle)
			);
		}
		/*!
		*@brief	�g��s����쐬�B
		*@param[in] scale		�g�嗦�B
		*/
		void MakeScaling(const CVector3& scale)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixScalingFromVector(scale)
			);
		}
		/*!
		* @brief	�v���W�F�N�V�����s����쐬�B
		*@param[in]	viewAngle	��p�B(���W�A��)�B
		*@param[in]	aspect		�A�X�y�N�g��B
		*@param[in]	fNear		�ߕ��ʁB
		*@param[in]	fFar		�����ʁB
		*/
		void MakeProjectionMatrix(
			float viewAngle,
			float aspect,
			float fNear,
			float fFar
		)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixPerspectiveFovLH(viewAngle, aspect, fNear, fFar)
			);
		}
		/*!
		* @brief	���s���e�s����쐬�B
		*@param[in]	w			�r���[�{�����[���̕��B
		*@param[in]	h			�r���[�{�����[���̍����B
		*@param[in]	fNear		�ߕ��ʁB
		*@param[in]	fFar		�����ʁB
		*/
		void MakeOrthoProjectionMatrix(float w, float h, float fNear, float fFar)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixOrthographicLH(w, h, fNear, fFar)
			);
		}
		/*!
		 * @brief	�����_�A������A�J�����ʒu����J�����s����쐬�B
		 *@param[in]	position	�J�����ʒu�B
		 *@param[in]	target		�����_�B
		 *@param[in]	up			�J�����̏�����B
		 */
		void MakeLookAt(const CVector3& position, const CVector3& target, const CVector3& up)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixLookAtLH(position, target, up)
			);
		}
		/*!
		 *@brief	�s��ƍs��̏�Z
		 *@details
		 * *this = m0 * m1
		 */
		void Multiply(const CMatrix& m0, const CMatrix& m1)
		{
			DirectX::XMFLOAT4X4 lm;
			DirectX::XMStoreFloat4x4(
				&lm,
				DirectX::XMMatrixMultiply(m0, m1)
			);
			mat = lm;
		}
		[[deprecated("This function will be delete. please use Multiply() function.")]]
		void Mul(const CMatrix& m0, const CMatrix& m1)
		{
			Multiply(m0, m1);
		}
		/*!
		*@brief	�s��̑�����Z�q
		*@details
		* this = this * _m;
		*/
		const CMatrix& operator*=(const CMatrix& _m)
		{
			Multiply(*this, _m);
			return *this;
		}
		/*!
		 *@brief	�t�s����v�Z�B
		 *@param[in]	m	���ɂȂ�s��B
		 */
		void Inverse(const CMatrix& _m)
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixInverse(NULL, _m)
			);
		}
		void Inverse()
		{
			Inverse(*this);
		}
		void Transpose()
		{
			DirectX::XMStoreFloat4x4(
				&mat,
				DirectX::XMMatrixTranspose(*this)
			);
		}
		
	};
	/*!
	*@brief	�s�񓯎m�̏�Z�B
	*@details
	* ��Z�͍�����E�Ɍ������Ă������Ă����B
	*/
	static inline CMatrix operator*(const CMatrix& m1, const CMatrix m2)
	{
		CMatrix mRet;
		mRet.Multiply(m1, m2);
		return mRet;
	}

};
#endif // _TKMATRIX_H_