#pragma once
#include "../Utils/Utils.h"
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")

namespace DS
{
	class GraphicsManager final : public Singleton<GraphicsManager>
	{
	public:
		friend Singleton <GraphicsManager>;

		void initialize(HWND windowHandle, DirectX::XMINT2 resolution, bool isFullScreen);

		ID3D11Device * getDevice();
		ID3D11DeviceContext * getDeviceContext();

		void beginDraw();
		void endDraw();
	private:
		GraphicsManager();
		~GraphicsManager();

		IDXGISwapChain * m_SwapChain;
		ID3D11Device * m_Device;
		ID3D11DeviceContext * m_DeviceContext;
		D3D_FEATURE_LEVEL m_FeatureLevel;
		ID3D11RenderTargetView * m_RenderTargetView;
		ID3D11Texture2D * m_DepthStencilBuffer;
		ID3D11DepthStencilView * m_DepthStencilView;
	};
}