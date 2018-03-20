#pragma once
#include "../Object/Object.h"

namespace DS
{
	struct Context;

	class Component
	{
	public:
		Component();
		virtual ~Component();

	protected:
		virtual void onUpdate(Context& context) {};
		virtual void onDraw() {};

	private:
		void update(Context& context);
		void draw();

		friend void Object::update(Context& context);
		friend void Object::draw();
	};
}