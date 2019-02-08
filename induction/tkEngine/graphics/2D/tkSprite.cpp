/*!
 * @brief	�X�v���C�g�B
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/2D/tkSprite.h"

namespace tkEngine{
	namespace {
		struct SSimpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	const CVector2	CSprite::DEFAULT_PIVOT = { 0.5f, 0.5f };
	CSprite::CSprite()
	{
	}
	CSprite::~CSprite()
	{
	}
	void CSprite::Init(CShaderResourceView& tex, float w, float h)
	{
		//�V�F�[�_�[���[�h�B
		m_ps.Load("shader/sprite.fx", "PSMain", CShader::EnType::PS);
		m_vs.Load("shader/sprite.fx", "VSMain", CShader::EnType::VS);
		m_size.x = w;
		m_size.y = h;
		float halfW = w * 0.5f;
		float halfH = h * 0.5f;
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-halfW, -halfH, 0.0f, 1.0f),
				CVector2(0.0f, 1.0f),
			},
			{
				CVector4(halfW, -halfH, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-halfW, halfH, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(halfW, halfH, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}

		};
		short indices[] = { 0,1,2,3 };
		
		m_primitive.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			CIndexBuffer::enIndexType_16,
			indices
		);
		m_textureSRV = &tex;
		m_cb.Create(nullptr, sizeof(SSpriteCB));
		m_isInited = true;
	}
	/*!
	*@brief	�X�V
	*@param[in]	trans		���s�ړ��B
	*@param[in]	rot			��]�B
	*@param[in]	scale		�g��B
	*/
	void CSprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
	{
		if (m_isInited == false) {
			//����������Ă��Ȃ��B
			return;
		}
		//�s�{�b�g���l���ɓ��ꂽ���s�ړ��s����쐬�B
		//�s�{�b�g�͐^�񒆂�0.0, 0.0�A���オ-1.0f, -1.0�A�E����1.0�A1.0�ɂȂ�悤�ɂ���B
		CVector2 localPivot = pivot;
		localPivot.x -= 0.5f;
		localPivot.y -= 0.5f;
		localPivot.x *= -2.0f;
		localPivot.y *= -2.0f;
		//�摜�̃n�[�t�T�C�Y�����߂�B
		CVector2 halfSize = m_size;
		halfSize.x *= 0.5f;
		halfSize.y *= 0.5f;
		CMatrix mPivotTrans;

		mPivotTrans.MakeTranslation(
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
		);
		CMatrix mTrans, mRot, mScale;
		mTrans.MakeTranslation(trans);
		mRot.MakeRotationFromQuaternion(rot);
		mScale.MakeScaling(scale);
		m_world = mPivotTrans * mScale;
		m_world = m_world * mRot;
		m_world = m_world * mTrans;

	}
	void CSprite::Draw(CRenderContext& rc, const CMatrix& viewMatrix, const CMatrix& projMatrix)
	{
		if (m_isInited == false) {
			//����������Ă��Ȃ��B
			return;
		}
		if (m_textureSRV == nullptr) {
			TK_WARNING("m_textureSRV is nullptr");
			return;
		}
		SSpriteCB cb;
		cb.WVP = m_world;
		cb.WVP = cb.WVP * viewMatrix;
		cb.WVP = cb.WVP * projMatrix;
		cb.mulColor = m_mulColor;

		rc.UpdateSubresource(m_cb, &cb);
		rc.VSSetConstantBuffer(0, m_cb);
		rc.PSSetConstantBuffer(0, m_cb);
		rc.PSSetShaderResource(0, *m_textureSRV);
		rc.PSSetShader(m_ps);
		rc.VSSetShader(m_vs);
		m_primitive.Draw(rc);
	}
}