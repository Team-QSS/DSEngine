#pragma once
#include "ResourceFactory.h"

namespace DS
{
	template<typename T>
	void * ResourceFactory<T>::alloc(size_t n)
	{
		if (n == 1)
		{
			return new T();
		}
		else
		{
			return new T[n];
		}
	}

	template<typename T>
	void ResourceFactory<T>::free(void * resource, size_t n)
	{
		if (n == 1)
		{
			delete resource;
		}
		else
		{
			delete[] resource;
		}
	}
}