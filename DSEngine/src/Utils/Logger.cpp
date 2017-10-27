#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <ctime>

namespace DS
{
	Logger::~Logger()
	{
		writeLogFile();
	}

	void Logger::initialize(bool useConsole)
	{
		m_UseConsole = useConsole;
	}

	void Logger::log(LogLevel level, const std::string& message, const BreakInfo& breakInfo)
	{
		log(level, "DSEngine", message, breakInfo);
	}

	void Logger::log(LogLevel level, const std::string& tag, const std::string& message, const BreakInfo& breakInfo)
	{
		std::stringstream logText;
		switch (level)
		{
		case LogLevel::Info:
			logText << "[Info]";
			break;
		case LogLevel::Warning:
			logText << "[Warning]";
			break;
		case LogLevel::Error:
			logText << "[Error]";
			break;
		case LogLevel::Debug:
			logText << "[Debug]";
			break;
		}

		logText << "[" << tag << "]" << message << std::endl;
		logText << "File : " << breakInfo.file << std::endl;
		logText << "Line : " << breakInfo.line << std::endl;

		switch (level)
		{
		case LogLevel::Info:
#if LOG_MIN_LEVEL <= 1
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Warning:
#if LOG_MIN_LEVEL <= 2
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Error:
#if LOG_MIN_LEVEL <= 3
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		case LogLevel::Debug:
#if LOG_MIN_LEVEL <= 4
			if (m_UseConsole)
			{
				std::cout << logText.str();
			}
			else
			{
				OutputDebugStringA(logText.str().c_str());
			}
			m_LogBuffer << logText.str();
#endif
			break;
		}
	}

	void Logger::writeLogFile()
	{
		if (!(m_LogBuffer.beg == m_LogBuffer.cur))
		{
			std::chrono::system_clock::time_point curTimePoint = std::chrono::system_clock::now();
			time_t curTimet = std::chrono::system_clock::to_time_t(curTimePoint);
			tm* curTime = new tm();
			localtime_s(curTime, &curTimet);

			char curTimeBuffer[30];
			strftime(curTimeBuffer, sizeof(curTimeBuffer), "%y/%m/%d-%X", curTime);
			std::ofstream logFileStream("./Log-" + std::string(curTimeBuffer));

			std::cout << "Log-" + std::string(curTimeBuffer) << std::endl << m_LogBuffer.str() << std::endl;
			logFileStream << m_LogBuffer.str() << std::endl;
			m_LogBuffer.clear();
			logFileStream.close();

			delete curTime;
		}
	}
}