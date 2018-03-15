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

	void DSEngine::initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize, Scene& initialScene, tstring sceneName)
	{
		if (m_IsInitialized) //중복 초기화 검사
		{
			LOG(LogLevel::Warning, "엔진 중복 초기화");
			return;
		}

		//싱글턴 객체 생성
		Logger::createInstance();
		SceneManager::createInstance();
		Window::createInstance();
		InputManager::createInstance();
		GraphicsManager::createInstance();

		m_Game = &game;

		Logger::getInstance().initialize(false, true);
		Window::getInstance().initialize(instanceHandle, windowSize);
		GraphicsManager::getInstance().initialize(Window::getInstance().getHandle(), windowSize, false);

		//게임 객체 초기화
		m_Game->initialize();

		SceneManager::getInstance().addScene(sceneName, initialScene);
		SceneManager::getInstance().setCurrentScene(sceneName);

		m_IsRunning = true;
	}

	void DSEngine::run()
	{
		while (m_IsRunning)
		{
			InputManager::getInstance().update();

			Window::getInstance().peekMessage();

			m_Game->update(m_GameContext);

			SceneManager::getInstance().getCurrentScene().update(1.0f);

			m_Game->draw();

			GraphicsManager::getInstance().draw();

			SceneManager::getInstance().getCurrentScene().draw();
		}
	}

	void DSEngine::goodBye()
	{
		m_IsRunning = false;
		GraphicsManager::destroyInstance();
		InputManager::destroyInstance();
		Window::destroyInstance();
		Logger::destroyInstance();
		SceneManager::destroyInstance();
	}
}