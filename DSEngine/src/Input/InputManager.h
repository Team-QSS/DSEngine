#pragma once
#include "../Utils/Utils.h"
#include <Windows.h>
#include <DirectXMath.h>

namespace DS
{
	class Window;

	using Key = char;

	enum class MouseButton
	{
		Left,
		Right
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		friend Singleton<InputManager>;

		void update();

		//�����ִٸ� true, �׿ܿ� false
		bool isKeyDown(Key key) const;
		//�ش� Ű�� ���� ù �����ӿ��� true, �׿ܿ� false
		bool isKeyPressed(Key key) const;
		//�ش� Ű�� �� ù �����ӿ��� true, �׿ܿ� false
		bool isKeyReleased(Key key) const;

		//�����ִٸ� true, �׿ܿ� false
		bool isButtonDown(MouseButton button) const;
		//�ش� ��ư�� ���� ù �����ӿ��� true, �׿ܿ� false
		bool isButtonPressed(MouseButton button) const;
		//�ش� ��ư�� �� ù �����ӿ��� true, �׿ܿ� false
		bool isButtonReleased(MouseButton button) const;

		//���콺 Ŀ�� ��ġ
		DirectX::XMINT2 getCursorPos() const;
	private:
		static const int KEY_COUNT = 256;
		static const int KEY_ID_MIN = 0x07;
		static const int KEY_ID_MAX = 0xfe;

	private:
		InputManager();
		~InputManager();

		void updateKeyState();
		void updateMouseState();

		void setMouseState(MouseButton button, bool isDown);

		BYTE* m_CurKeyState;
		BYTE* m_PreKeyState;

		bool m_CurMouseState[2];
		bool m_PreMouseState[2];

		friend class Window;
	};
}