#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"

using namespace std;

class TestGame : public DS::BaseGame
{
	void onInitialize() 
	{
		LOG(DS::LogLevel::Info, "Game Initialize ȣ��");
	}
	void onUpdate() 
	{
		LOG(DS::LogLevel::Info, "Game Update ȣ��");
	}
	void onDraw() 
	{
		LOG(DS::LogLevel::Info, "Game Draw ȣ��");
	}
	void onDestroy() 
	{
		LOG(DS::LogLevel::Info, "Game Destroy ȣ��");
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