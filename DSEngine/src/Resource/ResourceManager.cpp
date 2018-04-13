#include "ResourceManager.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace DS
{
	ResourceManager::ResourceManager()
	{
		std::ifstream resInfo("./Resources.res");
		
		resInfo.seekg(0, std::ios_base::end);
		int len = static_cast<int32>(resInfo.tellg());
		resInfo.seekg(0, std::ios_base::beg);

		char * buffer = new char[len];

		resInfo.read(buffer, len);

		tstring str(buffer);

		parseRes(str);

		delete[] buffer;
	}

	ResourceManager::~ResourceManager()
	{

	}

	void ResourceManager::parseRes(tstring dataString)
	{
		tstringstream stream(dataString);
		std::map<tstring, tstring> val;

		char* buffer = new char[dataString.length() + 1];

		while (!stream.eof())
		{
			stream.getline(buffer, dataString.length());
			tstring line(buffer);

			size colPos = line.find(':');
			if (colPos != tstring::npos)
			{
				tstring name = line.substr(0, colPos);
				tstring path = line.substr(colPos + 1, tstring::npos);
				insertPath(name, path, val);
			}
		}
	}

	void ResourceManager::insertPath(tstring& rawName, tstring& rawPath, std::map<tstring, tstring>& val)
	{
		tstring name = trim(rawName);
		tstring path = trim(rawPath);

		if (tstring::npos == name.find('|'))
		{
			while (tstring::npos == path.find_first_of('<'))
			{
				size start = path.find_first_of('<');
				size end = path.find_first_of('>');
				if (end == tstring::npos)
				{
					LOG(LogLevel::Error, "리소스 파일 분석 오류");
					break;
				}

				path.replace(start, end - start + 1, val[path.substr(start + 1, end)]);
			}

			m_Paths.insert(name, path);
		}
		else
		{
			size nameStart = name.find('<');
			size nameEnd = name.find('>');
			size nameMid = name.find('|');

			tstring startNumStr = name.substr(nameStart + 1, nameMid - nameStart - 1);
			int32 startNum = std::stoi(startNumStr);

			tstring endNumStr = name.substr(nameMid + 1, nameEnd - nameMid - 1);
			int32 endNum = std::stoi(endNumStr);

			size pathMid = path.find('|');
			size pathStart;
			for (pathStart = pathMid - 1; pathStart >= 0 && path[pathStart] != '<'; pathStart--);
			size pathEnd;
			for (pathEnd = pathMid + 1; pathEnd < path.length() && path[pathEnd] != '>'; pathEnd++);
		}
	}
}