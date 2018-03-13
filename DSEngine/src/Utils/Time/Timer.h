#pragma once

#include "..\..\Defines.h"
#include <functional>

namespace DS
{
	struct Context;
	
	class Timer final
	{
	private:
		Timer();
		Timer(float64 targetTime, bool countingDown, bool loop, std::function<void()> func, bool puased = false);
		Timer(const Timer& yRef);
		Timer(Timer&& yRef);
		
		~Timer();

		Timer& operator= (const Timer& yRef);
		Timer& operator= (Timer&& yRef);

		bool update(const Context& context);
		void setPaused(bool paused);
		void setCountingDown(bool countingDown);
		void setLoop(bool looping);
		void Reset(bool paused = false);
		void setTargetTime(float64 targetTime, bool reset = true, bool paused = false);
		void setFunction(const std::function<void()>& func);
		float64 forceEnd();
		void forward(float64 time);

		int32 getCurrentMinutes() const;
		int32 getCurrentSeconds() const;
		int32 getCurrentTotalSeconds() const;
		float64 getTargetTime() const;
		float64 getCurrentAccurateTime() const;

	private:
		friend class TimerManager;

		float64 m_TargetTime;
		float64 m_CurrentTime;
		bool m_CountingDown;
		bool m_Looping;
		bool m_Paused;
		bool m_Infinite;
		std::function<void()> m_ExcecutingFunction;
	};
}