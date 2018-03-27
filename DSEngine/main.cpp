#include <iostream>
#define LOG_MIN_LEVEL 1
#include "src\Defines.h"
#include "src\DSEngine.h"
#include "src\Object\Object.h"
#include "src\Component\SquareComponent.h"

using namespace std;
class TestObject : public DS::Object
{
public:
	TestObject() { addComponent(*(new DS::SquareComponent())); }
protected:
	virtual void onUpdate(DS::Context& context) override {}
};

class TestScene : public DS::Scene
{
public:
	TestScene() { addObject(*(new TestObject())); }
protected:
	virtual void onUpdate(DS::Context& context) override {}
};

class TestGame : public DS::BaseGame
{
protected:
	virtual void onInitialize() override 
	{ 
		DS::SceneManager::getInstance().addScene("test", *(new TestScene()));
		DS::SceneManager::getInstance().setCurrentScene("test");
	}
	virtual void onUpdate(DS::Context& context) override {}
	virtual void onDraw() override {}
	virtual void onDestroy() override {}
};

int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR cmdString, int show)
{
	DS::DSEngine::createInstance();

	DS::DSEngine::getInstance().initialize(*(new TestGame()), instanceHandle, { 800, 600 });

	DS::DSEngine::getInstance().run();

	return 0;
}