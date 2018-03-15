#pragma once
#include "../Object/Object.h"

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

		friend void Object::update(float deltaTime);
		friend void Object::draw();
	};
}