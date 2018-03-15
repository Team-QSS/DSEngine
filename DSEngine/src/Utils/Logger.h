#pragma once
#include "Utils.h"
#include "../Defines.h"
#include <string>
#include <sstream>

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
		std::string file;
		int line;

		BreakInfo(const std::string& file, int line): file(file), line(line) {}
	};

	class Logger final : public Singleton<Logger>
	{
	public:
		Logger() {};
		virtual ~Logger();

		void initialize(bool useConsole, bool useFile = false);

		void log(LogLevel level, const std::string& tag, const std::string& message, const BreakInfo& breakInfo);
		void log(LogLevel level, const std::string& message, const BreakInfo& breakInfo);

		void writeLogFile();


	private:
		bool m_UseConsole;
		bool m_UseFile;
		std::stringstream m_LogBuffer;
	};
}

#define LOG_WITH_TAG(level, tag, message) \
	DS::Logger::getInstance().log(level, tag, message, DS::BreakInfo(__FILE__, __LINE__));

#define LOG(level, message) \
	DS::Logger::getInstance().log(level, message, DS::BreakInfo(__FILE__, __LINE__));




