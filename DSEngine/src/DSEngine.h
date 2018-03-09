#pragma once
#include "Utils\Utils.h"
#include "Defines.h"
#include "Scene\Scene.h"
#include "Window\Window.h"
#include "Input\InputManager.h"
#include "Graphics\GraphicsManager.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		DSEngine();
		~DSEngine();

		void initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize, Scene& initialScene, std::string sceneName);

		void run();

		void goodBye();

	private:
		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;
	};
}