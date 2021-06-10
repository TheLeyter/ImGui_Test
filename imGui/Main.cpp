#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"winmm.lib")

#include <Windows.h>
#include <d3d9.h>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <tchar.h>

HINSTANCE g_hInstance = NULL;
HWND g_hWnd = NULL;
int g_iWindowWidth = 800;
int g_iWindowHeigh = 600;
bool g_bAppicationState = true;
IDirect3D9* g_pDirect3D = NULL;
IDirect3DDevice9* g_pDirect3DDevice = NULL;

#pragma region FuncPrototype

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR lpCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
bool CreateDeviceD3D(HWND hWnd);


#pragma endregion

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR lpCmdLine, int iCmdShow) {
	g_hInstance = GetModuleHandle(NULL);

	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "CheatMenu";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Can't register window class", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	g_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		"CheatMenu",
		"CheatMenu",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		200,
		200,
		g_iWindowWidth,
		g_iWindowHeigh,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	if (g_hWnd == NULL) {
		MessageBox(NULL, "Can't create window ", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);
	SetFocus(g_hWnd);
	SetForegroundWindow(g_hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (g_bAppicationState) {

		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
		case WM_DESTROY:
		{
			g_bAppicationState = false;
			return 0;
		}

	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

