#include "Scene.h"

namespace DS
{
	void Scene::addObject(Object* object)
	{

	}

	void Scene::removeObject(Object* object)
	{

	}

	void Scene::isObjectExist(Object* object)
	{

	}

	void Scene::update(float deltaTime)
	{
		for (Object& o : m_Objects)
		{
			o.update(deltaTime);
		}
	}
}