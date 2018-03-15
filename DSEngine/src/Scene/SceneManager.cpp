#include "SceneManager.h"
#include <utility>
#include "../Utils/Logger.h"

namespace DS
{
	void SceneManager::addScene(tstring name, Scene& scene)
	{
		if (!isSceneExist(name))
		{
			m_Scenes.insert(make_pair(name, &scene));
		}
		else
		{
			LOG(LogLevel::Warning, "이미 존재하는 Scene을 추가 시도");
		}		
	}

	void SceneManager::removeScene(tstring name)
	{
		if (isSceneExist(name))
		{
			m_Scenes.erase(name);
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 삭제 시도");
		}
		
	}

	Scene& SceneManager::getScene(tstring name)
	{
		if (isSceneExist(name))
		{
			return *m_Scenes[name];		//name에 해당되는 Scene이 있으면 객체를
		}
		else
		{
			LOG(LogLevel::Warning, "존재하지 않는 Scene을 Get 하려고 함");
			nullptr;					//없으면 null을 리턴한다
		}
	}

	bool SceneManager::isSceneExist(tstring name) 
	{
		auto iter = m_Scenes.find(name);

		if (iter != m_Scenes.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SceneManager::setCurrentScene(tstring name) 
	{
		m_CurrentScene = &getScene(name);
	}
	
	Scene& SceneManager::getCurrentScene()
	{
		return *m_CurrentScene;
	}
}