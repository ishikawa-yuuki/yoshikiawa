
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <assert.h>

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <AL/alc.h>
#include <Wingdi.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "OpenAL32.lib" )

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererGL.h>
#include <EffekseerSoundAL.h>

#if _DEBUG
#pragma comment(lib, "VS2013/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerRendererGL.lib" )
#pragma comment(lib, "VS2013/Debug/EffekseerSoundAL.lib" )
#else
#pragma comment(lib, "VS2013/Release/Effekseer.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerRendererGL.lib" )
#pragma comment(lib, "VS2013/Release/EffekseerSoundAL.lib" )
#endif

typedef int (APIENTRY * PFNWGLSWAPINTERVALEXTPROC)(int);

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static HWND g_window_handle = NULL;
static int g_window_width = 800;
static int g_window_height = 600;
static ::Effekseer::Manager*			g_manager = NULL;
static ::EffekseerRenderer::Renderer*	g_renderer = NULL;
static ::EffekseerSound::Sound*			g_sound = NULL;
static ::Effekseer::Effect*				g_effect = NULL;
static ::Effekseer::Handle				g_handle = -1;
static ::Effekseer::Vector3D			g_position;

static HDC								g_hDC = NULL;
static HGLRC							g_hGLRC = NULL;

static ALCdevice*						g_alcdev = NULL;
static ALCcontext*						g_alcctx = NULL;

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
static void WaitFrame()
{
	static DWORD beforeTime = timeGetTime();
	DWORD currentTime = timeGetTime();
	
	DWORD elapsedTime = currentTime - beforeTime;
	if (elapsedTime < 16) {
		Sleep(16 - elapsedTime);
	}
	beforeTime = timeGetTime();
}

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

	// OpenGL�̏��������s��
	g_hDC = GetDC( g_window_handle );

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA, 24,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32,
		0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	int pxfm = ChoosePixelFormat( g_hDC, &pfd );

	SetPixelFormat( g_hDC, pxfm, &pfd );

	g_hGLRC = wglCreateContext( g_hDC );

	wglMakeCurrent( g_hDC, g_hGLRC );

	auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalEXT(1);

	glViewport( 0, 0, g_window_width, g_window_height );
	
	// OpenAL�f�o�C�X���쐬
	g_alcdev = alcOpenDevice(NULL);

	// OpenAL�R���e�L�X�g���쐬
	g_alcctx = alcCreateContext(g_alcdev, NULL);

	alcMakeContextCurrent(g_alcctx);
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
			// �G�t�F�N�g�̈ړ��������s��
			g_manager->AddLocation( g_handle, ::Effekseer::Vector3D( 0.2f, 0.0f, 0.0f ) );

			// �G�t�F�N�g�̍X�V�������s��
			g_manager->Update();
			
			
			wglMakeCurrent( g_hDC, g_hGLRC );

			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// �G�t�F�N�g�̕`��J�n�������s���B
			g_renderer->BeginRendering();

			// �G�t�F�N�g�̕`����s���B
			g_manager->Draw();

			// �G�t�F�N�g�̕`��I���������s���B
			g_renderer->EndRendering();

			glFlush();
			wglMakeCurrent( 0, 0 );
			WaitFrame();
			SwapBuffers( g_hDC );
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
	g_renderer = ::EffekseerRendererGL::Renderer::Create( 2000 );
	
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
	g_sound = EffekseerSound::Sound::Create( 32 );

	// ���Đ��p�C���X�^���X����Đ��@�\���w��
	g_manager->SetSoundPlayer( g_sound->CreateSoundPlayer() );
	
	// ���Đ��p�C���X�^���X����T�E���h�f�[�^�̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_manager->SetSoundLoader( g_sound->CreateSoundLoader() );

	// ���_�ʒu���m��
	g_position = ::Effekseer::Vector3D( 10.0f, 5.0f, 20.0f );

	// ���e�s���ݒ�
	g_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovRH_OpenGL( 90.0f / 180.0f * 3.14f, (float)g_window_width / (float)g_window_height, 1.0f, 50.0f ) );

	// �J�����s���ݒ�
	g_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtRH( g_position, ::Effekseer::Vector3D( 0.0f, 0.0f, 0.0f ), ::Effekseer::Vector3D( 0.0f, 1.0f, 0.0f ) ) );
	
	// �G�t�F�N�g�̓Ǎ�
	g_effect = Effekseer::Effect::Create( g_manager, (const EFK_CHAR*)L"test.efk" );

	// �G�t�F�N�g�̍Đ�
	g_handle = g_manager->Play( g_effect, 0, 0, 0 );

	MainLoop();
	
	// �G�t�F�N�g�̒�~
	g_manager->StopEffect( g_handle );

	// �G�t�F�N�g�̔j��
	ES_SAFE_RELEASE( g_effect );

	// ��ɃG�t�F�N�g�Ǘ��p�C���X�^���X��j��
	g_manager->Destroy();

	// ���ɉ��Đ��p�C���X�^���X��j��
	g_sound->Destroy();

	// ���ɕ`��p�C���X�^���X��j��
	g_renderer->Destroy();

	// OpenAL�̉��
	alcDestroyContext(g_alcctx);
	alcCloseDevice(g_alcdev);
	
	g_alcctx = NULL;
	g_alcdev = NULL;

	// OpenGL�̉��
	wglMakeCurrent( 0, 0 );
	wglDeleteContext( g_hGLRC );
	timeEndPeriod(1);

	// COM�̏I������
	CoUninitialize();

	return 0;
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------