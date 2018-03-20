#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"
#include "src\DSEngine.h"

using namespace std;

class TestGame : public DS::BaseGame
{
protected:
	virtual void onInitialize() override {}
	virtual void onUpdate(DS::Context& context) override {}
	virtual void onDraw() override {}
	virtual void onDestroy() override {}
};

class TestScene : public DS::Scene
{
protected:
	virtual void onUpdate(DS::Context& context) override {}
};

int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR cmdString, int show)
{
	DS::DSEngine::createInstance();

	DS::DSEngine::getInstance().initialize(*(new TestGame()), instanceHandle, { 800, 600 }, *(new TestScene()), "test");

	DS::DSEngine::getInstance().run();

	return 0;
}