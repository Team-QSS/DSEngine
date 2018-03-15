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
		void bindVertexShader(tstring name);
		void bindPixelShader(tstring name);

	private:
		ShaderManager();
		~ShaderManager();
		friend Singleton<ShaderManager>;

		std::map<tstring, ID3D11VertexShader *>m_VertexShaders;
		std::map<tstring, ID3D11PixelShader *>m_PixelShaders;
	};
}