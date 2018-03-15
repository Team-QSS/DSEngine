#pragma once
#include "Utils.h"
#include "../Defines.h"
#include <string>
#include <sstream>

#ifndef LOG_MIN_LEVEL
#define LOG_MIN_LEVEL 1
#endif

namespace DS
{
	enum LogLevel
	{
		Info,
		Warning,
		Error,
		Debug
	};

	struct BreakInfo
	{
		tstring file;
		int line;

		BreakInfo(const tstring& file, int line): file(file), line(line) {}
	};

	class Logger final : public Singleton<Logger>
	{
	public:
		void initialize(bool useConsole, bool useFile = false);

		void log(LogLevel level, const tstring& tag, const tstring& message, const BreakInfo& breakInfo);
		void log(LogLevel level, const tstring& message, const BreakInfo& breakInfo);

		void writeLogFile();


	private:
		Logger() {};
		~Logger();
		friend Singleton<Logger>;

		bool m_UseConsole;
		bool m_UseFile;
		tstringstream m_LogBuffer;
	};
}

#define LOG_WITH_TAG(level, tag, message) \
	DS::Logger::getInstance().log(level, tag, message, DS::BreakInfo(__FILE__, __LINE__));

#define LOG(level, message) \
	DS::Logger::getInstance().log(level, message, DS::BreakInfo(__FILE__, __LINE__));




