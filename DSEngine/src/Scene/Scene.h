#pragma once
#include "../Object/Object.h"

namespace DS
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addObject(Object* object);
		void removeObject(Object* object);
		void isObjectExist(Object* object);

	private:
		void update();
		void draw();

		friend void Object::update(float deltaTime);
		friend void Object::draw();
		friend void Object::setScene(Scene* scene);
	};
}
