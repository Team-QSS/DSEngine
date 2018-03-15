#include "Utils.h"

namespace DS
{
	void terminate(int32 exitCode)
	{
		Logger::destroyInstance();
		exit(exitCode);
	}
}