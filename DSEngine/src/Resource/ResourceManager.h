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

		/* ���ҽ��� Ÿ�� �߰�
		 * extension : Ȯ����, factory : �ش� ���ҽ��� �����ϴ� ���丮
		 * ResourceFactory<ResourceType>::getInstance()�� ������ ��
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