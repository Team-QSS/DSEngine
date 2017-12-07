#include "BaseGame.h"

namespace DS
{
	void BaseGame::initialize()
	{
		onInitialize();
	}

	void BaseGame::update()
	{
		onUpdate();
	}

	void BaseGame::draw()
	{
		onDraw();
	}

	void BaseGame::destroy()
	{
		onDestroy();
	}
}