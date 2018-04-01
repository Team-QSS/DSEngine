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

		Object& getParent() const;

	protected:
		virtual void onUpdate(Context& context) {};
		virtual void onDraw() {};

	private:
		void update(Context& context);
		void draw();

		void setParent(Object* obj);

		Object* m_Parent;

		friend Object;
	};
}