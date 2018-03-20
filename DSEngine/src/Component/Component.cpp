#include "Component.h"

namespace DS
{
	Component::Component()
	{

	}

	Component::~Component()
	{

	}

	void Component::update(Context& context)
	{
		onUpdate(context);
	}

	void Component::draw()
	{
		onDraw();
	}
}