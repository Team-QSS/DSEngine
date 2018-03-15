#include "Timer.h"
#include "Context.h"
#include "../Utils.h"

namespace DS
{
	Timer::Timer() :
		m_TargetTime(1.0f),
		m_CurrentTime(0),
		m_CountingDown(false),
		m_Looping(false),
		m_Paused(false),
		m_Infinite(false),
		m_ExcecutingFunction(nullptr)
	{

	}
	Timer::Timer(float64 targetTime, bool countingDown, bool loop,
			std::function<void()> func, bool paused) :
		m_TargetTime(1.0f),
		m_CurrentTime(0),
		m_CountingDown(false),
		m_Looping(false),
		m_Paused(false),
		m_Infinite(false),
		m_ExcecutingFunction(nullptr)
	{

	}
	
	

	Timer::Timer(const Timer& yRef) :
		m_TargetTime(yRef.m_TargetTime),
		m_CurrentTime(yRef.m_CurrentTime),
		m_CountingDown(yRef.m_CountingDown),
		m_Looping(yRef.m_Looping),
		m_Paused(yRef.m_Paused),
		m_Infinite(yRef.m_Infinite),
		m_ExcecutingFunction(yRef.m_ExcecutingFunction)
	{
		
	}
	
	Timer::Timer(Timer&& yRef) :
		m_TargetTime(std::move(yRef.m_TargetTime)),
		m_CurrentTime(std::move(yRef.m_CurrentTime)),
		m_CountingDown(std::move(yRef.m_CountingDown)),
		m_Looping(std::move(yRef.m_Looping)),
		m_Paused(std::move(yRef.m_Paused)),
		m_Infinite(std::move(yRef.m_Infinite)),
		m_ExcecutingFunction(std::move(yRef.m_ExcecutingFunction))
	{

	}

	Timer::~Timer()
	{

	}

	Timer& Timer::operator= (const Timer& yRef)
	{
		m_TargetTime = yRef.m_TargetTime;
		m_CurrentTime = yRef.m_CurrentTime;
		m_CountingDown = yRef.m_CountingDown;
		m_Looping = yRef.m_Looping;
		m_Paused = yRef.m_Paused;
		m_Infinite = yRef.m_Infinite;
		m_ExcecutingFunction = yRef.m_ExcecutingFunction;
		return *this;
	}

	Timer& Timer::operator= (Timer&& yRef)
	{
		m_TargetTime = std::move(yRef.m_TargetTime);
		m_CurrentTime = std::move(yRef.m_CurrentTime);
		m_CountingDown = std::move(yRef.m_CountingDown);
		m_Looping = std::move(yRef.m_Looping);
		m_Paused = std::move(yRef.m_Paused);
		m_Infinite = std::move(yRef.m_Infinite);
		m_ExcecutingFunction = std::move(yRef.m_ExcecutingFunction);
		return *this;
	}

	bool Timer::update(const Context& context)
	{
		if (m_Paused)
		{
			return false;
		}

		if (m_CountingDown && m_CurrentTime >= 0)
		{
			m_CurrentTime -= context.time->deltaTime().getSeconds();
			if (m_CurrentTime < 0)
			{
				m_ExcecutingFunction();
				if (m_Looping)
				{
					Reset(false);
					return false;
				}
				return true;
			}
			return false;
		}
		else if (!m_CountingDown && m_CurrentTime <= m_TargetTime)
		{
			m_CurrentTime += context.time->deltaTime().getSeconds();
			if (m_CurrentTime > m_TargetTime)
			{
				m_ExcecutingFunction();
				if (m_Looping)
				{
					Reset(false);
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}

	void Timer::setPaused(bool paused)
	{
		m_Paused = paused;
	}

	void Timer::setCountingDown(bool countingDown)
	{
		m_CountingDown = countingDown;
	}

	void Timer::setLoop(bool looping)
	{
		m_Looping = looping;
	}

	void Timer::Reset(bool paused)
	{
		m_CurrentTime = m_CountingDown ? m_TargetTime : 0;
		setPaused(paused);
	}

	void Timer::setTargetTime(float64 targetTime, const bool reset, const bool paused)
	{
		m_TargetTime = targetTime;
		if (reset)
		{
			Reset(paused);
		}
	}

	void Timer::setFunction(const std::function<void()>& func)
	{
		m_ExcecutingFunction = func;
	}

	int32 Timer::getCurrentMinutes() const
	{
		int32 currentTime(0);
		currentTime = (int32)m_CurrentTime;
		return currentTime / 60;
	}

	int32 Timer::getCurrentSeconds() const
	{
		int32 currentTime(0);
		currentTime = (int32)m_CurrentTime;
		return currentTime % 60;
	}
	int32 Timer::getCurrentTotalSeconds() const
	{
		int32 currentTime(0);
		currentTime = (int32)m_CurrentTime;
		return currentTime;
	}

	float64 Timer::getTargetTime() const
	{
		return m_TargetTime;
	}

	float64 Timer::getCurrentAccurateTime() const
	{
		return m_CurrentTime;
	}

	float64 Timer::forceEnd()
	{
		float64 rest(m_CurrentTime);
		
		if (!m_CountingDown)
		{
			rest = m_TargetTime - rest;
		}
		m_CurrentTime = m_CountingDown ? 0 : m_TargetTime; //�� ���ǹ��� ������ update���� false�� ��ȯ��
		return rest;	//���� �ð� ����
	}

	void Timer::forward(float64 time)	 //�ð�����
	{
		if (m_CountingDown)
		{
			m_CurrentTime -= time;
		}
		else
		{
			m_CurrentTime += time;
		}
	}
}