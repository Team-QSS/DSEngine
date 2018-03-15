#pragma once
#include "Utils\Utils.h"
#include "Defines.h"
#include "Scene\Scene.h"
#include "Window\Window.h"
#include "Input\InputManager.h"
#include "Graphics\GraphicsManager.h"
#include "Scene\SceneManager.h"
#include "BaseGame.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		void initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize, Scene& initialScene, tstring sceneName);

		void run();

		void goodBye();

	private:
		DSEngine();
		~DSEngine();
		friend Singleton<DSEngine>;

		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;

		Context m_GameContext;
	};
}