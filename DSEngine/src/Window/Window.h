#pragma once
#include <Windows.h>
#include "../Utils/Utils.h"

namespace DS
{
	class Window final : public Singleton<Window>
	{
	public:
		Window();
		~Window();

		void initialize(HINSTANCE instanceHandle);

	private:
		HWND m_WindowHandle;

		bool m_IsInitialized;
	};
}
