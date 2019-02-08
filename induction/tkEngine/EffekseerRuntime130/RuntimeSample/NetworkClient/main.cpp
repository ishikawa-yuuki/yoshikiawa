
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <d3d9.h>
#include <XAudio2.h>
#pragma comment(lib, "d3d9.lib" )

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerSoundXAudio2.h>

#if _DEBUG
#pragma comment(lib, "VS2013/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "VS2013/Release/Effekseer.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerSoundXAudio2.lib" )
#endif
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static HWND g_window_handle = NULL;
static int g_window_width = 800;
static int g_window_height = 600;
static ::Effekseer::Manager*			g_manager = NULL;
static ::EffekseerRenderer::Renderer*	g_renderer = NULL;
static ::EffekseerSound::Sound*			g_sound = NULL;
static ::Effekseer::Vector3D			g_position;

static LPDIRECT3D9						g_d3d = NULL;
static LPDIRECT3DDEVICE9				g_d3d_device = NULL;
static IXAudio2*						g_xa2 = NULL;
static IXAudio2MasteringVoice*			g_xa2_master = NULL;

static ::Effekseer::Client*				g_client = NULL;

static int32_t							g_timer = 0;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg ) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void InitWindow()
{
	WNDCLASS wndClass;
	wchar_t szClassNme[]      =  L"RuntimeSample";
	wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = WndProc;
	wndClass.cbClsExtra    = 0;
	wndClass.cbWndExtra    = 0;
	wndClass.hInstance     = GetModuleHandle(0);
	wndClass.hIcon         = NULL;
	wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = szClassNme;
	RegisterClass(&wndClass);
	g_window_handle = CreateWindow(
		szClassNme,
		L"RuntimeSample",
		WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		g_window_width,
		g_window_height,
		NULL,
		NULL,
		GetModuleHandle(0),
		NULL);
	ShowWindow( g_window_handle, true );
	UpdateWindow( g_window_handle );
	
	// COM�̏�����
	CoInitializeEx( NULL, NULL );

	// DirectX9�̏��������s��
	D3DPRESENT_PARAMETERS d3dp;
	ZeroMemory(&d3dp, sizeof(d3dp));
	d3dp.BackBufferWidth = g_window_width;
	d3dp.BackBufferHeight = g_window_height;
	d3dp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dp.BackBufferCount = 1;      
	d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dp.Windowed = TRUE;
	d3dp.hDeviceWindow = g_window_handle;
	d3dp.EnableAutoDepthStencil = TRUE;
    d3dp.AutoDepthStencilFormat = D3DFMT_D16;

	g_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	g_d3d->CreateDevice( 
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dp,
		&g_d3d_device );
	
	// XAudio2�̏��������s��
	XAudio2Create( &g_xa2 );

	g_xa2->CreateMasteringVoice( &g_xa2_master );
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void MainLoop()
{
	for(;;)
	{ 
		MSG msg;
		if (PeekMessage (&msg,NULL,0,0,PM_NOREMOVE)) 
		{
			if( msg.message == WM_QUIT )
			{
				return ;
			}
			GetMessage (&msg,NULL,0,0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if( g_timer % 120 == 0 )
			{
				g_client->Reload( g_manager, (const EFK_CHAR*)L"test_reload.efk", (const EFK_CHAR*)L"test" );
			}

			// �G�t�F�N�g�̍X�V�������s���B
			g_manager->Update();
		
			g_d3d_device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
			g_d3d_device->BeginScene();

			// �G�t�F�N�g�̕`��J�n�������s���B
			g_renderer->BeginRendering();

			// �G�t�F�N�g�̕`����s���B
			g_manager->Draw();

			// �G�t�F�N�g�̕`��I���������s���B
			g_renderer->EndRendering();

			g_d3d_device->EndScene();

			g_timer++;

			{
				HRESULT hr;
				hr = g_d3d_device->Present( NULL, NULL, NULL, NULL );

				// �f�o�C�X���X�g����
				switch ( hr )
				{
					// �f�o�C�X���X�g
					case D3DERR_DEVICELOST:
					while ( FAILED( hr = g_d3d_device->TestCooperativeLevel() ) )
					{
						switch ( hr )
						{
							// �f�o�C�X���X�g
							case D3DERR_DEVICELOST:
								::SleepEx( 1000, true );
								break;

							// �f�o�C�X���X�g�F���Z�b�g��
							case D3DERR_DEVICENOTRESET:
								
								// �f�o�C�X���X�g�̏������s���O�Ɏ��s����
								g_renderer->OnLostDevice();

								D3DPRESENT_PARAMETERS d3dp;
								ZeroMemory(&d3dp, sizeof(d3dp));
								d3dp.BackBufferWidth = g_window_width;
								d3dp.BackBufferHeight = g_window_height;
								d3dp.BackBufferFormat = D3DFMT_X8R8G8B8;
								d3dp.BackBufferCount = 1;      
								d3dp.SwapEffect = D3DSWAPEFFECT_DISCARD;
								d3dp.Windowed = TRUE;
								d3dp.hDeviceWindow = g_window_handle;
								d3dp.EnableAutoDepthStencil = TRUE;
								d3dp.AutoDepthStencilFormat = D3DFMT_D16;

								g_d3d_device->Reset( &d3dp );

								// �f�o�C�X���X�g�̏����̌�Ɏ��s����
								g_renderer->OnResetDevice();

								break;
						}
					}
					break;
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
int main()
{
	InitWindow();

	// �`��p�C���X�^���X�̐���
	g_renderer = ::EffekseerRendererDX9::Renderer::Create( g_d3d_device, 2000 );
	
	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	g_manager = ::Effekseer::Manager::Create( 2000 );

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_manager->SetSpriteRenderer( g_renderer->CreateSpriteRenderer() );
	g_manager->SetRibbonRenderer( g_renderer->CreateRibbonRenderer() );
	g_manager->SetRingRenderer( g_renderer->CreateRingRenderer() );
	g_manager->SetModelRenderer( g_renderer->CreateModelRenderer() );

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetTextureLoader( g_renderer->CreateTextureLoader() );
	g_manager->SetModelLoader( g_renderer->CreateModelLoader() );

	// ���Đ��p�C���X�^���X�̐���
	g_sound = ::EffekseerSound::Sound::Create( g_xa2, 16, 16 );

	// ���Đ��p�C���X�^���X����Đ��@�\���w��
	g_manager->SetSoundPlayer( g_sound->CreateSoundPlayer() );
	
	// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetSoundLoader( g_sound->CreateSoundLoader() );

	// �N���C�A���g�̐���
	g_client = Effekseer::Client::Create();

	// �N���C�A���g���|�[�g60000�Őڑ�
	g_client->Start( "127.0.0.1", 60000 );

	MainLoop();

	// �N���C�A���g�̔j��
	ES_SAFE_DELETE( g_client );

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɉ��Đ��p�C���X�^���X��j��
	g_sound->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();

	// XAudio2�̉��
	if( g_xa2_master != NULL )
	{
		g_xa2_master->DestroyVoice();
		g_xa2_master = NULL;
	}
	ES_SAFE_RELEASE( g_xa2 );

	// DirectX�̉��
	ES_SAFE_RELEASE( g_d3d_device );
	ES_SAFE_RELEASE( g_d3d );

	// COM�̏I������
	CoUninitialize();

	return 0;
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------