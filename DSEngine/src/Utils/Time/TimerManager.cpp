#include "TimerManager.h"
#include "Context.h"
#include "Timer.h"
#include <algorithm>
#include <string>

namespace DS
{
	void TimerManager::update(const Context& context)
	{
		for (auto& it : m_GarbageContainer)
		{
			m_TimerContainer.erase(it.first);
		}
		m_GarbageContainer.clear();

		for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end(); )
		{
			if (it->second.update(context))
			{
				m_TimerContainer.erase(it++);
			}
			else
			{
				++it;
			}
		}
	}

	bool TimerManager::createTimer(const tstring& name, float32 targetTime, bool countingDown,
		bool loop, std::function<void()> func, bool paused)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return false;
			}
		}

		for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end(); ++it)
		{
			if (it->first == name)
			{
				m_GarbageContainer[it->first] = it->second;
				break;
			}
		}

		Timer newTimer(targetTime, countingDown, loop, func, paused);
		m_TimerContainer[name] = newTimer;
		return true;
	}

	bool TimerManager::removeTimer(const tstring& name)
	{
		for (auto it = m_TimerContainer.begin(); it != m_TimerContainer.end(); ++it)
		{
			if (it->first == name)
			{
				m_GarbageContainer[it->first] = it->second;
				return true;
			}
		}

		LOG(LogLevel::Warning, "TimerManager::removeTimer : trying to remove unknown timer '" + name + "'.");
		return false;
	}

	void TimerManager::pauseTimer(const tstring& name, bool paused)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.setPaused(paused);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::pauseTimer : trying to pause unknown Timer '" + name + "'.");
	}

	void TimerManager::setCountingDownTimer(const tstring& name, bool countingDown)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.setCountingDown(countingDown);
				return;
			}
			LOG(LogLevel::Warning, "TimerManager::setCountingDownTimer : trying to modify unknown Timer '" + name + "'.");
		}
	}

	void TimerManager::setLoopTimer(const tstring& name, bool looping)
	{
		for (auto & it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.setLoop(looping);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::SetLoopTimer: trying to modify unknown timer '" + name + "'.");
	}

	void TimerManager::resetTimer(const tstring& name, bool paused)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.Reset(paused);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::resetTimer : trying to reset unknown timer '" + name + "'.");
	}

	void TimerManager::setTargetTimeTimer(const tstring& name, float32 targetTime, bool reset, bool paused)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.setTargetTime(targetTime, reset, paused);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::setTargetTimeTimer : trying to modify unknown timer '" + name + "'.");
	}

	void TimerManager::setFunctionTimer(const tstring& name, const std::function<void()>& func)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.setFunction(func);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::setFunctionTimer : trying to modify unknown timer '" + name + "'.");
	}

	float64 TimerManager::forceEndTimer(const tstring& name)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.forceEnd();
			}
		}
		LOG(LogLevel::Warning, "TimerManager::forceEndTimer : trying to end unknown timer '" + name + "'.");
		return 0;
	}

	void TimerManager::forwardTimer(const tstring& name, float64 time)
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				it.second.forward(time);
				return;
			}
		}
		LOG(LogLevel::Warning, "TimerManager::forwardTimer : trying to forward unknown timer '" + name + "'.");
	}

	void TimerManager::forwardAllTimers(float64 time)
	{
		for (auto& it : m_TimerContainer)
		{
			it.second.forward(time);
		}
	}

	int32 TimerManager::getTimerMinutes(const tstring& name) const
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.getCurrentMinutes();
			}
		}
		LOG(LogLevel::Warning, "TimerManager::getTimerMinutes : couldn't find the timer '" + name + "'.");
		return 0;
	}

	int32 TimerManager::getTimerSeconds(const tstring& name) const
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.getCurrentSeconds();
			}
		}
		LOG(LogLevel::Warning, "TimerManager::getTimerMinutes : couldn't find the timer '" + name + "'.");
	}

	int32 TimerManager::getTimerTotalSeconds(const tstring& name) const
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.getCurrentTotalSeconds();
			}
		}
		LOG(LogLevel::Warning, "TimerManager::getTimerMinutes : couldn't find the timer '" + name + "'.");
	}

	float64 TimerManager::getTimerTargetTime(const tstring& name) const
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.getTargetTime();
			}
		}
		LOG(LogLevel::Warning, "TimerManager::getTimerMinutes : couldn't find the timer '" + name + "'.");
		return 0;
	}

	float64 TimerManager::getTimerAccurateTime(const tstring& name) const
	{
		for (auto& it : m_TimerContainer)
		{
			if (it.first == name)
			{
				return it.second.getCurrentAccurateTime();
			}
		}
	}
}