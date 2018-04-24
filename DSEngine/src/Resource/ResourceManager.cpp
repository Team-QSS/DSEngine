#include "ResourceManager.h"
#include "../Defines.h"
#include <iostream>
#include <algorithm>
#include <cctype>

namespace DS
{
	ResourceManager::ResourceManager()
	{
		std::ifstream resInfo("./Resources.dsr");
		
		resInfo.seekg(0, std::ios_base::end);
		int len = static_cast<int32>(resInfo.tellg());
		resInfo.seekg(0, std::ios_base::beg);

		char * buffer = new char[len];

		resInfo.read(buffer, len);

		tstring str(buffer);

		parseRes(str);

		delete[] buffer;

		for (auto const & it : m_Paths)
		{
			LOG(LogLevel::Debug, it.first + ": " + it.second);
		}
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

			size commentPos = line.find("//");
			if (commentPos != tstring::npos)
			{
				line.replace(commentPos, tstring::npos, ""); //주석 삭제
			}

			commentPos = line.find("/*");/* 여러 줄 주석 삭제 */
			if (commentPos != tstring::npos)
			{
				size commentEndPos = line.find("*/", commentPos);
				if (commentEndPos != tstring::npos)
				{
					line.replace(commentPos, commentEndPos - commentPos + 2, "");
				}
				else
				{
					do
					{
						stream.getline(buffer, dataString.length());
						line = buffer;
						commentEndPos = line.find("*/");
					} while (commentEndPos == tstring::npos);
					line.replace(0, commentEndPos + 2, "");
				}
			}

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

		if (path.at(0) == '\"') 
		{
			path.replace(0, 1, "");
		}

		if (path.at(path.length() - 1) == '\"')
		{
			path.replace(path.length() - 1, tstring::npos, "");
		}

		if (tstring::npos == name.find('|'))
		{
			while (tstring::npos != path.find_first_of('<'))
			{
				size start = path.find_first_of('<');
				size end = path.find_first_of('>');
				if (end == tstring::npos)
				{
					LOG(LogLevel::Error, "리소스 파일 분석 오류");
					break;
				}

				path.replace(start, end - start + 1, val[path.substr(start + 1, end - start - 1)]);
			}

			m_Paths[name] = path;
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
			size pathStart = path.find_last_of('<', pathMid);
			size pathEnd = path.find('>', pathMid);

			if (endNum <= startNum)
			{
				LOG(LogLevel::Error, "리소스 파일 오류");
				return;
			}

			for (int i = startNum; i < endNum; i++)
			{
				tstring tname = name;
				tstring tpath = path;
				insertPath(tname.replace(nameStart, nameEnd - nameStart + 1, std::to_string(i)),
					tpath.replace(pathStart, pathEnd - pathStart + 1, std::to_string(i)),
					val);
			}
		}
	}
}