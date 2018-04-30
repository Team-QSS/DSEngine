#pragma once
#include "Resource.h"
#include "../Utils/Singleton.h"

namespace DS
{
	class Factory
	{
	public:
		virtual void * alloc(int8 * buffer, tsize len) = 0;
		virtual void free(void * resource, size_t n = 1) = 0;
	};

	template<typename T>
	class ResourceFactory final: public Singleton<ResourceFactory<T>>, public Factory
	{
	public:
		friend Singleton<ResourceFactory<T>>;
		virtual void * alloc(int8 * buffer, tsize len) override;
		//virtual void ** alloc(int8 ** buffer, tsize n) override;
		virtual void free(void * resource, tsize n) override;

	private:
		ResourceFactory() = default;
		~ResourceFactory() = default;

	};
}

#include "ResourceFactory.inl"