#include "DSEngine.h"

namespace DS
{
	DSEngine::DSEngine() :
		m_Game(nullptr),
		m_IsInitialized(false),
		m_IsRunning(false)
	{

	}

	DSEngine::~DSEngine()
	{
		
	}

	void DSEngine::initialize(BaseGame& game, Scene& initialScene, const std::string &sceneName)
	{
		initialize(game, initialScene, std::move(sceneName));
	}

	void DSEngine::initialize(BaseGame& game, Scene& initialScene, const std::string &&sceneName)
	{
		if (m_IsInitialized) //중복 초기화 검사
		{
			LOG(LogLevel::Warning, "엔진 중복 초기화");
			return;
		}

		//싱글턴 객체 생성
		Logger::createInstance();
		SceneManager::createInstance();

		m_Game = &game;

		Logger::getInstance().initialize(false);

		//게임 객체 초기화
		m_Game->initialize();

		SceneManager::getInstance().addScene(sceneName, initialScene);
		SceneManager::getInstance().setCurrentScene(sceneName);

	}

	void DSEngine::run()
	{
		while (m_IsRunning)
		{
			Window::getInstance().peekMessage();

			m_Game->update();

			SceneManager::getInstance().getCurrentScene().update(1.0f);

			m_Game->draw();

			SceneManager::getInstance().getCurrentScene().draw();
		}
	}

	void DSEngine::goodBye()
	{
		m_IsRunning = false;
		Logger::destroyInstance();
		SceneManager::destroyInstance();
	}
}