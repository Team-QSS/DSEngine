#include "TObject.h"
#include "../Defines.h"

void TObject::onUpdate(float delta)
{
	LOG(DS::LogLevel::Info, "TObject update 호출");
}

void TObject::onDraw()
{
	LOG(DS::LogLevel::Info, "TObject draw 호출");
}