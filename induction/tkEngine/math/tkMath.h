/*!
 * @brief	���w�֌W�F�X�B
 */

#ifndef _TK_MATH_H_
#define _TK_MATH_H_

namespace tkEngine{
	class CMath{
	public:
		static constexpr float PI = 3.14159265358979323846f;
		static constexpr float PI2 = PI * 2.0f;
		/*!
		 * @brief	degree����radian�ɕϊ��B
		 */
		constexpr static inline float DegToRad( float deg )
		{
			return deg * (PI/180.0f);
		}
		/*!
		 * @brief	radian����degree�ɕϊ��B
		 */
		constexpr static inline float RadToDeg( float rad )
		{
			return rad / (PI/180.0f);
		}
		/*!
		 *@brief	t0��t1�Ԃ���`�⊮�B
		 *@details
		 *  ret = t0 + (t1-t0) + rate;
		 *@param[in]	t		��ԗ�	0.0�`1.0
		 */
		
		template<class T>
		static inline T Lerp(float rate, T t0, T t1)
		{
			T ret;
			ret.Lerp(rate, t0, t1);
			return ret;
		}
		template<>
		static inline float Lerp(float rate, float t0, float t1)
		{
			return t0 + (t1 - t0)*rate;
		}
	};
}

#endif //_TK_MATH_H_