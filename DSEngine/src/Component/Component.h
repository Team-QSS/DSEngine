#pragma once

namespace DS
{
	class Component
	{
	public:
		Component();
		virtual ~Component();

	protected:
		virtual void onUpdate(float deltaTime) {};
		virtual void onDraw() {};

	private:
		void update(float deltaTime);
		void draw();

	};
}