#include "Resource.h"
#include <iostream>
#include "../Utils/Utils.h"

namespace DS
{
	Resource::Resource(int8* buffer, tsize len)
	{
		
	}

	Resource::~Resource()
	{
		
	}

	const tstring& Resource::getExtension()
	{
		return m_Extension;
	}
}