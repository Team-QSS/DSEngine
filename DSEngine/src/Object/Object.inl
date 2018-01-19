#include "Object.h"
#include <typeinfo>
#include "../Utils/Utils.h"

namespace DS
{
	template <typename T>
	void Object::removeComponent()
	{
		if (Object::isComponentExist<T>()) m_GarbageCollector.push_back(Garbage(GarbageType::ComponentType, static_cast<void *>(m_Components[typeid(T).name])));
		else LOG(LogLevel::Warning, "���� ������Ʈ�� ���� �õ���");
	}

	template <typename T>
	T& Object::getComponent() const
	{
		if (Object::isComponentExist<T>()) return *m_Components[typeid(T).name];
		else LOG(LogLevel::Error, "���� ������Ʈ�� �˻� �õ���");

		return nullptr;
	}

	template <typename T>
	bool Object::isComponentExist()
	{
		if (m_Components.count(typeid(T).name) > 0) return true;
		else return false
	}

}