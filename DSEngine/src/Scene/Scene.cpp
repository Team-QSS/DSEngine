#include "Scene.h"
#include "../Object/Object.h"

namespace DS
{
	void Scene::addObject(Object& object)
	{
		m_Objects.insert(&object);
	}

	void Scene::removeObject(Object& object)
	{
		m_Objects.erase(&object);
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

	void Scene::update(float deltaTime)
	{
		for (Object* o : m_Objects)
		{
			if (o->isActive()) 
			{
				o->update(deltaTime);
			}
		}
		onUpdate(deltaTime); //게임 프로그래머가 update시 해야 할 동작을 적으면 실행됨
	}
	
	void Scene::draw() 
	{
		for (Object* o : m_Objects) 
		{
			if (o->isVisible) 
			{
				o->draw();
			}
		}
		onDraw();		//게임 프로그래머가 draw시 해야 할 동작을 적으면 실행됨
	}
}