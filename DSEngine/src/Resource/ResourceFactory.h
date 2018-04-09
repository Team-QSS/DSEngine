#pragma once
#include "Resource.h"
#include "../Utils/Singleton.h"

namespace DS
{
	class Factory
	{
	public:
		virtual void * alloc(size_t n) = 0;
		virtual void free(void * resource, size_t n) = 0;
	};

	template<typename T>
	class ResourceFactory final: public Singleton<ResourceFactory<T>>, Factory
	{
	public:
		friend Singleton<ResourceFactory<T>>;
		virtual void * alloc(size_t n = 1) override;
		virtual void free(void * resource, size_t n = 1) override;

	private:
		ResourceFactory() = default;
		~ResourceFactory() = default;

	};
}

#include "ResourceFactory.inl"