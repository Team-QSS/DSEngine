#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <ctime>
#include <cstdio>

namespace DS
{
	Logger::~Logger()
	{
		writeLogFile();
	}

	void Logger::initialize(bool useConsole, bool useFile)
	{
		m_UseConsole = useConsole;
		m_UseFile = useFile;
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
		if (!(m_LogBuffer.beg == m_LogBuffer.cur) && m_UseFile)
		{
			std::chrono::system_clock::time_point curTimePoint = std::chrono::system_clock::now();
			time_t curTimet = std::chrono::system_clock::to_time_t(curTimePoint);
			tm* curTime = new tm();
			localtime_s(curTime, &curTimet);

			try
			{
				char curTimeBuffer[60] = { 0 };
				strftime(curTimeBuffer, sizeof(curTimeBuffer), "Log%y-%m-%d-%H-%M-%S.txt", curTime);
				std::ofstream logFileStream;
				logFileStream.exceptions(std::ios::failbit | std::ios::eofbit | std::ios::badbit);
				std::cout << "Log-" + std::string(curTimeBuffer) << std::endl << m_LogBuffer.str() << std::endl;
				logFileStream.open(std::string(curTimeBuffer));

				logFileStream << m_LogBuffer.str() << std::endl;
				m_LogBuffer.clear();
				logFileStream.close();
			}
			catch (const std::ios_base::failure& e)
			{
				LOG(LogLevel::Error, e.what())
			}


			//char curTimeBuffer[60];
			//strftime(curTimeBuffer, sizeof(curTimeBuffer), "%y/%m/%d-%X", curTime);

			//FILE* fp;
			//fopen_s(&fp, std::string("Log-" + std::string(curTimeBuffer) + ".txt").c_str(), "wt");

			//fprintf_s(fp, "%s\n", m_LogBuffer.str().c_str());

			//fclose(fp);

			delete curTime;
		}
	}
}