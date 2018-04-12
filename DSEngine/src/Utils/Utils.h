#pragma once

#include "Singleton.h"
#include "Logger.h"
#include "Time\TimeManager.h"
#include "Time\Context.h"
#include "Time\Timer.h"

namespace DS
{
	int terminate(int exitCode);

	tstring& trim(tstring& str);
}