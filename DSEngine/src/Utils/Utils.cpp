#include "Utils.h"
#include <algorithm>
#include <cctype>

namespace DS
{
	int terminate(int exitCode)
	{
		Logger::destroyInstance();
		exit(exitCode);
	}

	tstring& trim(tstring& str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
			return !std::isspace(ch);
		}));
		str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), str.end());
		return str;
	}
}