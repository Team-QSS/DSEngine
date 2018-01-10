#include "Component.h"

namespace DS
{
	Component::Component()
	{

	}

	Component::~Component()
	{

	}

	void Component::update(float deltaTime)
	{
		onUpdate(deltaTime);
	}

	void Component::draw()
	{
		onDraw();
	}
}