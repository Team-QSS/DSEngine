#pragma once
#include "../Utils/Utils.h"
#include <map>
#include <functional>
#include "Resource.h"
#include "ResourceFactory.h"
//#include "ResourcePath.h"

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
		bool loadSet(tstring name);

		void unloadResource(tstring name);
		void unloadSet(tstring name);

		void moveSet(tstring unloadingSet, tstring loadingSet);

		Resource& getResource(tstring name);

	private:
		ResourceManager();
		~ResourceManager();

		void parseRes(tstring dataString);
		void insertPath(tstring& rawName, tstring& rawPath, std::map<tstring, tstring> & val);
	
		std::map<tstring, Resource *> m_Resources;
		std::map<tstring, Factory *> m_Factories;
		std::map<tstring, tstring> m_Paths;
	};
}

#include "ResourceFactory.inl"