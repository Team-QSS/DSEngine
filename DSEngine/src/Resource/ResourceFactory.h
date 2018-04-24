#pragma once
#include "Resource.h"
#include "../Utils/Singleton.h"

namespace DS
{
	class Factory
	{
	public:
		virtual void * alloc(int8 * buffer) = 0;
		virtual void free(void * resource, size_t n = 1) = 0;
	};

	template<typename T>
	class ResourceFactory final: public Singleton<ResourceFactory<T>>, Factory
	{
	public:
		friend Singleton<ResourceFactory<T>>;
		virtual void * alloc(int8 * buffer) override;
		virtual void ** alloc(int8 ** buffer, size n) override;
		virtual void free(void * resource, size_t n) override;

	private:
		ResourceFactory() = default;
		~ResourceFactory() = default;

	};
}

#include "ResourceFactory.inl"