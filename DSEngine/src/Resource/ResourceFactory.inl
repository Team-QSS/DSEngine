#include "ResourceFactory.h"

namespace DS
{
	template<typename T>
	void * ResourceFactory::alloc(size_t n = 1)
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
	void ResourceFactory::free(void * resource, size_t n = 1)
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