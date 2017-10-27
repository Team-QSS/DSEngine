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
			//중복 초기화로 인한 경고 출력
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
			//널포인터 참조 시도로 인한 에러 출력
		}

		return *s_Instance;
	}

	template<typename T>
	void Singleton<T>::destroyInstance()
	{
		if (s_Instance == nullptr)
		{
			//미초기화 상태의 접근으로 인한 에러 출력
		}
		else
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}
}