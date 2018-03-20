#pragma once
#include "..\..\Defines.h"
#include "../Singleton.h"
#include "Timer.h"
#include <map>
#include <functional>

namespace DS
{
	struct Context;
	class Timer;

	class TimerManager final : public Singleton<TimerManager>
	{
	public:
		friend Singleton<TimerManager>;

		/*void update(const Context& context);

		bool createTimer(const tstring& name, float32 targetTime, bool countingDown,
			bool loop, std::function<void()> func, bool paused = false);
		bool removeTimer(const tstring& name);
		void pauseTimer(const tstring& name, bool paused);
		void setCountingDownTimer(const tstring& name, bool countingDown);
		void setLoopTimer(const tstring& name, bool looping);
		void resetTimer(const tstring& name, bool paused = false);
		void setTargetTimeTimer(const tstring& name, float32 targetTime, bool reset, bool paused);
		void setFunctionTimer(const tstring& name, const std::function<void()>& func);
		float64 forceEndTimer(const tstring& name);
		void forwardTimer(const tstring& name, float64 time);
		void forwardAllTimers(float64 time);

		int32 getTimerMinutes(const tstring& name) const;
		int32 getTimerSeconds(const tstring& name) const;
		int32 getTimerTotalSeconds(const tstring& name) const;
		float64 getTimerTargetTime(const tstring& name) const;
		float64 getTimerAccurateTime(const tstring& name) const;
		
	private:
		TimerManager() {};
		~TimerManager() {};

		std::map<const tstring, Timer> m_TimerContainer;
		std::map<const tstring, Timer> m_GarbageContainer;
		

		TimerManager(const TimerManager& yRef) {};
		TimerManager(TimerManager&& yRef) {};
		TimerManager& operator= (const TimerManager& yRef) {};
		TimerManager& operator= (TimerManager&& yRef) {};*/
	};
}