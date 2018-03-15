#pragma once
#include <map>
#include "../Utils/Utils.h"
#include "Scene.h"

namespace DS
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void addScene(tstring name, Scene& scene);
		void removeScene(tstring name);

		Scene& getScene(tstring name);
		bool isSceneExist(tstring name);

		void setCurrentScene(tstring name);
		Scene& getCurrentScene();

	private:
		SceneManager() {}
		~SceneManager() {}
		friend Singleton<SceneManager>;

		std::map<tstring, Scene*> m_Scenes;
		Scene* m_CurrentScene;
	};
}