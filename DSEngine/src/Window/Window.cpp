#include "Window.h"
#include "../Utils/Logger.h"

namespace DS
{
	Window::Window() :
		m_WindowHandle(nullptr),
		m_IsInitialized(false),
		m_ShouldClose(false),
		m_IsActive(false)
//		m_IsFullScreen(false),
//		m_CanGoFullScreen(false)
	{

	}

	Window::~Window()
	{

	}

	void Window::initialize(HINSTANCE instanceHandle, int x_Size, int y_Size)
	{
		initialize(instanceHandle, DirectX::XMINT2(x_Size, y_Size));
	}

	void Window::initialize(HINSTANCE instanceHandle, DirectX::XMINT2 size)
	{
		if (m_IsInitialized)
		{
			LOG(LogLevel::Error, "윈도우 객체 중복 초기화 시도");
		}

		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = instanceHandle;
		wc.lpfnWndProc = NULL;
		wc.lpszClassName = "DSEngine";
		wc.lpszMenuName = "a";
		wc.style = CS_HREDRAW | CS_VREDRAW;

		if (!RegisterClass(&wc))
		{
			LOG(LogLevel::Error, "윈도우 클래스 등록 실패");
			terminate(0);
		}

		m_WindowHandle = CreateWindow("DSEngine", "a", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.x, size.y, 0, 0, instanceHandle, 0);

		if (!m_WindowHandle)
		{
			LOG(LogLevel::Error, "윈도우 생성 실패");
			terminate(0);
		}

		ShowWindow(m_WindowHandle, SW_SHOWNORMAL);
		UpdateWindow(m_WindowHandle);
	}

	void Window::peekMessage()
	{
		MSG msg = {};
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				m_ShouldClose = true;
			}
		}
	}

	const HWND& Window::getHandle() const
	{
		return m_WindowHandle;
	}

	bool Window::shouldClose() const
	{
		return m_ShouldClose;
	}

	bool Window::changeWindowTitle(const char* title)
	{
		return SetWindowText(m_WindowHandle, title) != 0;
	}

	bool Window::isActive() const
	{
		return m_IsActive;
	}

	void Window::setActive(bool active)
	{
		m_IsActive = active;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_ENTERSIZEMOVE:
			case WM_NCRBUTTONDOWN:
				Window::getInstance().setActive(false);
				break;
			case WM_EXITSIZEMOVE:
			case WM_EXITMENULOOP:
				Window::getInstance().setActive(true);
				break;
			case WM_KEYDOWN:
				//Input 구현 후 상호작용
			case WM_KEYUP:
				//Input 구현 후 상호작용
			case WM_KEYLAST:
				//Input 구현 후 상호작용
			case WM_SYSCOMMAND:
				//SC_KEYMENU == (wParam & 0xFFF0)

				//alt+enter 전체화면
				//Input 구현 후 상호작용
			default:
				return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
}