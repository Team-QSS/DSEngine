#pragma once
#include "Scene.h"

namespace DS
{
	class TScene : public Scene
	{
	protected:
		virtual void onUpdate(float deltaTime) override;
		virtual void onDraw() override;
	};
}
