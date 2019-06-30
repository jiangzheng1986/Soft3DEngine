#include "Soft3DEngine.h"

HINSTANCE hInst;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int FindLastChar(const WCHAR *String, WCHAR Char)
{
	int i = 0;
	int LastFound = -1;
	const WCHAR *String1 = String;
	while (true)
	{
		WCHAR Char1 = *String1++;
		if (Char1 == Char)
		{
			LastFound = i;
		}
		if (Char1 == '\0')
		{
			return LastFound;
		}
		i++;
	}
}

void GetDirectoryOfPath(WCHAR *Path1, const WCHAR *Path)
{
	wcscpy(Path1, Path);
	int LastFound1 = FindLastChar(Path1, '/');
	int LastFound2 = FindLastChar(Path1, '\\');
	int LastFound = MAX_(LastFound1, LastFound2);
	if (LastFound != -1)
	{
		Path1[LastFound] = 0;
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WCHAR ProgramPath_UTF16[1000];
	GetModuleFileNameW(nullptr, ProgramPath_UTF16, 1000);
	WCHAR ProgramDirectory_UTF16[1000];
	GetDirectoryOfPath(ProgramDirectory_UTF16, ProgramPath_UTF16);
	SetCurrentDirectoryW((WCHAR *)ProgramDirectory_UTF16);

	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"Soft3DEngine";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance;

   hWnd = CreateWindow(L"Soft3DEngine", L"Soft3DEngine", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, BACKBUFFER_WIDTH + 10, BACKBUFFER_HEIGHT + 35, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   CGame_GetInstance()->Initilize(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		CGame_GetInstance()->Draw(hdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}