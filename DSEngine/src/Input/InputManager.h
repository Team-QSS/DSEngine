#pragma once
#include "../Utils/Utils.h"
#include <Windows.h>

namespace DS
{
	class InputManager final : Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void initialize();
		
	private:
		bool m_CurKeyboardState[256];

		LRESULT CALLBACK WndProc(HINSTANCE instanceHandle, UINT message, WPARAM wParam, LPARAM lParam);
	};
}