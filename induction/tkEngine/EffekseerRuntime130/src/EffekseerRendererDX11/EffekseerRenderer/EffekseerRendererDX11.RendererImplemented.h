﻿
#ifndef	__EFFEKSEERRENDERER_DX11_RENDERER_IMPLEMENTED_H__
#define	__EFFEKSEERRENDERER_DX11_RENDERER_IMPLEMENTED_H__

//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "EffekseerRendererDX11.Base.h"
#include "EffekseerRendererDX11.Renderer.h"
#include "../../EffekseerRendererCommon/EffekseerRenderer.RenderStateBase.h"
#include "../../EffekseerRendererCommon/EffekseerRenderer.StandardRenderer.h"

#ifdef _MSC_VER
#include <xmmintrin.h>
#endif

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerRendererDX11
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Vertex
{
	::Effekseer::Vector3D	Pos;
	uint8_t		Col[4];
	float		UV[2];

	void SetColor( const ::Effekseer::Color& color )
	{
		Col[0] = color.R;
		Col[1] = color.G;
		Col[2] = color.B;
		Col[3] = color.A;
	}
};

struct VertexDistortion
{
	::Effekseer::Vector3D	Pos;
	uint8_t		Col[4];
	float		UV[2];
	::Effekseer::Vector3D	Tangent;
	::Effekseer::Vector3D	Binormal;

	void SetColor(const ::Effekseer::Color& color)
	{
		Col[0] = color.R;
		Col[1] = color.G;
		Col[2] = color.B;
		Col[3] = color.A;
	}
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
inline void TransformVertexes( Vertex* vertexes, int32_t count, const ::Effekseer::Matrix43& mat )
{
	#if 1
		__m128 r0 = _mm_loadu_ps( mat.Value[0] );
		__m128 r1 = _mm_loadu_ps( mat.Value[1] );
		__m128 r2 = _mm_loadu_ps( mat.Value[2] );
		__m128 r3 = _mm_loadu_ps( mat.Value[3] );

		float tmp_out[4];
		::Effekseer::Vector3D* inout_prev;

		// １ループ目
		{
			::Effekseer::Vector3D* inout_cur = &vertexes[0].Pos;
			__m128 v = _mm_loadu_ps( (const float*)inout_cur );

			__m128 x = _mm_shuffle_ps( v, v, _MM_SHUFFLE(0,0,0,0) );
			__m128 a0 = _mm_mul_ps( r0, x );
			__m128 y = _mm_shuffle_ps( v, v, _MM_SHUFFLE(1,1,1,1) );
			__m128 a1 = _mm_mul_ps( r1, y );
			__m128 z = _mm_shuffle_ps( v, v, _MM_SHUFFLE(2,2,2,2) );
			__m128 a2 = _mm_mul_ps( r2, z );

			__m128 a01 = _mm_add_ps( a0, a1 );
			__m128 a23 = _mm_add_ps( a2, r3 );
			__m128 a = _mm_add_ps( a01, a23 );

			// 今回の結果をストアしておく
			_mm_storeu_ps( tmp_out, a );
			inout_prev = inout_cur;
		}

		for( int i = 1; i < count; i++ )
		{
			::Effekseer::Vector3D* inout_cur = &vertexes[i].Pos;
			__m128 v = _mm_loadu_ps( (const float*)inout_cur );

			__m128 x = _mm_shuffle_ps( v, v, _MM_SHUFFLE(0,0,0,0) );
			__m128 a0 = _mm_mul_ps( r0, x );
			__m128 y = _mm_shuffle_ps( v, v, _MM_SHUFFLE(1,1,1,1) );
			__m128 a1 = _mm_mul_ps( r1, y );
			__m128 z = _mm_shuffle_ps( v, v, _MM_SHUFFLE(2,2,2,2) );
			__m128 a2 = _mm_mul_ps( r2, z );

			__m128 a01 = _mm_add_ps( a0, a1 );
			__m128 a23 = _mm_add_ps( a2, r3 );
			__m128 a = _mm_add_ps( a01, a23 );

			// 直前のループの結果を書き込みます
			inout_prev->X = tmp_out[0];
			inout_prev->Y = tmp_out[1];
			inout_prev->Z = tmp_out[2];

			// 今回の結果をストアしておく
			_mm_storeu_ps( tmp_out, a );
			inout_prev = inout_cur;
		}

		// 最後のループの結果を書き込み
		{
			inout_prev->X = tmp_out[0];
			inout_prev->Y = tmp_out[1];
			inout_prev->Z = tmp_out[2];
		}

	#else
		for( int i = 0; i < count; i++ )
		{
			::Effekseer::Vector3D::Transform(
			vertexes[i].Pos,
			vertexes[i].Pos,
			mat );
		}
	#endif
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
inline void TransformVertexes(VertexDistortion* vertexes, int32_t count, const ::Effekseer::Matrix43& mat)
{
#if 1
	__m128 r0 = _mm_loadu_ps(mat.Value[0]);
	__m128 r1 = _mm_loadu_ps(mat.Value[1]);
	__m128 r2 = _mm_loadu_ps(mat.Value[2]);
	__m128 r3 = _mm_loadu_ps(mat.Value[3]);

	float tmp_out[4];
	::Effekseer::Vector3D* inout_prev;

	// １ループ目
	{
		::Effekseer::Vector3D* inout_cur = &vertexes[0].Pos;
		__m128 v = _mm_loadu_ps((const float*) inout_cur);

		__m128 x = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 a0 = _mm_mul_ps(r0, x);
		__m128 y = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 a1 = _mm_mul_ps(r1, y);
		__m128 z = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 a2 = _mm_mul_ps(r2, z);

		__m128 a01 = _mm_add_ps(a0, a1);
		__m128 a23 = _mm_add_ps(a2, r3);
		__m128 a = _mm_add_ps(a01, a23);

		// 今回の結果をストアしておく
		_mm_storeu_ps(tmp_out, a);
		inout_prev = inout_cur;
	}

	for (int i = 1; i < count; i++)
	{
		::Effekseer::Vector3D* inout_cur = &vertexes[i].Pos;
		__m128 v = _mm_loadu_ps((const float*) inout_cur);

		__m128 x = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 a0 = _mm_mul_ps(r0, x);
		__m128 y = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 a1 = _mm_mul_ps(r1, y);
		__m128 z = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 a2 = _mm_mul_ps(r2, z);

		__m128 a01 = _mm_add_ps(a0, a1);
		__m128 a23 = _mm_add_ps(a2, r3);
		__m128 a = _mm_add_ps(a01, a23);

		// 直前のループの結果を書き込みます
		inout_prev->X = tmp_out[0];
		inout_prev->Y = tmp_out[1];
		inout_prev->Z = tmp_out[2];

		// 今回の結果をストアしておく
		_mm_storeu_ps(tmp_out, a);
		inout_prev = inout_cur;
	}

	// 最後のループの結果を書き込み
		{
			inout_prev->X = tmp_out[0];
			inout_prev->Y = tmp_out[1];
			inout_prev->Z = tmp_out[2];
		}

#else
	for (int i = 0; i < count; i++)
	{
		::Effekseer::Vector3D::Transform(
			vertexes[i].Pos,
			vertexes[i].Pos,
			mat);
	}
#endif

	for (int i = 0; i < count; i++)
	{
		auto vs = &vertexes[i];

		::Effekseer::Vector3D::Transform(
			vs->Tangent,
			vs->Tangent,
			mat);

		::Effekseer::Vector3D::Transform(
			vs->Binormal,
			vs->Binormal,
			mat);

		Effekseer::Vector3D zero;
		::Effekseer::Vector3D::Transform(
			zero,
			zero,
			mat);

		::Effekseer::Vector3D::Normal(vs->Tangent, vs->Tangent - zero);
		::Effekseer::Vector3D::Normal(vs->Binormal, vs->Binormal - zero);
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
class OriginalState
{
private:
	ID3D11SamplerState*	m_samplers[4];

	ID3D11BlendState*	m_blendState;
	float				m_blendFactor[4];
	UINT				m_blendSampleMask;

	ID3D11DepthStencilState*	m_depthStencilState;
	UINT						m_depthStencilStateRef;

	ID3D11RasterizerState*		m_pRasterizerState;

	ID3D11Buffer*				m_vertexConstantBuffer;
	ID3D11Buffer*				m_pixelConstantBuffer;

	ID3D11VertexShader*			m_pVS;
	ID3D11PixelShader*			m_pPS;

	ID3D11InputLayout*			m_layout;
	D3D11_PRIMITIVE_TOPOLOGY	m_topology;

	ID3D11ShaderResourceView*	m_psSRVs[4];

	ID3D11Buffer*				m_pVB;
	UINT						m_vbStrides;
	UINT						m_vbOffset;

	ID3D11Buffer*				m_pIB;
	DXGI_FORMAT					m_ibFormat;
	UINT						m_ibOffset;

public:
	OriginalState();
	~OriginalState();
	void SaveState(ID3D11Device* device, ID3D11DeviceContext* context );
	void LoadState(ID3D11Device* device, ID3D11DeviceContext* context );
	void ReleaseState();
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
/**
	@brief	描画クラス
	@note
	ツール向けの描画機能。
*/
class RendererImplemented
	: public Renderer
	, public ::Effekseer::ReferenceObject
{
friend class DeviceObject;

private:
	ID3D11Device*			m_device;
	ID3D11DeviceContext*	m_context;
	ID3D11DeviceContext*	m_immidiateContext = nullptr;	//即時コンテキスト。
	VertexBuffer*		m_vertexBuffer;
	IndexBuffer*		m_indexBuffer;
	int32_t				m_squareMaxCount;

	Shader*							m_shader;
	Shader*							m_shader_no_texture;

	Shader*							m_shader_distortion;
	Shader*							m_shader_no_texture_distortion;

	EffekseerRenderer::StandardRenderer<RendererImplemented, Shader, Vertex, VertexDistortion>*	m_standardRenderer;

	::Effekseer::Vector3D	m_lightDirection;
	::Effekseer::Color		m_lightColor;
	::Effekseer::Color		m_lightAmbient;

	::Effekseer::Matrix44	m_proj;
	::Effekseer::Matrix44	m_camera;
	::Effekseer::Matrix44	m_cameraProj;

	// 座標系
	::Effekseer::CoordinateSystem			m_coordinateSystem;

	::EffekseerRenderer::RenderStateBase*	m_renderState;

	Effekseer::TextureData					m_background;

	std::set<DeviceObject*>	m_deviceObjects;

	// ステート
	OriginalState*	m_state;

	bool	m_restorationOfStates;

	D3D11_COMPARISON_FUNC	m_depthFunc;

	EffekseerRenderer::DistortingCallback* m_distortingCallback;

public:
	/**
		@brief	コンストラクタ
	*/
	RendererImplemented( int32_t squareMaxCount );

	/**
		@brief	デストラクタ
	*/
	~RendererImplemented();

	void OnLostDevice();
	void OnResetDevice();

	/**
		@brief	初期化
	*/
	bool Initialize(
		ID3D11Device* device, 
		ID3D11DeviceContext* context, 
		ID3D11DeviceContext* immidiateContext,
		D3D11_COMPARISON_FUNC depthFunc) ;

	void Destroy();

	void SetRestorationOfStatesFlag(bool flag);

	/**
		@brief	描画開始
	*/
	bool BeginRendering();

	/**
		@brief	描画終了
	*/
	bool EndRendering();

	/**
		@brief	デバイス取得
	*/
	ID3D11Device* GetDevice() ;

	/**
		@brief	コンテキスト取得
	*/
	ID3D11DeviceContext* GetContext();
	/**
		@brief	即時コンテキスト取得
	*/
	ID3D11DeviceContext* GetImmidiateContext()
	{
		return m_immidiateContext;
	}

	/**
		@brief	頂点バッファ取得
	*/
	VertexBuffer* GetVertexBuffer();

	/**
		@brief	インデックスバッファ取得
	*/
	IndexBuffer* GetIndexBuffer();

	/**
		@brief	最大描画スプライト数
	*/
	int32_t GetSquareMaxCount() const;

	::EffekseerRenderer::RenderStateBase* GetRenderState();

	/**
		@brief	ライトの方向を取得する。
	*/
	const ::Effekseer::Vector3D& GetLightDirection() const;

	/**
		@brief	ライトの方向を設定する。
	*/
	void SetLightDirection( ::Effekseer::Vector3D& direction );

	/**
		@brief	ライトの色を取得する。
	*/
	const ::Effekseer::Color& GetLightColor() const;

	/**
		@brief	ライトの色を設定する。
	*/
	void SetLightColor( ::Effekseer::Color& color );

	/**
		@brief	ライトの環境光の色を取得する。
	*/
	const ::Effekseer::Color& GetLightAmbientColor() const;

	/**
		@brief	ライトの環境光の色を設定する。
	*/
	void SetLightAmbientColor( ::Effekseer::Color& color );

	/**
		@brief	投影行列を取得する。
	*/
	const ::Effekseer::Matrix44& GetProjectionMatrix() const;

	/**
		@brief	投影行列を設定する。
	*/
	void SetProjectionMatrix( const ::Effekseer::Matrix44& mat );

	/**
		@brief	カメラ行列を取得する。
	*/
	const ::Effekseer::Matrix44& GetCameraMatrix() const;

	/**
		@brief	カメラ行列を設定する。
	*/
	void SetCameraMatrix( const ::Effekseer::Matrix44& mat );

	/**
		@brief	カメラプロジェクション行列を取得する。
	*/
	::Effekseer::Matrix44& GetCameraProjectionMatrix();

	/**
		@brief	スプライトレンダラーを生成する。
	*/
	::Effekseer::SpriteRenderer* CreateSpriteRenderer();

	/**
		@brief	リボンレンダラーを生成する。
	*/
	::Effekseer::RibbonRenderer* CreateRibbonRenderer();
	
	/**
		@brief	リングレンダラーを生成する。
	*/
	::Effekseer::RingRenderer* CreateRingRenderer();

	/**
		@brief	モデルレンダラーを生成する。
	*/
	::Effekseer::ModelRenderer* CreateModelRenderer();

	/**
		@brief	軌跡レンダラーを生成する。
	*/
	::Effekseer::TrackRenderer* CreateTrackRenderer();

	/**
		@brief	テクスチャ読込クラスを生成する。
	*/
	::Effekseer::TextureLoader* CreateTextureLoader( ::Effekseer::FileInterface* fileInterface = NULL );

	/**
		@brief	モデル読込クラスを生成する。
	*/
	::Effekseer::ModelLoader* CreateModelLoader( ::Effekseer::FileInterface* fileInterface = NULL );

	/**
	@brief	背景を取得する。
	*/
	Effekseer::TextureData* GetBackground() override { return &m_background; }

	/**
		@brief	背景を設定する。
	*/
	void SetBackground(ID3D11ShaderResourceView* background) override;

	EffekseerRenderer::DistortingCallback* GetDistortingCallback() override;

	void SetDistortingCallback(EffekseerRenderer::DistortingCallback* callback) override;

	EffekseerRenderer::StandardRenderer<RendererImplemented, Shader, Vertex, VertexDistortion>* GetStandardRenderer() { return m_standardRenderer; }

	void SetVertexBuffer( VertexBuffer* vertexBuffer, int32_t size );
	void SetVertexBuffer(ID3D11Buffer* vertexBuffer, int32_t size);
	void SetIndexBuffer( IndexBuffer* indexBuffer );
	void SetIndexBuffer(ID3D11Buffer* indexBuffer);

	void SetLayout( Shader* shader );
	void DrawSprites( int32_t spriteCount, int32_t vertexOffset );
	void DrawPolygon( int32_t vertexCount, int32_t indexCount);

	void BeginShader(Shader* shader);
	void EndShader(Shader* shader);

	void SetTextures(Shader* shader, Effekseer::TextureData** textures, int32_t count);

	void ResetRenderState();

	virtual int GetRef() { return ::Effekseer::ReferenceObject::GetRef(); }
	virtual int AddRef() { return ::Effekseer::ReferenceObject::AddRef(); }
	virtual int Release() { return ::Effekseer::ReferenceObject::Release(); }
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#endif	// __EFFEKSEERRENDERER_DX11_RENDERER_IMPLEMENTED_H__