#pragma once
#include "Utils\Utils.h"
#include"Defines.h"

namespace DS
{
	class DSEngine final : public Singleton<DSEngine>
	{
	public:
		DSEngine();
		~DSEngine();

		void initialize(BaseGame& game);

		void run();

		void goodBye();

	private:
		BaseGame* m_Game;
		bool m_IsInitialized;
		bool m_IsRunning;
	};
}