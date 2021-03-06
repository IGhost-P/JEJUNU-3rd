// prac01.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
// 2021. 05. 25.
// Created by Soo-Kyun Kim

#include "framework.h"
#include "prac01.h"
#include "gl.h"
#include "glu.h"
#include "glut.h"


#define MAX_LOADSTRING 100
#define	IDT_TIMER	1

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

/////////////////////// sk
HDC hDeviceContext;								// current device context
HGLRC hRenderingContext;						// current rendering context

//-----------------------------------------------------
     // virtual trackball
#include "trackball.h"
TrackBall trball;
bool bLButtonDown = false;
//-----------------------------------------------------

bool bSetupPixelFormat(HDC hdc);
void Resize(int width, int height);
void DrawScene(HDC MyDC);

 //Texture
 GLubyte image[64][64][3];
 
#include "bmpLoader.h"
MyBMPLoader* bmpLoader = NULL;
void LoadTexture(void);


GLfloat vertices[8][3] = {
    { -1.0f, -1.0f,  1.0f }, { -1.0f,  1.0f,  1.0f },
    {  1.0f,  1.0f,  1.0f }, {  1.0f, -1.0f,  1.0f },
    { -1.0f, -1.0f, -1.0f }, { -1.0f,  1.0f, -1.0f },
    {  1.0f,  1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f }
};

GLfloat colors[8][3] = {
    { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }
};

void Quad(int a, int b, int c, int d);
//-----------------------------------------------------


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC01, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC01));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC01));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL; // MAKEINTRESOURCEW(IDC_PRAC01);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT clientRect;

    switch (message)
    {
    case WM_CREATE:
        // Initialize for the OpenGL rendering
        hDeviceContext = GetDC(hWnd);
        if (!bSetupPixelFormat(hDeviceContext)) {
            MessageBox(hWnd, "Error in setting up pixel format for OpenGL", "Error", MB_OK | MB_ICONERROR);
            DestroyWindow(hWnd);
        }
        hRenderingContext = wglCreateContext(hDeviceContext);
        wglMakeCurrent(hDeviceContext, hRenderingContext);

        // virtual trackball
        trball.initialize();

        break;

    case WM_SIZE:
        GetClientRect(hWnd, &clientRect);
        Resize(clientRect.right, clientRect.bottom);

        // virtual trackball
        trball.resize(clientRect.right, clientRect.bottom);

        InvalidateRect(hWnd, NULL, false);

        break;
        /*
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        */
    case WM_PAINT:
        {
        DrawScene(hDeviceContext);
        ValidateRect(hWnd, NULL);
      
        /*
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
            */
        }
        break;

    
    case WM_LBUTTONDOWN:
        if (!bLButtonDown)
        {
            bLButtonDown = true;
            trball.start((int)LOWORD(lParam), (int)HIWORD(lParam));
        }
        break;

    case WM_LBUTTONUP:
        bLButtonDown = false;
        break;

    case WM_MOUSEMOVE:
        if (bLButtonDown)
        {
            trball.end((int)LOWORD(lParam), (int)HIWORD(lParam));
            InvalidateRect(hWnd, NULL, true);
        }
        break;

    case WM_DESTROY:
        // Destroy all about OpenGL
        if (hRenderingContext)
            wglDeleteContext(hRenderingContext);
        if (hDeviceContext)
            ReleaseDC(hWnd, hDeviceContext);

        // Destroy a timer
        KillTimer(hWnd, IDT_TIMER);

        PostQuitMessage(0);
        break;

  
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

bool bSetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd;
    int pixelformat;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.dwLayerMask = PFD_MAIN_PLANE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.cAccumBits = 0;
    pfd.cStencilBits = 0;

    if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == 0) {
        MessageBox(NULL, "ChoosePixelFormat() failed!!!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    if (SetPixelFormat(hdc, pixelformat, &pfd) == false) {
        MessageBox(NULL, "SetPixelFormat() failed!!!", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

void Resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);

    float cx = width;
    float cy = height;

   /*
    if (cx <= cy)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)cy / (GLfloat)cx,
            2.0 * (GLfloat)cy / (GLfloat)cx, 1.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)cx / (GLfloat)cy,
            2.0 * (GLfloat)cx / (GLfloat)cy, -2.0, 2.0, 1.0, 10.0);
    
   */
   //----------------------------------------------------
    GLfloat aspect = (GLfloat)cx / (GLfloat)cy;
    gluPerspective(35.0f, aspect, 0.1f, 50.0f);
    //----------------------------------------------------


    return;

}
    
/*
* DrawScene : to draw a scene
*/
void DrawScene(HDC MyDC)
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(4.0f, 4.0f, 4.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
           
    glMultMatrixd(trball.rMat);
   
    //------------------------------------------------
    glEnable(GL_TEXTURE_2D);
    LoadTexture();
  
    //------------------------------------------------
    Quad(0, 3, 2, 1);
    Quad(1, 2, 6, 5);
    Quad(2, 3, 7, 6);
    Quad(3, 0, 4, 7);
    Quad(4, 5, 6, 7);
    Quad(5, 4, 0, 1);
    
    SwapBuffers(MyDC);

    return;
}


void Quad(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glColor3fv(colors[a]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3fv(vertices[a]);
    glColor3fv(colors[b]);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(vertices[b]);
    glColor3fv(colors[c]);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(vertices[c]);
    glColor3fv(colors[d]);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3fv(vertices[d]);
    glEnd();

    return;
}

void LoadTexture(void)
{ 
    register int i, j;
    int a, b;
    for (i = 0; i < 64; i++)
    {
        for (j = 0; j < 64; j++)
        {
            int c = (((i & 0x08) == 0) ^ ((j & 0x08) == 0)) * 255;
            image[i][j][0] = (GLubyte)c;
            image[i][j][1] = (GLubyte)c;
            image[i][j][2] = (GLubyte)c;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    return;









}
