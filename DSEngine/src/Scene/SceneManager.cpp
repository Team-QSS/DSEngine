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
			LOG(LogLevel::Warning, "�̹� �����ϴ� Scene�� �߰� �õ�");
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
			LOG(LogLevel::Warning, "�������� �ʴ� Scene�� ���� �õ�");
		}
		
	}

	Scene& SceneManager::getScene(tstring name)
	{
		if (isSceneExist(name))
		{
			return *m_Scenes[name];		//name�� �ش�Ǵ� Scene�� ������ ��ü��
		}
		else
		{
			LOG(LogLevel::Warning, "�������� �ʴ� Scene�� Get �Ϸ��� ��");
			nullptr;					//������ null�� �����Ѵ�
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