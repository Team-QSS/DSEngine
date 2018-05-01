#pragma once
#include "../Defines.h"

namespace DS
{
	class ResourceManager;
	class Resource
	{
	public:
		friend ResourceManager;
		Resource(int8* buffer, tsize len);
		virtual ~Resource();

		const tstring& getExtension();

	private:
		tstring m_Extension;
	};

}