#pragma once
#include <Windows.h>
#include <assert.h>
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

	private:
		HWND m_WindowHandle;

		bool m_IsInitialized;
	};
}
