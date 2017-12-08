#include "Window.h"

namespace DS
{
	Window::Window() :
		m_IsInitialized(false)
	{

	}

	Window::~Window()
	{

	}

	void Window::initialize(HINSTANCE instanceHandle, int width, int height)
	{
		if (m_IsInitialized)
		{
			LOG(LogLevel::Error, "������ ��ü �ߺ� �ʱ�ȭ �õ�");
		}

		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hInstance = instanceHandle;
		wc.lpfnWndProc;
		wc.lpszClassName = "a";
		wc.lpszMenuName = "a";
		wc.style = CS_HREDRAW | CS_VREDRAW;

		if (!RegisterClass(&wc))
		{
			LOG(LogLevel::Error, "������ Ŭ���� ��� ����");
			terminate(0);
		}

		m_WindowHandle = CreateWindow("a", "a", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instanceHandle, 0);

		if (!m_WindowHandle)
		{
			LOG(LogLevel::Error, "������ ���� ����");
			terminate(0);
		}
	}
}