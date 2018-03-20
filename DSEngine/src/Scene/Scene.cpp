#include "Scene.h"
#include "../Object/Object.h"
#include "../Utils/Logger.h"

namespace DS
{
	Scene::Scene()
	{
		//Scene이 생성될 때 실행되어야 할 동작을 기술
	}

	Scene::~Scene()
	{
		//Scene이 소멸될 때 실행되어야 할 동작을 기술
		//엔진 차원에서 소멸될 때 Obejct 컨테이너를 비우도록 함

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
			LOG(LogLevel::Warning, "이미 존재하는 Object를 추가 시도");
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
			LOG(LogLevel::Warning, "존재하지 않는 Object를 삭제 시도");
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
		onUpdate(context); //게임 프로그래머가 update시 해야 할 동작을 적으면 실행됨
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
		onDraw();		//게임 프로그래머가 draw시 해야 할 동작을 적으면 실행됨
	}

	void Scene::collectGarbage()
	{
		for (Object* object : m_GarbageCollector)
		{
			if (!isObjectExist(*object))
			{
				LOG(LogLevel::Error, "오브젝트 제거 오류");
				break;
			}
			m_Objects.erase(object);
		}
		m_GarbageCollector.clear();
	}
}