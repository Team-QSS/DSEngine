#pragma once
#include <set>
#include <vector>

namespace DS
{
	class Object;
	class DSEngine;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

	protected:
		virtual void onUpdate(float deltaTime) = 0;
		virtual void onDraw() {};

		void addObject(Object& object);
		void removeObject(Object& object);
		bool isObjectExist(Object& object);

		int objectQuantity();	//������Ʈ ����

		void collectGarbage();

	private:
		void update(float deltaTime);
		void draw();
		std::set<Object*> m_Objects; //���� ������Ʈ���� ��� �����̳�
		std::vector<Object*> m_GarbageCollector;

		friend DSEngine;	
		friend Object;
	};
}
