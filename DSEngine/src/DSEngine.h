#pragma once
#include "Defines.h"
#include "Utils\Utils.h"
#include "Scene\SceneManager.h"
#include "Window\Window.h"
#include "Input\InputManager.h"
#include "Graphics\GraphicsManager.h"
#include "BaseGame.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		friend Singleton<DSEngine>;

		void initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize, Scene& initialScene, tstring sceneName);

		void run();

		void goodBye();

	private:
		DSEngine();
		~DSEngine();
		

		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;
		Context m_GameContext;
	};
}