	/*!
 * @brief	�x�N�g��
 */

#ifndef _TKVECTOR_H_
#define _TKVECTOR_H_


namespace tkEngine{
	class CMatrix;
	
	class CVector2 {
	public:
		static const CVector2 Zero;
		CVector2()
		{

		}
		CVector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		/*!
		*@brief	������Z�q�B
		*/
		CVector2& operator=(const CVector2& _v)
		{
			vec = _v.vec;
			return *this;
		}
		union {
			DirectX::XMFLOAT2 vec;
			struct { float x, y; };
			float v[2];
		};
		/*!
		* @brief	���`��ԁB
		*@details
		* this = v0 + (v1-v0) * t;
		*/
		void Lerp(float t, const CVector2& v0, const CVector2& v1)
		{
			x = v0.x + (v1.x - v0.x) * t;
			y = v0.y + (v1.y - v0.y) * t;
		}
	};
	/*!
	 * @brief	�x�N�g���B
	 */
	class CVector3{
	public:
		union{
			DirectX::XMFLOAT3 vec;
			float v[3];
			struct { float x, y, z; };
		};
		static const CVector3 Zero;
		static const CVector3 Right;
		static const CVector3 Left;
		static const CVector3 Up;
		static const CVector3 Down;
		static const CVector3 Front;
		static const CVector3 Back;
		static const CVector3 AxisX;
		static const CVector3 AxisY;
		static const CVector3 AxisZ;
		static const CVector3 One;
	public:
		//XMVECTOR�ւ̈Öق̕ϊ��B
		operator DirectX::XMVECTOR() const
		{
			return DirectX::XMLoadFloat3(&vec);
		}
		//operator D3DXVECTOR3(void) { return s_cast<D3DXVECTOR3>(*this); }
		/*!
		*@brief	������Z�q�B
		*/
		CVector3& operator=(const CVector3& _v)
		{
			vec = _v.vec;
			return *this;
		}
		CVector3() 
		{
			x = y = z = 0.0f;
		}
		/*!
		* @brief	�R���X�g���N�^�B
		*/
		CVector3(float x, float y, float z)
		{
			Set(x, y, z);
		}
		/*!
		* @brief	���`��ԁB
		*@details
		* this = v0 + (v1-v0) * t;
		*/
		void Lerp(float t, const CVector3& v0, const CVector3& v1)
		{
			DirectX::XMVECTOR _v = DirectX::XMVectorLerp(
				DirectX::XMLoadFloat3(&v0.vec),
				DirectX::XMLoadFloat3(&v1.vec),
				t);
			DirectX::XMStoreFloat3(&vec, _v);
		}
		template<class TVector>
		void CopyTo(TVector& dst) const
		{
			dst.x = x;
			dst.y = y;
			dst.z = z;
		}
		template<>
		void CopyTo(btVector3& dst) const
		{
			dst.setX(x);
			dst.setY(y);
			dst.setZ(z);
		}
		/*!
		* @brief	�x�N�g���̊e�v�f��ݒ�B
		*/
		void Set(float _x, float _y, float _z)
		{
			vec.x = _x;
			vec.y = _y;
			vec.z = _z;
		}
		template<class TVector>
		void Set(TVector& _v)
		{
			Set(_v.x, _v.y, _v.z);
		}
		void Set(btVector3& _v)
		{
			this->x = _v.x();
			this->y = _v.y();
			this->z = _v.z();
		}
		
		/*!
		 * @brief	�x�N�g�������Z�B
		 */
		void Add( const CVector3& _v) 
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&_v.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorAdd(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		void Add( const CVector3& v0, const CVector3& v1 )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&v0.vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&v1.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorAdd(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		/*!
		 * @brief	�x�N�g�������Z�B
		 */
		void Subtract( const CVector3& _v )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&_v.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorSubtract(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		void Subtract( const CVector3& v0, const CVector3& v1 )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&v0.vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&v1.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorSubtract(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		/*!
		 * @brief	���ρB
		 */
		float Dot( const CVector3& _v ) const
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&_v.vec);
			return DirectX::XMVector3Dot(xmv0, xmv1).m128_f32[0];
		}
		/*!
		 * @brief	�O�ρB
		 */
		void Cross(const CVector3& _v)
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&_v.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVector3Cross(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		void Cross(const CVector3& v0, const CVector3& v1)
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&v0.vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&v1.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVector3Cross(xmv0, xmv1);
			DirectX::XMStoreFloat3(&vec, xmvr);
		}
		/*!
		 * @brief	�������擾
		 */
		float Length() const
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat3(&vec);
			return DirectX::XMVector3Length(xmv).m128_f32[0];
		}
		/*!
		 * @brief	�����̓����擾
		 */
		float LengthSq() const
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat3(&vec);
			return DirectX::XMVector3LengthSq(xmv).m128_f32[0];
		}
		/*!
		* @brief	�g��B
		*/
		void Scale(float s)
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat3(&vec);
			xmv = DirectX::XMVectorScale(xmv, s);
			DirectX::XMStoreFloat3(&vec, xmv);
		}
		/*!
		* @brief	�@���𐳋K���B
		*/
		void Normalize()
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat3(&vec);
			xmv = DirectX::XMVector3Normalize(xmv);
			DirectX::XMStoreFloat3(&vec, xmv);
		}
		/*!
		* @brief	���Z�B
		*/
		void Div(float d)
		{
			float scale = 1.0f / d;
			Scale(scale);
		}
		/*!
		* @brief	�ő�l��ݒ�B
		*/
		void Max(const CVector3& vMax)
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&vMax.vec);
			DirectX::XMStoreFloat3(&vec,  DirectX::XMVectorMax(xmv0, xmv1));
		}
		/*!
		* @brief	�ŏ��l��ݒ�B
		*/
		void Min(const CVector3& vMin)
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat3(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat3(&vMin.vec);
			DirectX::XMStoreFloat3(&vec, DirectX::XMVectorMin(xmv0, xmv1));
		}
		/*!
		 *@brief	���Z������Z�q�B
		 */
		const CVector3& operator+=(const CVector3& _v)
		{
			Add(_v);
			return *this;
		}
		/*!
		*@brief�@��Z������Z�q�B
		*/
		const CVector3& operator*=(float s) 
		{
			Scale(s);
			return *this;
		}
		/*!
		*@brief	���Z������Z�q�B
		*/
		const CVector3& operator-=(const CVector3& _v)
		{
			Subtract(_v);
			return *this;
		}
		/*!
		 *@brief	���Z������Z�q�B
		 */
		const CVector3& operator/=(const float s)
		{
			Div(s);
			return *this;
		}
	};
	/*!
	 *@brief	4�v�f�̃x�N�g���N���X�B
	 */
	class CVector4{
	public:
		union{
			DirectX::XMFLOAT4 vec;
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float v[4];
		};
		static const CVector4 White;
		static const CVector4 Black;
		static const CVector4 Gray;
		static const CVector4 Yellow;
	public:
		operator DirectX::XMVECTOR() const
		{
			return DirectX::XMLoadFloat4(&vec);
		}
		CVector4()
		{
			x = y = z = w = 0.0f;
		}
		template<class TVector4>
		void CopyTo(TVector4& dst) const
		{
			dst.x = x;
			dst.y = y;
			dst.z = z;
			dst.w = w;
		}
		template<>
		void CopyTo(btQuaternion& dst) const
		{
			dst.setX(x);
			dst.setY(y);
			dst.setZ(z);
			dst.setW(w);
		}
		/*!
		*@brief	������Z�q�B
		*/
		CVector4& operator=(const CVector4& _v)
		{
			vec = _v.vec;
			return *this;
		}
		/*!
		 *@brief	�R���X�g���N�^
		 */
		CVector4(float x, float y, float z, float w)
		{
			Set(x, y, z, w);
		}
		/*!
		*@brief	�R���X�g���N�^
		*@details
		* w�ɂ�1.0���i�[����܂��B
		*/
		CVector4(const CVector3& v)
		{
			Set(v);
		}
		/*!
		 *@brief	�x�N�g���̊e�v�f��ݒ�B
		 */
		void Set(float _x, float _y, float _z, float _w)
		{
			this->x = _x;
			this->y = _y;
			this->z = _z;
			this->w = _w;
		}
		/*!
		* @brief	�@���𐳋K���B
		*/
		void Normalize()
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat4(&vec);
			xmv = DirectX::XMVector4Normalize(xmv);
			DirectX::XMStoreFloat4(&vec, xmv);
		}
		/*!
		*@brief	�x�N�g����ݒ�B
		*/
		void Set(const CVector4& _v)
		{
			*this = _v;
		}
		/*!
		*@brief	�x�N�g����ݒ�B
		*@details
		* w�ɂ�1.0���i�[����܂��B
		*/
		
		void Set(const CVector3& _v)
		{
			this->x = _v.x;
			this->y = _v.y;
			this->z = _v.z;
			this->w = 1.0f;
		}
		/*!
		 *@brief	�x�N�g�������Z�B
		 */
		void Add( const CVector4& _v )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat4(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat4(&_v.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorAdd(xmv0, xmv1);
			DirectX::XMStoreFloat4(&vec, xmvr);
		}
		void Add( const CVector4& v0, const CVector4& v1 )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat4(&v0.vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat4(&v1.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorAdd(xmv0, xmv1);
			DirectX::XMStoreFloat4(&vec, xmvr);
		}
		/*!
		 *@brief	�x�N�g�������Z�B
		 */
		void Subtract( const CVector4& _v )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat4(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat4(&_v.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorSubtract(xmv0, xmv1);
			DirectX::XMStoreFloat4(&vec, xmvr);
		}
		void Subtract( const CVector4& v0, const CVector4& v1 )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat4(&v0.vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat4(&v1.vec);
			DirectX::XMVECTOR xmvr = DirectX::XMVectorSubtract(xmv0, xmv1);
			DirectX::XMStoreFloat4(&vec, xmvr);
		}
		/*!
		 *@brief	����
		 */
		float Dot( const CVector4& _v )
		{
			DirectX::XMVECTOR xmv0 = DirectX::XMLoadFloat4(&vec);
			DirectX::XMVECTOR xmv1 = DirectX::XMLoadFloat4(&_v.vec);
			return DirectX::XMVector4Dot(xmv0, xmv1).m128_f32[0];
		}
		/*!
		 * @brief	�������擾
		 */
		float Length()
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat4(&vec);
			return DirectX::XMVector4Length(xmv).m128_f32[0];
		}
		/*!
		 * @brief	�����̓����擾
		 */
		float LengthSq()
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat4(&vec);
			return DirectX::XMVector4LengthSq(xmv).m128_f32[0];
		}
		/*!
		* @brief	�g��B
		*/
		void Scale(float s)
		{
			DirectX::XMVECTOR xmv = DirectX::XMLoadFloat4(&vec);
			xmv = DirectX::XMVectorScale(xmv, s);
			DirectX::XMStoreFloat4(&vec, xmv);
		}
	};
	
	class CQuaternion : public CVector4{
	public:
		static const CQuaternion Identity;		//!<�P�ʃN�H�[�^�j�I���B
		CQuaternion() 
		{
			x = y = z = 0.0f;
			w = 1.0f;
		}
		CQuaternion(float x, float y, float z, float w) :
			CVector4(x, y, z, w)
		{
		}
		
		/*!
		 *@brief	�C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
		 */
		void SetRotation( const CVector3& axis, float angle )
		{
			float s;
			float halfAngle = angle * 0.5f;
			s = sin(halfAngle);
			w = cos(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
		}
		void SetRotationDeg(const CVector3& axis, float angle)
		{
			float s;
			float halfAngle = CMath::DegToRad(angle) * 0.5f;
			s = sin(halfAngle);
			w = cos(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
		}
		void Set(const btQuaternion& rot)
		{
			x = rot.x();
			y = rot.y();
			z = rot.z();
			w = rot.w();
		}
		/*!
		*@brief	�s�񂩂�N�H�[�^�j�I�����쐬�B
		*/
		void SetRotation(const CMatrix& m);
		/*!
		*@brief	from�x�N�g������to�x�N�g���ɉ�]������N�H�[�^�j�I�����쐬�B
		*/
		void SetRotation( CVector3 from,  CVector3 to);
	
		/*!
		 *@brief	���ʐ��`�⊮�B
		 */
		void Slerp(float t, CQuaternion q1, CQuaternion q2)
		{
			DirectX::XMVECTOR xmv = DirectX::XMQuaternionSlerp(
				DirectX::XMLoadFloat4(&q1.vec),
				DirectX::XMLoadFloat4(&q2.vec),
				t
			);
			DirectX::XMStoreFloat4(&vec, xmv);
		}
		/*!
		*@brief	�N�H�[�^�j�I�����m�̐ρB
		* �������͏�Z�̏��Ԃ����w��B
		* �E���獶�Ɍ������ď�Z����Ă����B
		* �����A�������͒��ϓI�ɕ�����ɂ����̂Ŕ񐄏��B
		* operator*���g������������₷���ł��B
		*/
		void Multiply(const CQuaternion& rot)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			qw = w; qx = x; qy = y; qz = z;
			pw = rot.w; px = rot.x; py = rot.y; pz = rot.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;

		}
		
		/*!
		 *@brief	�N�H�[�^�j�I�����m�̏�Z�B
		 * �������͏�Z�̏��Ԃ����w��B
		 * �E���獶�Ɍ������ď�Z����Ă����B
		 * �����A�������͒��ϓI�ɕ�����ɂ����̂Ŕ񐄏��B
		 * operator*���g������������₷���ł��B
		 *@details
		 * this = rot0 * rot1;
		 */
		void Multiply(const CQuaternion& rot0, const CQuaternion& rot1)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			qw = rot0.w; qx = rot0.x; qy = rot0.y; qz = rot0.z;
			pw = rot1.w; px = rot1.x; py = rot1.y; pz = rot1.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}
		/*!
		*@brief	�N�H�[�^�j�I��������Z�q
		* ������̏�Z���Ԃ͍s��Ɠ����ɂȂ�B
		* ���������g���������ϓI�ɕ�����₷���͂��B
		*@details
		* this = rot0 * rot1;
		*/
		const CQuaternion& operator*=(const CQuaternion& rot0)
		{
			Multiply(rot0, *this);
			return *this;
		}
		/*!
		*@brief	�x�N�g���ɃN�H�[�^�j�I����K�p����B
		*@param[in,out] v	�x�N�g���B
		*/
		void Apply(CVector4& _v)
		{
			DirectX::XMVECTOR xmv = DirectX::XMVector3Rotate(_v, *this);
			DirectX::XMStoreFloat4(&_v.vec, xmv);
		}
		void Apply(CVector3& _v)
		{
			DirectX::XMVECTOR xmv = DirectX::XMVector3Rotate(_v, *this);
			DirectX::XMStoreFloat3(&_v.vec, xmv);
		}
		[[deprecated("This function will be delete. please use Apply() function.")]]
		void Multiply(CVector4& _v)
		{
			Apply(_v);
		}
		[[deprecated("This function will be delete. please use Apply() function.")]]
		void Multiply(CVector3& _v)
		{
			Apply(_v);
		}
	};
	
	//�����^�̃x�N�g���N���X�B
	__declspec(align(16)) class CVector4i {
	public:
		union {
			struct { int x, y, z, w; };
			int v[4];
		};
	};
	/*!
	*@brief	�x�N�g�����m�̉��Z�B
	*/
	template<class TVector>
	static inline TVector operator+(const TVector& v0, const TVector& v1)
	{
		TVector result;
		result.Add(v0, v1);
		return result;
	}
	/*!
	*@brief	�x�N�g���̃X�P�[���{�B
	*/
	template<class TVector>
	static inline TVector operator*(const TVector& v, float s)
	{
		TVector result;
		result = v;
		result.Scale(s);
		return result;
	}
	/*!
	*@brief	�x�N�g���̏��Z�B
	*/
	template<class TVector>
	static inline TVector operator/(const TVector& v, float s)
	{
		TVector result;
		result = v;
		result.Div(s);
		return result;
	}
	/*!
	*@brief	�x�N�g�����m�̌��Z�B
	*/
	template<class TVector>
	static inline TVector operator-(const TVector& v0, const TVector& v1)
	{
		TVector result;
		result.Subtract(v0, v1);
		return result;
	}
	/*!
	*@brief	�x�N�g�����m�̊O�ρB
	*/
	template< class TVector> 
	static inline TVector Cross(const TVector& v0, const TVector& v1)
	{
		TVector result;
		result.Cross(v0, v1);
		return result;
	}
	/*!
	*@brief	�x�N�g�����m�̓��ρB
	*/
	template< class TVector>
	static inline float Dot(const TVector& v0, const TVector& v1)
	{
		return v0.Dot(v1);
	}
	/*!
	*@brief	�N�H�[�^�j�I�����m�̏�Z�B
	*@details
	* ��Z�͍�����E�Ɍ������Ă������Ă����B
	*/
	static inline CQuaternion operator*(const CQuaternion& q1, const CQuaternion q2)
	{
		CQuaternion qRet;
		qRet.Multiply(q2, q1);
		return qRet;
	}
}


#endif // _TKVECTOR_H_