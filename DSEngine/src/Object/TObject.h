#pragma once
#include "Object.h"

class TObject : public DS::Object
{
public:
	virtual void onUpdate(float deltaTime) override;
	virtual void onDraw() override;
};