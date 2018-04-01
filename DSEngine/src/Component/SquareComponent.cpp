#include "SquareComponent.h"
#include "../Graphics/GraphicsManager.h"
#include <utility>
#include "TransformComponent.h"

namespace DS
{
	SquareComponent::SquareComponent(DirectX::XMFLOAT2 & size) :
		SquareComponent(std::move(size))
	{

	}

	SquareComponent::SquareComponent(DirectX::XMFLOAT2 && size):
		m_Size(size),
		m_VertexBuffer(nullptr),
		m_IndexBuffer(nullptr),
		m_ConstantBuffer(nullptr)
	{
		ID3D11Device* device = GraphicsManager::getInstance().getDevice();
		HRESULT result;

		DirectX::XMFLOAT4 vertices[4] = 
		{ 
			{-size.x / 2, size.y / 2, 0.0f, 1.0f }, 
			{ size.x / 2, size.y / 2, 0.0f, 1.0f },
			{ size.x / 2, -size.y / 2, 0.0f, 1.0f },
			{-size.x / 2, -size.y / 2, 0.0f, 1.0f }
		};

		D3D11_BUFFER_DESC vbd;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.ByteWidth = sizeof(DirectX::XMFLOAT4) * 4;
		vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
		vbd.Usage = D3D11_USAGE_DYNAMIC;

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

		DirectX::XMFLOAT4X4 identityMatrix
		{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};

		D3D11_BUFFER_DESC mbd;
		mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		mbd.ByteWidth = sizeof(DirectX::XMFLOAT4X4);
		mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		mbd.MiscFlags = 0;
		mbd.StructureByteStride = 0;
		mbd.Usage = D3D11_USAGE_DYNAMIC;

		D3D11_SUBRESOURCE_DATA mrd;
		mrd.pSysMem = &identityMatrix;
		mrd.SysMemPitch = 0;
		mrd.SysMemSlicePitch = 0;

		result = device->CreateBuffer(&mbd, &mrd, &m_ConstantBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create ConstantBuffer Error");
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

	void SquareComponent::setSize(DirectX::XMFLOAT2 & size)
	{
		m_Size = size;
	}

	void SquareComponent::setSize(DirectX::XMFLOAT2 && size)
	{
		m_Size = size;
	}

	void SquareComponent::resizeVertexBuffer()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		D3D11_MAPPED_SUBRESOURCE vmr;
		deviceContext->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);
		DirectX::XMFLOAT4 vertices[4] =
		{
			{ -m_Size.x / 2, m_Size.y / 2, 0.0f, 1.0f },
			{ m_Size.x / 2, m_Size.y / 2, 0.0f, 1.0f },
			{ m_Size.x / 2, -m_Size.y / 2, 0.0f, 1.0f },
			{ -m_Size.x / 2, -m_Size.y / 2, 0.0f, 1.0f }
		};
		vmr.pData = reinterpret_cast<void *>(vertices);
		
		deviceContext->Unmap(m_VertexBuffer, 0);
	}

	void SquareComponent::onDraw()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		UINT stride = sizeof(DirectX::XMFLOAT4);
		UINT offset = 0;

		DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(
			getParent().getTransformComponent().position.x, 
			getParent().getTransformComponent().position.y, 
			static_cast<float>(getParent().getTransformComponent().depth));

		DirectX::XMMATRIX rotate = DirectX::XMMatrixRotationAxis(
			{ 0.0, 0.0f, 1.0f, 0.0f }, 
			getParent().getTransformComponent().angle);

		DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(
			getParent().getTransformComponent().size.x, 
			getParent().getTransformComponent().size.y,
			1.0f);

		DirectX::XMMATRIX world = scale * rotate * translate;

		D3D11_MAPPED_SUBRESOURCE vmr;
		deviceContext->Map(m_ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);
		XMStoreFloat4x4(static_cast<DirectX::XMFLOAT4X4 *>(vmr.pData), XMMatrixTranspose(world));

		deviceContext->Unmap(m_ConstantBuffer, 0);
		
		deviceContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
		deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
		deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext->DrawIndexed(6, 0, 0);
	}
}