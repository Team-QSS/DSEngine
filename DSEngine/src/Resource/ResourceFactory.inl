#pragma once
#include "ResourceFactory.h"

namespace DS
{
	template<typename T>
	void * ResourceFactory<T>::alloc(int8 * buffer, tsize len)
	{
		return new T(buffer, len);
	}

	template<typename T>
	void ResourceFactory<T>::free(void * resource, tsize n)
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