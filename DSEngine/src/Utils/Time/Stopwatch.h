#pragma once
#include "..\..\Defines.h"
#include "Time.h"
#include <vector>

namespace DS
{
	class Stopwatch final
	{
	public:
		Stopwatch();
		Stopwatch(const Stopwatch& yRef);
		Stopwatch(Stopwatch&& yRef);
		~Stopwatch();

		Stopwatch& operator= (const Stopwatch& yRef);
		Stopwatch& operator= (Stopwatch&& yRef);

		void Start();
		void Stop();
		void Reset();
		void Lap();
		const std::vector<Time>& getLapTimes() const;
		Time getTime();

	private:
		bool m_isPaused;
		bool m_isStarted;
		std::vector<std::pair<Time, Time>> m_TimePairVec;
		std::vector<Time> m_Laps;
	};
}