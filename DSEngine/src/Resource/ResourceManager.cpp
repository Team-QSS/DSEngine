#include "ResourceManager.h"
#include <iostream>
#include <algorithm>
#include <cctype>

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

		parseRes(m_Paths, str);

		delete[] buffer;
	}

	ResourceManager::~ResourceManager()
	{

	}

	void ResourceManager::parseRes(ResourcePath& paths, tstring dataString)
	{
		tstringstream stream(dataString);

		char* buffer = new char[dataString.length() + 1];

		while (!stream.eof())
		{
			stream.getline(buffer, dataString.length());
			tstring line(buffer);

			size colPos = line.find(':');
			if (colPos != tstring::npos)
			{
				tstring name = line.substr(0, colPos);
				trim(name);

				
			}
		}
	}
}