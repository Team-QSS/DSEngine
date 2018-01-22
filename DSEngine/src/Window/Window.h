#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include "../Utils/Utils.h"

namespace DS
{
	class Window final : public Singleton<Window>
	{
	public:
		Window();
		~Window();

		void initialize(HINSTANCE instanceHandle, int x_Size, int y_Size);
		void initialize(HINSTANCE instanceHandle, DirectX::XMINT2 size);

		const HWND& getHandle() const;

		void peekMessage();

		bool shouldClose() const;

		bool isActive() const;
		void setActive(bool active);

//		bool isFullScreen() const;
//		bool canGoFullScreen() const;
//		void setFullScreen(HWND hWnd, bool fullscreen);
//		void toggleFullScreen(HWND hWnd);

		bool setWindowName(const char* windowName) const;	//윈도우 이름 바꾸기
		bool setWindowName(std::string windowName) const;	//윈도우 이름 바꾸기

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HWND m_WindowHandle;

		bool m_IsInitialized;
		bool m_ShouldClose;
		bool m_IsActive;
//		bool m_IsFullScreen;
//		bool m_CanGoFullScreen;
	};
}
