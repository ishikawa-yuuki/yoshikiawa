/*!
 *@brief	AABB
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/math/tkAabb.h"

namespace tkEngine{
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CAabb::CAabb()
	{
		memset(m_vertexPosition, 0, sizeof(m_vertexPosition));
	}
	/*!
	 *@brief	�������B
	 */
	void CAabb::Init(const CVector3& centerPosition, const CVector3& halfSize)
	{
		Update(centerPosition, halfSize);
	}
	void CAabb::CalcVertexPosition()
	{
		//8���_�̍��W���v�Z�B
		m_vertexPosition[0] = m_centerPosition;
		m_vertexPosition[0].x -= m_halfSize.x;
		m_vertexPosition[0].y -= m_halfSize.y;
		m_vertexPosition[0].z -= m_halfSize.z;

		m_vertexPosition[1] = m_centerPosition;
		m_vertexPosition[1].x += m_halfSize.x;
		m_vertexPosition[1].y -= m_halfSize.y;
		m_vertexPosition[1].z -= m_halfSize.z;

		m_vertexPosition[2] = m_centerPosition;
		m_vertexPosition[2].x -= m_halfSize.x;
		m_vertexPosition[2].y += m_halfSize.y;
		m_vertexPosition[2].z -= m_halfSize.z;

		m_vertexPosition[3] = m_centerPosition;
		m_vertexPosition[3].x += m_halfSize.x;
		m_vertexPosition[3].y += m_halfSize.y;
		m_vertexPosition[3].z -= m_halfSize.z;

		m_vertexPosition[4] = m_centerPosition;
		m_vertexPosition[4].x -= m_halfSize.x;
		m_vertexPosition[4].y -= m_halfSize.y;
		m_vertexPosition[4].z += m_halfSize.z;

		m_vertexPosition[5] = m_centerPosition;
		m_vertexPosition[5].x += m_halfSize.x;
		m_vertexPosition[5].y -= m_halfSize.y;
		m_vertexPosition[5].z += m_halfSize.z;

		m_vertexPosition[6] = m_centerPosition;
		m_vertexPosition[6].x -= m_halfSize.x;
		m_vertexPosition[6].y += m_halfSize.y;
		m_vertexPosition[6].z += m_halfSize.z;

		m_vertexPosition[7] = m_centerPosition;
		m_vertexPosition[7].x += m_halfSize.x;
		m_vertexPosition[7].y += m_halfSize.y;
		m_vertexPosition[7].z += m_halfSize.z;
	}
	/*!
	 *@brief	�X�V�B
	 *@param[in]	centerPosition		���S���W�B
	 */
	void CAabb::Update( const CVector3& centerPosition, const CVector3& halfSize)
	{
		m_centerPosition = centerPosition;
		m_halfSize = halfSize;
		CalcVertexPosition();
	}
}