#include "InputManager.h"
#include <Windows.h>
#include "../Window/Window.h"

namespace DS
{
	InputManager::InputManager() :
		m_CurKeyState(new BYTE[KEY_COUNT]),
		m_PreKeyState(new BYTE[KEY_COUNT])
	{

	}

	InputManager::~InputManager()
	{
		if (m_CurKeyState)
		{
			delete[] m_CurKeyState;
		}

		if (m_PreKeyState)
		{
			delete[] m_PreKeyState;
		}
	}

	void InputManager::update()
	{
		updateKeyState();
		updateMouseState();
	}

	void InputManager::updateKeyState()
	{
		//현재 상태를 이전 프레임의 상태로 변환
		BYTE* temp = m_PreKeyState;
		m_PreKeyState = m_CurKeyState;
		m_CurKeyState = temp;

		//현재 프레임의 키보드 상태 확인
		if (!GetKeyboardState(m_CurKeyState))
		{
			LOG(LogLevel::Error, "키보드 입력 오류");
		}
	}

	void InputManager::updateMouseState()
	{
		bool temp;

		//현재 상태를 이전 프레임의 상태로 변환
		temp = m_CurMouseState[0];
		m_CurMouseState[0] = m_PreMouseState[0];
		m_PreMouseState[0] = temp;

		temp = m_CurMouseState[1];
		m_CurMouseState[1] = m_PreMouseState[1];
		m_PreMouseState[1] = temp;
	}

	bool InputManager::isKeyDown(char key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		return m_CurKeyState[key];
	}

	bool InputManager::isKeyPressed(char key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		if (!m_PreKeyState[key] && m_CurKeyState[key])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::isKeyReleased(char key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "잘못된 키보드 키값 체크");
			return false;
		}

		if (m_PreKeyState[key] && !m_CurKeyState[key])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::isButtonDown(MouseButton button) const
	{
		switch (button)
		{
			case MouseButton::Left:
				return m_CurMouseState[0];
			case MouseButton::Right:
				return m_CurMouseState[1];
		}
		return false;
	}

	bool InputManager::isButtonPressed(MouseButton button) const
	{
		switch (button)
		{
		case MouseButton::Left:
			return !m_PreMouseState[0] && m_CurMouseState[0];
		case MouseButton::Right:
			return !m_PreMouseState[1] && m_CurMouseState[1];
		}
		return false;
	}

	bool InputManager::isButtonReleased(MouseButton button) const
	{
		switch (button)
		{
		case MouseButton::Left:
			return m_PreMouseState[0] && !m_CurMouseState[0];
		case MouseButton::Right:
			return m_PreMouseState[1] && !m_CurMouseState[1];
		}
		return false;
	}

	DirectX::XMINT2 InputManager::getCursorPos() const
	{
		POINT cursorPos;
		if (!GetCursorPos(&cursorPos))
		{
			LOG(LogLevel::Error, "커서 위치 참고 오류");
		}

		ScreenToClient(Window::getInstance().getHandle(), &cursorPos);

		return { cursorPos.x, cursorPos.y };
	}
}