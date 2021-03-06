#pragma once
#include <map>
#include "../Utils/Utils.h"
#include "Scene.h"
#include "../Defines.h"

namespace DS
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		friend Singleton<SceneManager>;
		
		void addScene(std::string name, Scene& scene);
		void removeScene(std::string name);

		Scene& getScene(std::string name);
		bool isSceneExist(std::string name);

		void setCurrentScene(std::string name);
		Scene& getCurrentScene();

	private:
		SceneManager() {}
		~SceneManager() {}

		std::map<tstring, Scene*> m_Scenes;
		Scene* m_CurrentScene;
	};
}