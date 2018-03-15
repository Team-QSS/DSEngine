#pragma once
#include <set>
#include <vector>

namespace DS
{
	class Object;
	class DSEngine;
	struct Context;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

	protected:
		virtual void onUpdate(Context& context) = 0;
		virtual void onDraw() {};

		void addObject(Object& object);
		void removeObject(Object& object);
		bool isObjectExist(Object& object);

		int objectQuantity();	//������Ʈ ����

		void collectGarbage();

	private:
		void update(Context& context);
		void draw();

		std::set<Object*> m_Objects; //���� ������Ʈ���� ��� �����̳�
		std::vector<Object*> m_GarbageCollector;

		friend DSEngine;	
		friend Object;
	};
}
