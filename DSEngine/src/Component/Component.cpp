#include "Component.h"

namespace DS
{
	Component::Component() :
		m_Parent(nullptr)
	{

	}

	Component::~Component()
	{

	}

	Object& Component::getParent() const
	{
		return *(m_Parent);
	}

	void Component::update(Context& context)
	{
		onUpdate(context);
	}

	void Component::draw()
	{
		onDraw();
	}

	void Component::setParent(Object* obj)
	{
		m_Parent = obj;
	}
}