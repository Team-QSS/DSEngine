#include "ShaderManager.h"
#include "GraphicsManager.h"

namespace DS
{
	ShaderManager::ShaderManager()
	{
		
	}

	ShaderManager::~ShaderManager()
	{

	}

	void ShaderManager::bindVertexShader(tstring name)
	{
		if (m_VertexShaders.count(name) > 0) GraphicsManager::getInstance().getDeviceContext()->VSSetShader(m_VertexShaders[name], nullptr, 1);
	}

	void ShaderManager::bindPixelShader(tstring name)
	{
		if (m_PixelShaders.count(name) > 0) GraphicsManager::getInstance().getDeviceContext()->PSSetShader(m_PixelShaders[name], nullptr, 1);
	}
}