#include "Time.h"

namespace DS
{
	const float64 Time::NANO_TO_SECONDS = 1.0e-9;
	const float64 Time::NANO_TO_MILLISECNODS = 1.0e-6;
	const float64 Time::NANO_TO_MICROSECNODS = 1.0e-3;

	Time::Time()
		: m_Duration()
	{
		
	}
	Time::Time(const Time& t)
		: m_Duration(t.m_Duration)
	{
		
	}

	Time::Time(Time&& t)
		: m_Duration(t.m_Duration)
	{

	}

	Time::~Time()
	{
		
	}

	Time& Time::operator= (const Time& t)
	{
		m_Duration = t.m_Duration;
		return *this;
	}

	Time& Time::operator= (Time&& t)
	{
		m_Duration = t.m_Duration;
		return *this;
	}

	Time& Time::operator+= (const Time& t)
	{
		m_Duration += t.m_Duration;
		return *this;
	}

	Time& Time::operator-= (const Time& t)
	{
		m_Duration -= t.m_Duration;
		return *this;
	}

	Time& Time::operator*= (const std::chrono::system_clock::duration::rep& t)
	{
		m_Duration *= t;
		return *this;
	}

	Time& Time::operator/= (const std::chrono::system_clock::duration::rep& t)
	{
		m_Duration /= t;
		return *this;
	}

	Time& Time::operator%= (const std::chrono::system_clock::duration::rep& t)
	{
		m_Duration %= t;
		return *this;
	}

	Time& Time::operator%= (const Time& t)
	{
		m_Duration %= t.m_Duration;
		return *this;
	}

	Time Time::operator+ (const Time& t) const
	{
		Time time(*this);
		time += t;
		return time;
	}

	Time Time::operator- (const Time& t) const
	{
		Time time(*this);
		time -= t;
		return time;
	}

	Time& Time::operator++ ()
	{
		++m_Duration;
		return *this;
	}

	Time Time::operator++ (int32)
	{
		Time time(*this);
		time.m_Duration++;
		return time;
	}

	Time& Time::operator-- ()
	{
		--m_Duration;
		return *this;
	}

	Time Time::operator-- (int32)
	{
		Time time(*this);
		time.m_Duration--;
		return time;
	}

	float64 Time::getHours() const
	{
		return getSeconds() / 3600.0;
	}

	float64 Time::getMinutes() const
	{
		return getSeconds() / 60.0;
	}
	
	float64 Time::getSeconds() const
	{
		return getNanoSeconds() * NANO_TO_SECONDS;
	}

	float64 Time::getMilliSeconds() const
	{
		return getNanoSeconds() * NANO_TO_MILLISECNODS;
	}

	float64 Time::getMicroSeconds() const
	{
		return getNanoSeconds() * NANO_TO_MICROSECNODS;
	}

	float64 Time::getNanoSeconds() const
	{
		//여기서 오류가 날 리가 없어요 - Splash
		return float64(std::chrono::duration_cast<std::chrono::nanoseconds>(m_Duration).count());
	}
}