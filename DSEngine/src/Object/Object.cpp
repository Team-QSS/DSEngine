#include "Object.h"
#include "../Component/Component.h"


namespace DS
{
	Object::Object():
		m_IsActive(true),
		m_IsVisible(true),
		m_Scene(nullptr),
		m_Parent(nullptr)
	{

	}

	Object::~Object()
	{

	}

	Object::Garbage::Garbage(Object::GarbageType type, void* element) :
		type(type),
		element(element)
	{

	}

	bool Object::isActive() const
	{
		return m_IsActive;
	}

	bool Object::isVisible() const
	{
		return m_IsVisible;
	}

	Scene& Object::getScene() const
	{
		return *m_Scene;
	}

	void Object::update(float deltaTime)
	{
		collectGarbage();

		if (!m_IsActive) return;

		onUpdate(deltaTime);

		for (Component* component : m_Components)
		{
			component->update(deltaTime);
		}

		for (Object* child : m_Children)
		{
			child->update(deltaTime);
		}
	}

	void Object::draw()
	{
		if (!m_IsVisible) return;

		onDraw();

		for (Component* component : m_Components)
		{
			component->draw();
		}

		for (Object* child : m_Children)
		{
			child->draw();
		}
	}

	void Object::addComponent(Component& component)
	{
		if (m_Components.count(&component) > 0)
		{
			LOG(LogLevel::Warning, "�ִ� ������Ʈ�� �ٽ� �߰��Ϸ��� �õ���");
			return;
		}

		m_Components.insert(&component);
	}

	void Object::removeComponent(Component& component)
	{
		if (m_Components.count(&component) < 1)
		{
			LOG(LogLevel::Warning, "���� ������Ʈ�� �����Ϸ��� �õ���");
			return;
		}

		m_GarbageCollector.push_back(Garbage(GarbageType::ComponentType, static_cast<void*>(&component)));
	}

	void Object::addChild(Object& object)
	{
		if (m_Children.count(&object) > 0)
		{
			LOG(LogLevel::Warning, "�ִ� ���ϵ带 �ٽ� �߰��Ϸ��� �õ���");
			return;
		}

		m_Children.insert(&object);
	}

	void Object::removeChild(Object& object)
	{
		if (m_Children.count(&object) < 1)
		{
			LOG(LogLevel::Warning, "���� ���ϵ带 �����Ϸ��� �õ���");
			return;
		}

		m_GarbageCollector.push_back(Garbage(GarbageType::ObjectType, static_cast<void*>(&object)));
	}

	const std::set<Object*>& Object::getChildren() const
	{
		return m_Children;
	}

	bool Object::isChildExist(Object& object)
	{
		if (m_Children.count(&object) > 0) return true;
		else return false;
	}

	void Object::setActive(bool active)
	{
		m_IsActive = active;
	}

	void Object::setVisible(bool visible)
	{
		m_IsVisible = visible;
	}

	void Object::setScene(Scene* scene)
	{
		m_Scene = scene;
	}

	void Object::setParent(Object* object)
	{
		m_Parent = object;
	}

	void Object::collectGarbage()
	{
		for (Garbage garbage : m_GarbageCollector)
		{
			switch (garbage.type)
			{
			case GarbageType::ComponentType:
				Component* component = reinterpret_cast<Component *>(garbage.element);

				if (m_Components.count(component) < 1)
				{
					LOG(LogLevel::Error, "������Ʈ���� ����");
					break;
				}

				m_Components.erase(component);
				break;
			case GarbageType::ObjectType:

				Object* object = reinterpret_cast<Object *>(garbage.element);

				if (m_Children.count(object) < 1)
				{
					LOG(LogLevel::Error, "���ϵ� ���� ����");
					break;
				}

				m_Children.erase(object);
				break;
			}
		}
	}

}