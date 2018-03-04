#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"

using namespace std;

class TestGame : public DS::BaseGame
{
protected:
	virtual void onInitialize() override {}
	virtual void onUpdate() override {}
	virtual void onDraw() override {}
	virtual void onDestroy() override {}
};

class TestScene : public DS::Scene
{
protected:
	virtual void onUpdate(float deltaTime) override {}
};

int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR cmdString, int show)
{
	DS::DSEngine::createInstance();

	auto engine = DS::DSEngine::getInstance();

	engine.initialize(*(new TestGame()), instanceHandle, { 800, 600 }, *(new TestScene()), "test");

	engine.run();

	return 0;
}