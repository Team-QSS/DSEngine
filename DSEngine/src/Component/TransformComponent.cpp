#include "TransformComponent.h"

namespace DS
{
	TransformComponent::TransformComponent() :
		m_Position({ 0, 0 }),
		m_Size({ 1, 1 }),
		m_Angle(0),
		m_Depth(0)
	{

	}

	void TransformComponent::move(const DirectX::XMFLOAT2& offset)
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
	}

	void TransformComponent::move(const DirectX::XMFLOAT2&& offset)
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
	}

	void TransformComponent::stretch(const DirectX::XMFLOAT2& offset)
	{
		m_Size.x *= offset.x;
		m_Size.y *= offset.y;
	}

	void TransformComponent::stretch(const DirectX::XMFLOAT2&& offset)
	{
		m_Size.x *= offset.x;
		m_Size.y *= offset.y;
	}
}