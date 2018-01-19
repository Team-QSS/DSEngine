#pragma once
#include "Utils\Utils.h"
#include "Defines.h"
#include "Scene\Scene.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		DSEngine();
		~DSEngine();

		void initialize(BaseGame& game, Scene& initialScene, const std::string& sceneName);
		void initialize(BaseGame& game, Scene& initialScene, const std::string&& sceneName);

		void run();

		void goodBye();

	private:
		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;
	};
}