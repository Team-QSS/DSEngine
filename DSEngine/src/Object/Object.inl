#include "Object.h"
#include <typeinfo>
#include "../Utils/Utils.h"

namespace DS
{
	template <typename T>
	void Object::removeComponent()
	{
		bool result = false;
		std::type_info ti = typeid(T);
		for (Component* component : m_Components)
		{
			if (component && ti == typeid(*component))
			{
				m_GarbageCollector.push_back(Garbage(GarbageType::ComponentType, static_cast<void*>(component)));
				result = true;
			}
		}

		if(!result) LOG(LogLevel::Warning, "���� ������Ʈ�� ���� �õ���")
	}

	template <typename T>
	T& Object::getComponent() const
	{
		std::type_info ti = typeid(T);
		for (Component* component : m_Components)
		{
			if (component && ti == typeid(*component))
			{
				return *component;
			}
		}

		LOG(LogLevel::Warning, "���� ������Ʈ�� �˻� �õ���");

		return nullptr;
	}

	template <typename T>
	bool Object::isComponentExist()
	{
		std::type_info ti = typeid(T);
		for (Component* component : m_Components)
		{
			if (component && ti == typeid(*component))
			{
				return true;
			}
		}

		return false;
	}

}