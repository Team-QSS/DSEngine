#include "ShaderManager.h"
#include "GraphicsManager.h"
#include <iostream>
#include "../Defines.h"
#include <exception>

namespace DS
{
	ShaderManager::ShaderManager():
		m_VShader(nullptr),
		m_PShader(nullptr),
		m_Layout(nullptr)
	{
		ID3D11Device * device = GraphicsManager::getInstance().getDevice();
		HRESULT result;
		
		int8* vsBuffer = nullptr;
		int8* psBuffer = nullptr;
		int32 vsLen = 0;
		int32 psLen = 0;
		
		try
		{
			//버텍스, 픽셀 셰이더 오브젝트 읽기
			std::ifstream vStream("VertexShader.cso", std::ios_base::binary);
			vStream.seekg(0, std::ios_base::end);
			vsLen = static_cast<int32>(vStream.tellg());
			vStream.seekg(0, std::ios_base::beg);

			vsBuffer = new int8[vsLen];

			vStream.read(reinterpret_cast<char *>(vsBuffer), vsLen);
			vStream.close();

			std::ifstream pStream("PixelShader.cso", std::ios_base::binary);
			pStream.seekg(0, std::ios_base::end);
			psLen = static_cast<int32>(pStream.tellg());
			pStream.seekg(0, std::ios_base::beg);

			psBuffer = new int8[psLen];

			
			pStream.read(reinterpret_cast<char *>(psBuffer), psLen);
			pStream.close();
		}
		catch (const std::ios_base::failure& e)
		{
			LOG(LogLevel::Error, e.what());
		}
		

		

		//버텍스 픽셀 셰이더 생성
		result = device->CreateVertexShader(vsBuffer, vsLen, nullptr, &m_VShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLevel::Error, "DirectX", "Create vertex Shader Failed");
		}

		result = device->CreatePixelShader(psBuffer, psLen, nullptr, &m_PShader);
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

		delete[] vsBuffer;
		delete[] psBuffer;

		this->bind();
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