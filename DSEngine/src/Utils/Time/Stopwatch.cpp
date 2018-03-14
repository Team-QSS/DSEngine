#include "Stopwatch.h"
#include "TimeManager.h"
#include "..\Utils.h"

namespace DS
{
	Stopwatch::Stopwatch() :
		m_isPaused(false),
		m_isStarted(false),
		m_TimePairVec(),
		m_Laps()
	{

	}

	Stopwatch::Stopwatch(const Stopwatch& yRef) :
		m_isPaused(yRef.m_isPaused),
		m_isStarted(yRef.m_isStarted),
		m_TimePairVec(yRef.m_TimePairVec),
		m_Laps(yRef.m_Laps)
	{

	}
	
	Stopwatch::Stopwatch(Stopwatch&& yRef) :
		m_isPaused(yRef.m_isPaused),
		m_isStarted(yRef.m_isStarted),
		m_TimePairVec(yRef.m_TimePairVec),
		m_Laps(yRef.m_Laps)
	{

	}

	Stopwatch::~Stopwatch()
	{

	}

	Stopwatch& Stopwatch::operator= (const Stopwatch& yRef)
	{
		m_isPaused = yRef.m_isPaused;
		m_isStarted = yRef.m_isStarted;
		m_TimePairVec = yRef.m_TimePairVec;
		m_Laps = yRef.m_Laps;
		return *this;
	}

	Stopwatch& Stopwatch::operator= (Stopwatch&& yRef)
	{
		m_isPaused = yRef.m_isPaused;
		m_isStarted = yRef.m_isStarted;
		m_TimePairVec = yRef.m_TimePairVec;
		m_Laps = yRef.m_Laps;
		return *this;
	}
	
	void Stopwatch::Start()
	{
		if (m_isStarted)
		{
			LOG(LogLevel::Warning, "Stopwatch already running. Overwritting start time.");
		}
		
		m_TimePairVec.push_back(std::make_pair(TimeManager::getInstance().currentTime(), Time()));
		
		m_isStarted = true;
		m_isPaused = false;
	}

	void Stopwatch::Stop()
	{
		m_TimePairVec.back().second = TimeManager::getInstance().currentTime();
		m_isPaused = true;
		m_isStarted = false;
	}

	void Stopwatch::Reset()
	{
		m_TimePairVec.clear();
		m_isStarted = false;
		m_isPaused = false;
	}

	void Stopwatch::Lap()
	{
		m_Laps.push_back(getTime());
	}

	const std::vector<Time>& Stopwatch::getLapTimes() const
	{
		return m_Laps;
	}

	Time Stopwatch::getTime()
	{
		Time totalTime;
		if (m_isPaused)
		{
			m_TimePairVec.back().second = TimeManager::getInstance().currentTime();
		}
		for (auto& time : m_TimePairVec)
		{
			totalTime += time.second - time.first;
		}
		return totalTime;
	}
}