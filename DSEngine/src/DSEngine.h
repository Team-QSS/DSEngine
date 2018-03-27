#pragma once
#include "Defines.h"
#include "Utils\Utils.h"
#include "Scene\SceneManager.h"
#include "Window\Window.h"
#include "Input\InputManager.h"
#include "Graphics\GraphicsManager.h"
#include "Utils\Time\TimeManager.h"
#include "Utils\FPS.h"
#include "BaseGame.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		friend Singleton<DSEngine>;

		void initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize);

		void run();

		void update();
		void draw();

		void goodBye();

	private:
		DSEngine();
		~DSEngine();
		

		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;

		InputManager* m_InputManager;
		Window* m_Window;
		SceneManager* m_SceneManager;
		GraphicsManager* m_GraphicsManager;
		
		Context m_Context;
		FPS m_FPS;
	};
}