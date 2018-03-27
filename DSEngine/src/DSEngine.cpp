#include "DSEngine.h"
#include "Graphics\ShaderManager.h"

namespace DS
{
	DSEngine::DSEngine() :
		m_Game(nullptr),
		m_IsInitialized(false),
		m_IsRunning(false),
		m_InputManager(nullptr),
		m_Window(nullptr),
		m_SceneManager(nullptr),
		m_GraphicsManager(nullptr)
	{
		
	}

	DSEngine::~DSEngine()
	{
		
	}

	void DSEngine::initialize(BaseGame& game, HINSTANCE instanceHandle, DirectX::XMINT2 windowSize)
	{
		if (m_IsInitialized) //중복 초기화 검사
		{
			LOG(LogLevel::Warning, "엔진 중복 초기화");
			return;
		}

		//싱글턴 객체 생성
		Logger::createInstance();
		Logger::getInstance().initialize(false, true);

		SceneManager::createInstance();
		Window::createInstance();
		InputManager::createInstance();
		GraphicsManager::createInstance();
		TimeManager::createInstance();

		m_Game = &game;

		Window::getInstance().initialize(instanceHandle, windowSize);
		GraphicsManager::getInstance().initialize(Window::getInstance().getHandle(), windowSize, false);

		ShaderManager::createInstance();

		m_InputManager = &InputManager::getInstance();
		m_Window = &Window::getInstance();
		m_SceneManager = &SceneManager::getInstance();
		m_GraphicsManager = &GraphicsManager::getInstance();

		m_Context.time = &TimeManager::getInstance();

		//게임 객체 초기화
		m_Game->initialize();

		m_IsRunning = true;
	}

	void DSEngine::run()
	{
		while (m_IsRunning)
		{
			DSEngine::update();
			DSEngine::draw();
		}
	}

	void DSEngine::update()
	{
		m_FPS.update(m_Context);
		m_InputManager->update();
		m_Window->peekMessage();
		m_Game->update(m_Context);
		m_SceneManager->getCurrentScene().update(m_Context);
	}

	void DSEngine::draw()
	{
		m_GraphicsManager->beginDraw();
		m_Game->draw();
		m_SceneManager->getCurrentScene().draw();
		m_GraphicsManager->endDraw();
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