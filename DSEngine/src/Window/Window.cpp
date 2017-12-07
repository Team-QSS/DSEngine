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

	void Window::initialize(HINSTANCE instanceHandle)
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
	}
}