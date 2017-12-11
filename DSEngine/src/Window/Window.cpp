#include "Window.h"

namespace DS
{
	Window::Window() :
		m_IsInitialized(false),
		m_WindowHandle(nullptr),
		m_ShouldClose(false)
	{

	}

	Window::~Window()
	{

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

	bool Window::shouldClose() const
	{
		return m_ShouldClose;
	}

	bool Window::changeWindowTitle(const char* title)
	{
		return SetWindowText(m_WindowHandle, title) != 0;
	}
}