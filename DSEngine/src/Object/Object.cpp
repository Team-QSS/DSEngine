#include "Object.h"
#include "../Component/Component.h"
#include "../Component/TransformComponent.h"
#include <utility>
#include <map>
#include <iterator>

using namespace std;

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
		for (Object* o : m_Children)
		{
			delete o;
		}
		m_Children.clear();

		for(auto it = m_Components.begin; it != m_Components.end(); it++)
		{
			delete it[2];
		}
		m_Components.clear();

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

		for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			iter->second->update(deltaTime);
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

		for (auto iter = m_Components.begin(); iter != m_Components.end(); iter++)
		{
			iter->second->draw();
		}

		for (Object* child : m_Children)
		{
			child->draw();
		}
	}

	void Object::addComponent(Component& component)
	{
		if (m_Components.count(typeid(component).name()) > 0)
		{
			LOG(LogLevel::Warning, "�ִ� ������Ʈ�� �ٽ� �߰��Ϸ��� �õ���");
			return;
		}

		m_Components.insert(make_pair(typeid(component).name(), &component));
	}

	void Object::removeComponent(Component& component)
	{
		if (m_Components.count(typeid(component).name()) < 1)
		{
			LOG(LogLevel::Warning, "���� ������Ʈ�� �����Ϸ��� �õ���");
			return;
		}

		m_GarbageCollector.push_back(Garbage(GarbageType::ComponentType, static_cast<void*>(&component)));
	}

	TransformComponent& getTransformComponent()
	{
		return getComponent<TransformComponent>();
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
			Component* component = reinterpret_cast<Component *>(garbage.element);
			Object* object = reinterpret_cast<Object *>(garbage.element);
			switch (garbage.type)
			{
			case GarbageType::ComponentType:
				if (m_Components.count(typeid(component).name()) < 1)
				{
					LOG(LogLevel::Error, "������Ʈ���� ����");
					break;
				}

				m_Components.erase(typeid(component).name());
				delete component;
				break;
			case GarbageType::ObjectType:
				if (isChildExist(*object))
				{
					LOG(LogLevel::Error, "���ϵ� ���� ����");
					break;
				}

				m_Children.erase(object);
				delete object;
				break;
			}
		}

		m_GarbageCollector.clear();
	}

}