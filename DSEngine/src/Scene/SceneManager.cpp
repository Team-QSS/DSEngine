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
			return m_Scenes[name];		//name�� �ش�Ǵ� Scene�� ������ ��ü��
		}
		else
		{
			nullptr;					//������ null�� �����Ѵ�
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