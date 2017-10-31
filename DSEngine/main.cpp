#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"
#include "src\Utils\Utils.h"

using namespace std;

int main()
{
	DS::Logger::createInstance();
	DS::Logger::getInstance().initialize(true);
	LOG(DS::LogLevel::Info, "Log 1");

	DS::Logger::destroyInstance();
	return 0;
}