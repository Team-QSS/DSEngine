#include "ResourceManager.h"
#include <iostream>

namespace DS
{
	ResourceManager::ResourceManager()
	{
		std::ifstream resInfo("./Resources.json");
		
		resInfo.seekg(0, std::ios_base::end);
		int len = static_cast<int32>(resInfo.tellg());
		resInfo.seekg(0, std::ios_base::beg);

		char * buffer = new char[len];

		resInfo.read(buffer, len);

		tstring str(buffer);

		parseJson(m_Paths, str);
	}

	ResourceManager::~ResourceManager()
	{

	}

	void ResourceManager::parseJson(ResourcePath& paths, tstring dataString)
	{
		
	}
}