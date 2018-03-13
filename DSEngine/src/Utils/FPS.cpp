#include "FPS.h"
#include "Time\Time.h"
#include "Time\Context.h"

namespace DS
{
	FPS::FPS() :
		CurrentFPS(0),
		PreviousFPS(0),
		m_Timer(0.0),
		m_Counter(0)
	{

	}

	void FPS::update(const Context& context)
	{
		++m_Counter;
		m_Timer += context.time->deltaTime().getSeconds();

		if (m_Timer > 1.0)
		{
			m_Timer -= 1.0;
			PreviousFPS = CurrentFPS;
			CurrentFPS = m_Counter;
			m_Counter = 0;
		}
	}
}