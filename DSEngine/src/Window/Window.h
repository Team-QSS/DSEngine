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

		void initialize(HINSTANCE instanceHandle, DirectX::XMINT2 size);

		void peekMessage();

		bool shouldClose() const;
		bool changeWindowTitle(const char* title);

	private:
		HWND m_WindowHandle;

		bool m_IsInitialized;
		bool m_ShouldClose;
	};
}
