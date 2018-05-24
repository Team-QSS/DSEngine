#include "GraphicsManager.h"
#include "ShaderManager.h"
#include <d3d11.h>

namespace DS
{
	GraphicsManager::GraphicsManager() :
		m_SwapChain(nullptr),
		m_Device(nullptr),
		m_DeviceContext(nullptr),
		m_RenderTargetView(nullptr),
		m_DepthStencilView(nullptr),
		m_DepthStencilBuffer(nullptr),
		m_FeatureLevel(D3D_FEATURE_LEVEL_11_0),
		m_MatrixBuffer(nullptr)
	{
		
	}

	GraphicsManager::~GraphicsManager()
	{
		ShaderManager::destroyInstance();
		if (m_SwapChain)
		{
			m_SwapChain->Release();
			m_SwapChain = nullptr;
		}

		if (m_Device)
		{
			m_Device->Release();
			m_Device = nullptr;
		}

		if (m_DeviceContext)
		{
			m_DeviceContext->Release();
			m_DeviceContext = nullptr;
		}

		if (m_RenderTargetView)
		{
			m_RenderTargetView->Release();
			m_RenderTargetView = nullptr;
		}

		if (m_DepthStencilBuffer)
		{
			m_DepthStencilBuffer->Release();
			m_DepthStencilBuffer = nullptr;
		}

		if (m_DepthStencilView)
		{
			m_DepthStencilView->Release();
			m_DepthStencilView = nullptr;
		}
	}

	void GraphicsManager::initialize(HWND windowHandle, DirectX::XMINT2 resolution, bool isFullScreen)
	{
		HRESULT result;

		UINT flag = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined(DEBUG) || defined(_DEBUG)
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferCount = 2;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.Height = resolution.y;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Width = resolution.x;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.Flags = 0;
		sd.OutputWindow = windowHandle;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Windowed = !isFullScreen;

		result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag, nullptr, 0, D3D11_SDK_VERSION, 
			&sd, &m_SwapChain, &m_Device, &m_FeatureLevel, &m_DeviceContext);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Creating Device and SwapChain Failed");
		}

		ID3D11Texture2D* backBuffer = nullptr;
		result = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&backBuffer));
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Getting BackBuffer Failed");
		}

		result = m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Creating RenderTargetView Failed");
		}	

		D3D11_TEXTURE2D_DESC dsd;
		dsd.ArraySize = 1;
		dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dsd.CPUAccessFlags = 0;
		dsd.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
		dsd.Height = resolution.y;
		dsd.MipLevels = 1;
		dsd.MiscFlags = 0;
		dsd.SampleDesc.Count = 1;
		dsd.SampleDesc.Quality = 0;
		dsd.Usage = D3D11_USAGE_DEFAULT;
		dsd.Width = resolution.x;

		result = m_Device->CreateTexture2D(&dsd, nullptr, &m_DepthStencilBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Creating DepthStencilBuffer Failed");
		}

		result = m_Device->CreateDepthStencilView(m_DepthStencilBuffer, nullptr, &m_DepthStencilView);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create DepthStencilView Failed");
		}

		D3D11_VIEWPORT vp;
		vp.Height = (float32) resolution.y;
		vp.MaxDepth = 1;
		vp.MinDepth = 0;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = (float32) resolution.x;

		m_DeviceContext->RSSetViewports(1, &vp);
		m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);


		DirectX::XMMATRIX ortho = DirectX::XMMatrixOrthographicLH(800.0f, 600.f, 0.0f, 100.0f);


		D3D11_BUFFER_DESC matrixBufferDesc;
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(DirectX::XMFLOAT4X4);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		XMStoreFloat4x4(&m_OrthoMatrix, ortho);
		
		D3D11_SUBRESOURCE_DATA matrixResourceData;
		matrixResourceData.pSysMem = &m_OrthoMatrix;
		matrixResourceData.SysMemPitch = 0;
		matrixResourceData.SysMemSlicePitch = 0;

		result = m_Device->CreateBuffer(&matrixBufferDesc, &matrixResourceData, &m_MatrixBuffer);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create ConstantBuffer Error");
		}
		
		

		
	}

	ID3D11Device * GraphicsManager::getDevice()
	{
		return m_Device;
	}

	ID3D11DeviceContext * GraphicsManager::getDeviceContext()
	{
		return m_DeviceContext;
	}

	void GraphicsManager::beginDraw()
	{
		DirectX::XMMATRIX ortho = DirectX::XMLoadFloat4x4(&m_OrthoMatrix);
		 
		D3D11_MAPPED_SUBRESOURCE mappedResource;

		HRESULT result;
		result = m_DeviceContext->Map(m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Draw Failed");
		}

		DirectX::XMStoreFloat4x4(static_cast<DirectX::XMFLOAT4X4 *>(mappedResource.pData), DirectX::XMMatrixTranspose(ortho));

		m_DeviceContext->Unmap(m_MatrixBuffer, 0);

		m_DeviceContext->VSSetConstantBuffers(1, 1, &m_MatrixBuffer);
		

		float bg[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, bg);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		ShaderManager::getInstance().bind();
	}

	void GraphicsManager::endDraw()
	{
		m_SwapChain->Present(1, 0);
	}
}