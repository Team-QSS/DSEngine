#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"

using namespace std;

int main()
{
	DS::DSEngine::createInstance();

	auto engine = DS::DSEngine::getInstance();

	return 0;
}