#include "Utils.h"

namespace DS
{
	int terminate(int exitCode)
	{
		Logger::destroyInstance();
		exit(exitCode);
	}
}