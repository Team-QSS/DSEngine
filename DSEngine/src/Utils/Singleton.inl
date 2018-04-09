#include "Singleton.h"
#include "Logger.h"

namespace DS
{
	template<typename T>
	T* DS::Singleton<T>::s_Instance = nullptr;

	template<typename T>
	void Singleton<T>::createInstance()
	{
		if (s_Instance != nullptr)
		{
			LOG(LogLevel::Warning, "�̹� �ʱ�ȭ�� �̱��� ��ü �ʱ�ȭ �õ�");
		}
		else
		{
			s_Instance = new T();
		}
	}

	template<typename T>
	T& Singleton<T>::getInstance()
	{
		if (s_Instance == nullptr)
		{
			LOG(LogLevel::Warning, "���ʱ�ȭ ������ �̱��� ��ü ���� �õ�. createInstance() �Լ��� ���� ȣ���Ͻÿ�");
			s_Instance = new T();
		}

		return *s_Instance;
	}

	template<typename T>
	void Singleton<T>::destroyInstance()
	{
		if (s_Instance == nullptr)
		{
			LOG(LogLevel::Warning, "���ʱ�ȭ ������ �̱��� ��ü �Ҵ� ���� �õ�. createInstance() �Լ��� ���� ȣ���Ͻÿ�");
		}
		else
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}