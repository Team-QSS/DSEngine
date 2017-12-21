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

	void DSEngine::initialize(BaseGame& game)
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

		//게임 객체 초기화
		m_Game->initialize();

	}

	void DSEngine::run()
	{
		while (m_IsRunning)
		{
			m_Game->update();

			SceneManager::getInstance().getCurrentScene().update(1.0f);

			m_Game->draw();

			SceneManager::getInstance().getCurrentScene().draw();
		}
	}

	void DSEngine::goodBye()
	{
		Logger::destroyInstance();
		SceneManager::destroyInstance();
	}
}