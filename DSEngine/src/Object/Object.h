#pragma once
#include <string>
#include <vector>
#include "../Component/Component.h"

namespace DS
{
	class Scene;

	class Object
	{
	public:
		Object();
		virtual ~Object();

		bool isActive();

		bool isInvisible();

		Scene& getScene();
	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addComponent(Component* component);
		void removeComponent(Component* component);
		template <typename T>
		T& getComponent() const;
		template <typename T>
		bool isComponentExist();

		void addChild(Object* object);
		void removeChild(Object* object);
		const std::vector<Object*>& getChildren() const;
		void isChildExist(Object* object);

		void setActive(bool active);

		void setInvisible(bool invisible);

	private:
		void update(float deltaTime);
		void draw();

		friend void Component::update(float deltaTime);
		friend void Component::draw();
	};
}