#include "SquareComponent.h"
#include "../Graphics/GraphicsManager.h"

namespace DS
{
	SquareComponent::SquareComponent():
		m_VertexBuffer(nullptr),
		m_IndexBuffer(nullptr),
		m_ConstantBuffer(nullptr)
	{
		ID3D11Device* device = GraphicsManager::getInstance().getDevice();
		HRESULT result;

		DirectX::XMFLOAT4 vertices[4] = { {-1, 1, 0, 1}, {1, 1, 0, 1}, {1, -1, 0, 1}, {-1, -1, 0, 1} };

		D3D11_BUFFER_DESC vbd;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.ByteWidth = sizeof(DirectX::XMFLOAT4) * 4;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		vbd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA vrd;
		vrd.pSysMem = vertices;
		vrd.SysMemPitch = 0;
		vrd.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&vbd, &vrd, &m_VertexBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create VertexBuffer Error");
		}

		UINT indices[6] = { 0,1,2,0,2,3 };

		D3D11_BUFFER_DESC ibd;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.ByteWidth = sizeof(UINT) * 6;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ird;
		ird.pSysMem = indices;
		ird.SysMemPitch = 0;
		ird.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&ibd, &ird, &m_IndexBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create IndexBuffer Error");
		}
	}

	SquareComponent::~SquareComponent()
	{
		if (m_VertexBuffer)
		{
			m_VertexBuffer->Release();
			m_VertexBuffer = nullptr;
		}

		if (m_IndexBuffer)
		{
			m_IndexBuffer->Release();
			m_IndexBuffer = nullptr;
		}

		if (m_ConstantBuffer)
		{
			m_ConstantBuffer->Release();
			m_ConstantBuffer = nullptr;
		}
	}

	void SquareComponent::onDraw()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		UINT stride = sizeof(DirectX::XMFLOAT4);
		deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, )
	}
}