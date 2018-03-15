#include "Scene.h"
#include "../Object/Object.h"
#include "../Utils/Logger.h"

namespace DS
{
	Scene::Scene()
	{
		//Scene�� ������ �� ����Ǿ�� �� ������ ���
	}

	Scene::~Scene()
	{
		//Scene�� �Ҹ�� �� ����Ǿ�� �� ������ ���
		//���� �������� �Ҹ�� �� Obejct �����̳ʸ� ��쵵�� ��

		for (Object* o : m_Objects)
		{
			delete o;
		}
		m_Objects.clear();
		m_GarbageCollector.clear();
	}

	void Scene::addObject(Object& object)
	{
		if (!isObjectExist(object))
		{
			m_Objects.insert(&object);
		}
		else
		{
			LOG(LogLevel::Warning, "�̹� �����ϴ� Object�� �߰� �õ�");
		}
	}

	void Scene::removeObject(Object& object)
	{
		if (isObjectExist(object))
		{
			m_GarbageCollector.push_back(&object);
		}
		else
		{
			LOG(LogLevel::Warning, "�������� �ʴ� Object�� ���� �õ�");
		}		
	}

	bool Scene::isObjectExist(Object& object)
	{
		auto iter = m_Objects.find(&object);

		if (iter != m_Objects.end())
		{
			return true;
		}
		else 
		{
			return false;
		}	
	}

	int Scene::objectQuantity() 
	{
		return m_Objects.size();
	}

	void Scene::update(Context& context)
	{
		collectGarbage();

		for (Object* o : m_Objects)
		{
			if (o->isActive()) 
			{
				o->update(context);
			}
		}
		onUpdate(context); //���� ���α׷��Ӱ� update�� �ؾ� �� ������ ������ �����
	}
	
	void Scene::draw() 
	{
		for (Object* o : m_Objects) 
		{
			if (o->isVisible()) 
			{
				o->draw();
			}
		}
		onDraw();		//���� ���α׷��Ӱ� draw�� �ؾ� �� ������ ������ �����
	}

	void Scene::collectGarbage()
	{
		for (Object* object : m_GarbageCollector)
		{
			if (!isObjectExist(*object))
			{
				LOG(LogLevel::Error, "������Ʈ ���� ����");
				break;
			}
			m_Objects.erase(object);
		}
		m_GarbageCollector.clear();
	}
}