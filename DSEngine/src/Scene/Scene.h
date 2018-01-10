#pragma once
#include <unordered_set>
#include <iterator>

namespace DS
{
	class Object;

	class Scene
	{
	public:
		Scene() = delete;
		virtual ~Scene();

	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addObject(Object& object);
		void removeObject(Object& object);
		bool isObjectExist(Object& object);
		int objectQuantity();	//오브젝트 수량

	private:
		void update(float deltaTime);
		void draw();

		std::unordered_set<Object&> m_Objects; //현재 오브젝트들을 담는 컨테이너
	
		friend class Object;
	};
}
