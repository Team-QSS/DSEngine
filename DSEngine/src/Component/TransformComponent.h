#pragma once
#include "Component.h"
#include <DirectXMath.h>

namespace DS
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		~TransformComponent() = default;

		void move(const DirectX::XMFLOAT2& offset);
		void move(const DirectX::XMFLOAT2&& offset);

		void stretch(const DirectX::XMFLOAT2& offset);
		void stretch(const DirectX::XMFLOAT2&& offset);

		DirectX::XMFLOAT2 m_Position;
		DirectX::XMFLOAT2 m_Size;

		int m_Depth;
		float m_Angle;
	};
}