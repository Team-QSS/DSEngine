#include "TScene.h"
#include "../Defines.h"

namespace DS
{
	void TScene::onUpdate(float delta)
	{
		LOG(LogLevel::Info, "TScene update 호출");
	}

	void TScene::onDraw() 
	{
		LOG(LogLevel::Info, "TScene draw 호출");
	}
}