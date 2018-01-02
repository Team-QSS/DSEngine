#include "SceneManager.h"
#include <utility>

namespace DS
{
	void SceneManager::addScene(std::string name, Scene& scene)
	{
		m_Scenes.insert(make_pair(name, &scene));
	}

	void SceneManager::removeScene(std::string name)
	{
		m_Scenes.erase(name);
	}

	Scene* SceneManager::getScene(std::string name)
	{
		if (isSceneExist(name))
		{
			return m_Scenes[name];		//name에 해당되는 Scene이 있으면 객체를
		}
		else
		{
			nullptr;					//없으면 null을 리턴한다
		}
	}

	bool SceneManager::isSceneExist(std::string name) 
	{
		auto iter = m_Scenes.find(name);

		if (iter != m_Scenes.end)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SceneManager::setCurrentScene(std::string name) 
	{
		m_CurrentScene = *getScene(name);
	}
	Scene& SceneManager::getCurrentScene()
	{
		return m_CurrentScene;
	}
}