#include "BaseGame.h"

namespace DS
{
	void BaseGame::initialize()
	{
		onInitialize();
	}

	void BaseGame::update(Context& context)
	{
		onUpdate(context);
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