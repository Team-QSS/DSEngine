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

	void DSEngine::initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize, Scene& initialScene, std::string sceneName)
	{
		if (m_IsInitialized) //�ߺ� �ʱ�ȭ �˻�
		{
			LOG(LogLevel::Warning, "���� �ߺ� �ʱ�ȭ");
			return;
		}

		//�̱��� ��ü ����
		Logger::createInstance();
		SceneManager::createInstance();
		Window::createInstance();
		InputManager::createInstance();

		m_Game = &game;

		Logger::getInstance().initialize(false, true);
		Window::getInstance().initialize(instanceHandle, windowSize);

		//���� ��ü �ʱ�ȭ
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

			m_Game->update();

			SceneManager::getInstance().getCurrentScene().update(1.0f);

			m_Game->draw();

			SceneManager::getInstance().getCurrentScene().draw();
		}
	}

	void DSEngine::goodBye()
	{
		m_IsRunning = false;
		InputManager::destroyInstance();
		Window::destroyInstance();
		Logger::destroyInstance();
		SceneManager::destroyInstance();
	}
}