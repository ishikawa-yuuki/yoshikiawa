/*!
 *@brief	AABB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/math/tkBox.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CBox::CBox()
	{
		memset(m_vertexPosition, 0, sizeof(m_vertexPosition));
	}
	/*!
	 *@brief	�������B
	 */
	void CBox::Init(const CVector3& halfSize)
	{
		m_halfSize = halfSize;
	}

	/*!
	 *@brief	�X�V�B
	 *@param[in]	worldMatrix		���[���h�s��B
	 */
	void CBox::Update( const CMatrix& worldMatrix )
	{
		//8���_�̍��W���v�Z�B
		m_vertexPosition[0] = CVector3::Zero;
		m_vertexPosition[0].x -= m_halfSize.x;
		m_vertexPosition[0].y -= m_halfSize.y;
		m_vertexPosition[0].z -= m_halfSize.z;

		m_vertexPosition[1] = CVector3::Zero;
		m_vertexPosition[1].x += m_halfSize.x;
		m_vertexPosition[1].y -= m_halfSize.y;
		m_vertexPosition[1].z -= m_halfSize.z;

		m_vertexPosition[2] = CVector3::Zero;
		m_vertexPosition[2].x -= m_halfSize.x;
		m_vertexPosition[2].y += m_halfSize.y;
		m_vertexPosition[2].z -= m_halfSize.z;

		m_vertexPosition[3] = CVector3::Zero;
		m_vertexPosition[3].x += m_halfSize.x;
		m_vertexPosition[3].y += m_halfSize.y;
		m_vertexPosition[3].z -= m_halfSize.z;

		m_vertexPosition[4] = CVector3::Zero;
		m_vertexPosition[4].x -= m_halfSize.x;
		m_vertexPosition[4].y -= m_halfSize.y;
		m_vertexPosition[4].z += m_halfSize.z;

		m_vertexPosition[5] = CVector3::Zero;
		m_vertexPosition[5].x += m_halfSize.x;
		m_vertexPosition[5].y -= m_halfSize.y;
		m_vertexPosition[5].z += m_halfSize.z;

		m_vertexPosition[6] = CVector3::Zero;
		m_vertexPosition[6].x -= m_halfSize.x;
		m_vertexPosition[6].y += m_halfSize.y;
		m_vertexPosition[6].z += m_halfSize.z;

		m_vertexPosition[7] = CVector3::Zero;
		m_vertexPosition[7].x += m_halfSize.x;
		m_vertexPosition[7].y += m_halfSize.y;
		m_vertexPosition[7].z += m_halfSize.z;
		
		for( auto& pos : m_vertexPosition ){
			worldMatrix.Apply(pos);
		}
	}
}