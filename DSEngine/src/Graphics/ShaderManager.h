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
		friend Singleton<ShaderManager>;

		void bind();

	private:
		ShaderManager();
		~ShaderManager();

		ID3D11VertexShader* m_VShader;
		ID3D11PixelShader* m_PShader;
		ID3D11InputLayout* m_Layout;
	};
}