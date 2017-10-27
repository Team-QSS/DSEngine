#include "Singleton.h"

namespace DS
{
	template<typename T>
	T* DS::Singleton<T>::s_Instance = nullptr;

	template<typename T>
	void Singleton<T>::createInstance()
	{
		if (s_Instance)
		{
			//�ߺ� �ʱ�ȭ�� ���� ��� ���
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
			//�������� ���� �õ��� ���� ���� ���
		}

		return *s_Instance;
	}

	template<typename T>
	void Singleton<T>::destroyInstance()
	{
		if (s_Instance == nullptr)
		{
			//���ʱ�ȭ ������ �������� ���� ���� ���
		}
		else
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}