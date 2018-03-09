#include "GraphicsManager.h"
#include <d3d11.h>

namespace DS
{
	GraphicsManager::GraphicsManager()
	{

	}

	GraphicsManager::~GraphicsManager()
	{

	}

	void GraphicsManager::initialize(HWND windowHandle, DirectX::XMINT2 resolution, bool isFullScreen)
	{
		HRESULT result;

		UINT flag = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined(DEBUG) || defined(_DEBUG)
		flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif



		result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flag, nullptr, 0, D3D11_SDK_VERSION, 
			&m_Device, &m_FeatureLevel, &m_DeviceContext);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Creating Device and SwapChain Failed");
		}

		DXGI_SWAP_CHAIN_DESC sd;
		sd.BufferCount = 2;
		sd.BufferDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		sd.BufferDesc.Height = resolution.y;
		sd.BufferDesc.RefreshRate.Denominator = 60;
		sd.BufferDesc.RefreshRate.Numerator = 1;
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

		IDXGIDevice* dxgiDevice = nullptr;
		result = m_Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void **>(&dxgiDevice));
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Get DXGIDevice Failed");
		}

		IDXGIAdapter* dxgiAdapter = nullptr;
		result = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void **>(&dxgiAdapter));
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Get DXGIAdapter Failed");
		}

		IDXGIFactory* dxgiFactory = nullptr;
		result = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void **>(&dxgiFactory));
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Get DXGIFactory");
		}

		result = dxgiFactory->CreateSwapChain(m_Device, &sd, &m_SwapChain);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create SwapChain Failed");
		}

		if (dxgiFactory)
		{
			dxgiFactory->Release();
			dxgiFactory = nullptr;
		}
		if (dxgiAdapter)
		{
			dxgiAdapter->Release();
			dxgiAdapter = nullptr;
		}
		if (dxgiDevice)
		{
			dxgiDevice->Release();
			dxgiDevice = nullptr;
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

		if (backBuffer)
		{
			backBuffer->Release();
			backBuffer = nullptr;
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
		vp.Height = 1080;
		vp.MaxDepth = 1;
		vp.MinDepth = 0;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		vp.Width = 1920;

		m_DeviceContext->RSSetViewports(1, &vp);
	}

	void GraphicsManager::draw()
	{
		float bg[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
		m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, bg);
		m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
}