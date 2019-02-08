﻿
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include "EffekseerRendererDX11.Shader.h"
#include "EffekseerRendererDX11.RendererImplemented.h"

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace EffekseerRendererDX11
{
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Shader::Shader(
		RendererImplemented* renderer,
		ID3D11VertexShader* vertexShader,
		ID3D11PixelShader* pixelShader,
		ID3D11InputLayout* vertexDeclaration )
	: DeviceObject			( renderer )
	, m_vertexShader		( vertexShader )
	, m_pixelShader			( pixelShader )
	, m_vertexDeclaration	( vertexDeclaration )
	, m_constantBufferToVS	( NULL )
	, m_constantBufferToPS	( NULL )
	, m_vertexConstantBuffer(NULL)
	, m_pixelConstantBuffer(NULL)
	, m_vertexRegisterCount(0)
	, m_pixelRegisterCount(0)
{
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Shader::~Shader()
{
	ES_SAFE_RELEASE( m_vertexShader );
	ES_SAFE_RELEASE( m_pixelShader );
	ES_SAFE_RELEASE( m_vertexDeclaration );
	ES_SAFE_RELEASE( m_constantBufferToVS );
	ES_SAFE_RELEASE( m_constantBufferToPS );

	ES_SAFE_DELETE_ARRAY(m_vertexConstantBuffer);
	ES_SAFE_DELETE_ARRAY(m_pixelConstantBuffer);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
Shader* Shader::Create(
	RendererImplemented* renderer, 
		const uint8_t vertexShader[], 
		int32_t vertexShaderSize,
		const uint8_t pixelShader[], 
		int32_t pixelShaderSize,
		const char* name, 
		const D3D11_INPUT_ELEMENT_DESC decl[],
		int32_t layoutCount )
{
	assert( renderer != NULL );
	assert( renderer->GetDevice() != NULL );

	HRESULT hr;

	ID3D11VertexShader* vs = NULL;
	ID3D11PixelShader* ps = NULL;

	hr = renderer->GetDevice()->CreateVertexShader(
		vertexShader,
		vertexShaderSize,
		NULL,
		&vs);

	if( FAILED(hr) )
	{
		printf( "* %s Error\n", name );
		return NULL;
	}

	hr = renderer->GetDevice()->CreatePixelShader(
		(const DWORD*)pixelShader,
		pixelShaderSize,
		NULL,
		&ps);

	if( FAILED(hr) )
	{
		printf( "* %s Error\n", name );
		return NULL;
	}

	ID3D11InputLayout* vertexDeclaration = NULL;

	hr = renderer->GetDevice()->CreateInputLayout(
		decl, 
		layoutCount, 
		vertexShader,
		vertexShaderSize, &vertexDeclaration);
	
	if( FAILED(hr) )
	{
		printf( "* %s Error\n", name );
		return NULL;
	}

	return new Shader( renderer, vs, ps, vertexDeclaration );
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Shader::OnLostDevice()
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void Shader::OnResetDevice()
{
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void Shader::SetVertexConstantBufferSize(int32_t size)
{
	ES_SAFE_DELETE_ARRAY(m_vertexConstantBuffer);
	m_vertexConstantBuffer = new uint8_t[size];

	D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.ByteWidth = size;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

	GetRenderer()->GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_constantBufferToVS);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void Shader::SetPixelConstantBufferSize(int32_t size)
{
	ES_SAFE_DELETE_ARRAY(m_pixelConstantBuffer);
	m_pixelConstantBuffer = new uint8_t[size];

	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = size;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	GetRenderer()->GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_constantBufferToPS);
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void Shader::SetConstantBuffer()
{
	if (m_vertexRegisterCount > 0)
	{
		GetRenderer()->GetContext()->UpdateSubresource( m_constantBufferToVS, 0, NULL, m_vertexConstantBuffer, 0, 0 );
		GetRenderer()->GetContext()->VSSetConstantBuffers(0, 1, &m_constantBufferToVS);
	}

	if (m_pixelRegisterCount > 0)
	{
		GetRenderer()->GetContext()->UpdateSubresource( m_constantBufferToPS, 0, NULL, m_pixelConstantBuffer, 0, 0 );
		GetRenderer()->GetContext()->PSSetConstantBuffers(0, 1, &m_constantBufferToPS);
	}
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}