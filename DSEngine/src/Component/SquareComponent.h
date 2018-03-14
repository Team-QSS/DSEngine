#pragma once
#include "Component.h"
#include <d3d11.h>
#include <DirectXMath.h>

namespace DS
{
	class SquareComponent : public Component
	{
	public:
		SquareComponent();
		virtual ~SquareComponent();

	protected:
		virtual void onDraw() override;

	private:
		ID3D11Buffer * m_VertexBuffer;
		ID3D11Buffer * m_IndexBuffer;
		ID3D11Buffer * m_ConstantBuffer;
	};
}