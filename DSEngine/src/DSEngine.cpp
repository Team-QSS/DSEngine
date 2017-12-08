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
		if (m_IsInitialized) //�ߺ� �ʱ�ȭ �˻�
		{
			LOG(LogLevel::Warning, "���� �ߺ� �ʱ�ȭ");
			return;
		}

		//�̱��� ��ü ����
		Logger::createInstance();

		m_Game = &game;

		//���� ��ü �ʱ�ȭ
		m_Game->initialize();

	}

	void DSEngine::run()
	{
		while (m_IsRunning)
		{
			m_Game->update();
			m_Game->draw();
		}
	}

	void DSEngine::goodBye()
	{
		Logger::destroyInstance();
	}
}