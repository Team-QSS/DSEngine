#pragma once
#include "../Utils/Utils.h"
#include <map>
#include <functional>
#include "Resource.h"
#include "ResourceFactory.h"
#include "ResourcePath.h"

namespace DS
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		friend Singleton<ResourceManager>;

		/* 리소스의 타입 추가
		 * extension : 확장자, factory : 해당 리소스를 생성하는 팩토리
		 * ResourceFactory<ResourceType>::getInstance()로 넣으면 됨
		 */
		template <typename T>
		void addResourceType(tstring extension, Factory& factory);

		bool loadResource(tstring name);
		bool loadGroup(tstring name);

		void unloadResource(tstring name);
		void unloadGroup(tstring name);

		void moveGroup(tstring unloadingGroup, tstring loadingGroup);

		Resource& getResource(tstring name);

	private:
		ResourceManager();
		~ResourceManager();

		void parseJson(ResourcePath& paths, tstring dataString);
	
		std::map<tstring, Resource *> m_Resources;
		std::map<tstring, Factory *> m_Factories;
		ResourcePath m_Paths;
	};
}

#include "ResourceFactory.inl"