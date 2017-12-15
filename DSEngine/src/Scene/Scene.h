#pragma once
#include <unordered_set>
#include <iterator>
#include "../Object/Object.h"

namespace DS
{
	class Object;

	class Scene
	{
	public:
		Scene() = delete;
		virtual ~Scene() = delete;

	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addObject(Object* object);
		void removeObject(Object* object);
		void isObjectExist(Object* object);

	private:
		void update(float deltaTime);
		void draw();

		std::unordered_set<Object&> m_Objects; //현재 오브젝트들을 담는 컨테이너

		friend void Object::update(float deltaTime);
		friend void Object::draw();
		friend void Object::setScene(Scene* scene);
	};
}
