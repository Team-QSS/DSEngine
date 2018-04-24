#pragma once
#include "ResourceFactory.h"

namespace DS
{
	template<typename T>
	void * ResourceFactory<T>::alloc(int8 * buffer)
	{
		return new T(buffer);
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