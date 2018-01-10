#pragma once
#include "Scene.h"
#include "../Object/TObject.h"

namespace DS
{
	class TScene : public Scene
	{
	public:
		TScene()
		{
			addObject(*(new TObject()));
		}
	protected:
		virtual void onUpdate(float deltaTime) override;
		virtual void onDraw() override;
	};
}
