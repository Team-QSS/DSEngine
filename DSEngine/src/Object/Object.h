#pragma once
#include <string>
#include <vector>
#include <set>

namespace DS
{
	class Scene;
	class Component;

	class Object
	{
	public:
		Object();
		virtual ~Object();

		bool isActive() const;
		bool isVisible() const;

		Scene& getScene() const;

	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addComponent(Component& component);
		void removeComponent(Component& component);
		template<typename T>
		void removeComponent();
		template <typename T>
		T& getComponent() const;
		template <typename T>
		bool isComponentExist();

		void addChild(Object& object);
		void removeChild(Object& object);
		const std::set<Object*>& getChildren() const;
		bool isChildExist(Object& object);

		void setActive(bool active);

		void setVisible(bool visible);

	private:
		enum class GarbageType
		{
			ComponentType,
			ObjectType
		};

		struct Garbage
		{
			Garbage(GarbageType type, void* element);
			GarbageType type;
			void* element;
		};

		void update(float deltaTime);
		void draw();

		void setScene(Scene* scene);
		void setParent(Object* object);

		void collectGarbage();

		bool m_IsActive;
		bool m_IsVisible;

		Scene* m_Scene;
		Object* m_Parent;

		std::set<Component*> m_Components;
		std::set<Object*> m_Children;
		std::vector<Garbage> m_GarbageCollector;

	};
}

#include "Object.inl"