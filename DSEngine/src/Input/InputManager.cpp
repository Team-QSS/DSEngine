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
		//���� ���¸� ���� �������� ���·� ��ȯ
		BYTE* temp = m_PreKeyState;
		m_PreKeyState = m_CurKeyState;
		m_CurKeyState = temp;

		//���� �������� Ű���� ���� Ȯ��
		if (!GetKeyboardState(m_CurKeyState))
		{
			LOG(LogLevel::Error, "Ű���� �Է� ����");
		}
	}

	void InputManager::updateMouseState()
	{
		bool temp;

		//���� ���¸� ���� �������� ���·� ��ȯ
		m_PreKeyState[0] = m_CurMouseState[0];
		m_PreKeyState[1] = m_CurMouseState[1];
	}

	void InputManager::setMouseState(MouseButton button, bool isDown)
	{
		switch (button)
		{
		case MouseButton::Left:
			m_CurMouseState[0] = isDown;
			break;
		case MouseButton::Right:
			m_CurMouseState[1] = isDown;
			break;
		}
	}


	bool InputManager::isKeyDown(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "�߸��� Ű���� Ű�� üũ");
			return false;
		}

		return m_CurKeyState[key] & 0xf0;
	}

	bool InputManager::isKeyPressed(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "�߸��� Ű���� Ű�� üũ");
			return false;
		}

		if (!(m_PreKeyState[key] & 0xf0) && (m_CurKeyState[key] & 0xf0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::isKeyReleased(Key key) const
	{
		if (key <= KEY_ID_MIN || KEY_ID_MAX < key)
		{
			LOG(LogLevel::Warning, "�߸��� Ű���� Ű�� üũ");
			return false;
		}

		if ((m_PreKeyState[key] & 0xf0) && !(m_CurKeyState[key] & 0xf0))
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
			LOG(LogLevel::Error, "Ŀ�� ��ġ ���� ����");
		}

		ScreenToClient(Window::getInstance().getHandle(), &cursorPos);

		return { cursorPos.x, cursorPos.y };
	}
}