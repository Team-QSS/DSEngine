#pragma once

#include "..\..\Defines.h"
#include "..\Utils.h"
#include <memory>
#include "Time.h"
#include <chrono>

namespace DS
{
	class TimeManager final : public Singleton<TimeManager>
	{
	private:
		TimeManager();
		TimeManager(const TimeManager& t) {};
		TimeManager(TimeManager&& t) {};
		TimeManager& operator= (const TimeManager& t) {};
		TimeManager& operator= (TimeManager&& t) {};
		~TimeManager() {};

	public:
		friend Singleton<TimeManager>;

		void startMonitoring();
		void stopMonitoring();

		const Time& deltaTime();
		const Time& timeSinceStart();
		const Time& currentTime();
		tstring getTimeStamp();

	private:
		std::chrono::high_resolution_clock::time_point m_StartTime;
		Time m_DeltaTime;
		Time m_ElapsedTime;
		Time m_CurrentTime;
	};
}