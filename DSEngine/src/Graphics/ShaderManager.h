#pragma once
#include "../Utils/Utils.h"
#include <map>
#include <d3d11.h>
#include <filesystem>

namespace DS
{
	class ShaderManager final : public Singleton<ShaderManager>
	{
	public:
		void bindVertexShader(std::string name);
		void bindPixelShader(std::string name);

	private:
		ShaderManager();
		~ShaderManager();

		std::map<std::string, ID3D11VertexShader *>m_VertexShaders;
		std::map<std::string, ID3D11PixelShader *>m_PixelShaders;
	};
}