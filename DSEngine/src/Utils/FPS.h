#pragma once

#include "..\Defines.h"

namespace DS
{
	struct Context;

	struct FPS
	{
		int32 CurrentFPS, PreviousFPS;

		FPS();

		void update(const Context& context);

	private:
		float64 m_Timer;
		int32 m_Counter;
	};
}