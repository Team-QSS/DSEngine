#include "ShaderManager.h"
#include "GraphicsManager.h"
#include <iostream>
#include "../Defines.h"

namespace DS
{
	ShaderManager::ShaderManager():
		m_VShader(nullptr),
		m_PShader(nullptr),
		m_Layout(nullptr)
	{
		ID3D11Device * device = GraphicsManager::getInstance().getDevice();
		HRESULT result;
		
		int8* vsBuffer;
		int8* psBuffer;
		int32 vsLen;
		int32 psLen;
		
		//버텍스, 픽셀 셰이더 오브젝트 읽기

		//버텍스 픽셀 셰이더 생성
		result = device->CreateVertexShader(vsBuffer, vsLen, nullptr, &m_VShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create Vertex Shader Failed");
		}

		result = device->CreatePixelShader(vsBuffer, vsLen, nullptr, &m_PShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create Pixel Shader Failed");
		}

		D3D11_INPUT_ELEMENT_DESC ied;
		ied.AlignedByteOffset = 0;
		ied.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		ied.InputSlot = 0;
		ied.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		ied.InstanceDataStepRate = 0;
		ied.SemanticIndex = 0;
		ied.SemanticName = "POSITION";

		result = device->CreateInputLayout(&ied, 1, vsBuffer, vsLen, &m_Layout);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create Input Layout Failed");
		}
	}

	ShaderManager::~ShaderManager()
	{
		if (m_Layout)
		{
			m_Layout->Release();
			m_Layout = nullptr;
		}
		if (m_VShader)
		{
			m_VShader->Release();
			m_VShader = nullptr;
		}
		if (m_PShader)
		{
			m_PShader->Release();
			m_PShader = nullptr;
		}
	}

	void ShaderManager::bind()
	{
		ID3D11DeviceContext * deviceContext = GraphicsManager::getInstance().getDeviceContext();

		deviceContext->VSSetShader(m_VShader, 0, 0);
		deviceContext->PSSetShader(m_PShader, 0, 0);
		deviceContext->IASetInputLayout(m_Layout);
	}
}