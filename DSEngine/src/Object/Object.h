#pragma once
#include <string>
#include <vector>
#include "../Component/Component.h"
#include "../Scene/Scene.h"

namespace DS
{
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

		void setScene(Scene* scene);

		friend void Component::update(float deltaTime);
		friend void Component::draw();

		friend void Scene::update(float deltaTime);
		friend void Scene::draw();
		
	};
}