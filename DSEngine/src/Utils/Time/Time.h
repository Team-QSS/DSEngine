#pragma once

#include <chrono>
#include "..\..\Defines.h"

namespace DS
{
	class Time final
	{
	public:
		Time();
		Time(const Time& t);
		Time(Time&& t);
		~Time();

		Time& operator= (const Time& t);
		Time& operator= (Time&& t);

		Time& operator+= (const Time& t);
		Time& operator-= (const Time& t);
		Time& operator*= (const std::chrono::system_clock::duration::rep& t);
		Time& operator/= (const std::chrono::system_clock::duration::rep& t);
		Time& operator%= (const std::chrono::system_clock::duration::rep& t);
		Time& operator%= (const Time& t);

		Time operator+ (const Time& t) const;
		Time operator- (const Time& t) const;

		Time& operator++();
		Time operator++(int32 t);
		Time& operator--();
		Time operator--(int32 t);

		float64 getHours() const;
		float64 getMinutes() const;
		float64 getSeconds() const;
		float64 getMilliSeconds() const;
		float64 getMicroSeconds() const;
		float64 getNanoSeconds() const;

	private:
		friend class TimeManager;
		friend class Stopwatch;

		std::chrono::high_resolution_clock::duration m_Duration;

		static const float64 NANO_TO_SECONDS;
		static const float64 NANO_TO_MILLISECNODS;
		static const float64 NANO_TO_MICROSECNODS;
	};
}