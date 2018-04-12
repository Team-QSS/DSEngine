#pragma once
#include "../Defines.h"
#include <map>
#include <vector>

namespace DS
{
	class ResourceManager;

	class ResourcePath final
	{
	public:
		friend ResourceManager;

	private:
		ResourcePath() = default;
		~ResourcePath() = default;

		tstring m_Extension;

		std::vector<tstring> m_Path;
		std::map<tstring, ResourcePath *> m_Paths;
	};
}