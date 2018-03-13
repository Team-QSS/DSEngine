#include "TimeManager.h"

namespace DS
{
	const Time& TimeManager::deltaTime()
	{
		return m_DeltaTime;
	}

	const Time& TimeManager::timeSinceStart()
	{
		return m_ElapsedTime;
	}
	
	const Time& TimeManager::currentTime()
	{
		m_CurrentTime.m_Duration = std::chrono::high_resolution_clock::now().time_since_epoch();
		return m_CurrentTime;
	}

	void TimeManager::startMonitoring()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}

	void TimeManager::stopMonitoring()
	{
		auto endTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime.m_Duration = endTime - m_StartTime;
		m_ElapsedTime += m_DeltaTime;
	}

	tstring TimeManager::getTimeStamp()
	{
		int32 totalSeconds = int32(m_ElapsedTime.getSeconds());
		int32 seconds = totalSeconds % 60;
		int32 minutes = totalSeconds / 60;
		int32 hours = totalSeconds / 3600;

		tstringstream strstr;
		if (hours < 10)
		{
			strstr << "0";
		}
		strstr << hours << " : ";
	
		if (minutes < 10)
		{
			strstr << "0";
		}
		strstr << minutes << " : ";

		if (seconds < 10)
		{
			strstr << "0";
		}
		strstr << seconds;

		return strstr.str();
	}
}