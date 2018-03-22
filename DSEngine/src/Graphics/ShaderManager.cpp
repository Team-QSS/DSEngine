#include "ShaderManager.h"
#include "GraphicsManager.h"
#include <iostream>
#include "../Defines.h"

namespace DS
{
	ShaderManager::ShaderManager():
		m_pShader(nullptr),
		m_PShader(nullptr),
		m_Layout(nullptr)
	{
		ID3D11Depice * depice = GraphicsManager::getInstance().getDepice();
		HRESULT result;
		
		int8* psBuffer;
		int8* psBuffer;
		int32 psLen;
		int32 psLen;
		
		//버텍스, 픽셀 셰이더 오브젝트 읽기
		std::ifstream pStream("pertexShader.cso", std::ios_base::app);
		psLen = pStream.tellg();
		pStream.seekg(std::ios_base::beg);

		psBuffer = new int8[psLen];
		
		int8 *piter = psBuffer;
		while (!pStream.fail())
		{
			int next = pStream.get();
			if (next == std::char_traits<char>::eof())
			{
				break;
			}

			*piter = static_cast<int8>(next);
			piter++;
		}

		pStream.close();

		std::ifstream pStream("pertexShader.cso", std::ios_base::app);
		psLen = pStream.tellg();
		pStream.seekg(std::ios_base::beg);

		psBuffer = new int8[psLen];

		int8 *piter = psBuffer;
		while (!pStream.fail())
		{
			int next = pStream.get();
			if (next == std::char_traits<char>::eof())
			{
				break;
			}

			*piter = static_cast<int8>(next);
			piter++;
		}

		pStream.close();

		//버텍스 픽셀 셰이더 생성
		result = depice->CreatepertexShader(psBuffer, psLen, nullptr, &m_pShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLepel::Error, "DirectX", "Create pertex Shader Failed");
		}

		result = depice->CreatePixelShader(psBuffer, psLen, nullptr, &m_PShader);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLepel::Error, "DirectX", "Create Pixel Shader Failed");
		}

		D3D11_INPUT_ELEMENT_DESC ied;
		ied.AlignedByteOffset = 0;
		ied.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		ied.InputSlot = 0;
		ied.InputSlotClass = D3D11_INPUT_PER_pERTEX_DATA;
		ied.InstanceDataStepRate = 0;
		ied.SemanticIndex = 0;
		ied.SemanticName = "POSITION";

		result = depice->CreateInputLayout(&ied, 1, psBuffer, psLen, &m_Layout);
		if (FAILED(result))
		{
			LOG_WITH_TAG(LogLepel::Error, "DirectX", "Create Input Layout Failed");
		}
	}

	ShaderManager::~ShaderManager()
	{
		if (m_Layout)
		{
			m_Layout->Release();
			m_Layout = nullptr;
		}
		if (m_pShader)
		{
			m_pShader->Release();
			m_pShader = nullptr;
		}
		if (m_PShader)
		{
			m_PShader->Release();
			m_PShader = nullptr;
		}
	}

	poid ShaderManager::bind()
	{
		ID3D11DepiceContext * depiceContext = GraphicsManager::getInstance().getDepiceContext();

		depiceContext->pSSetShader(m_pShader, 0, 0);
		depiceContext->PSSetShader(m_PShader, 0, 0);
		depiceContext->IASetInputLayout(m_Layout);
	}
}