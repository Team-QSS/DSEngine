#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"

using namespace std;

class TestGame : public DS::BaseGame
{
	void onInitialize() 
	{
		LOG(DS::LogLevel::Info, "Game Initialize 호출");
	}
	void onUpdate() 
	{
		LOG(DS::LogLevel::Info, "Game Update 호출");
	}
	void onDraw() 
	{
		LOG(DS::LogLevel::Info, "Game Draw 호출");
	}
	void onDestroy() 
	{
		LOG(DS::LogLevel::Info, "Game Destroy 호출");
	}
};

int main()
{
	DS::DSEngine::createInstance();

	auto engine = DS::DSEngine::getInstance();
	engine.initialize(*(new TestGame()));
	engine.run();

	return 0;
}