#pragma once

#include "src\Utils\Logger.h"

// #include <png.h>

namespace DS
{
	class Texture final
	{
	public:
		Texture(const tstring& path);
		~Texture();

		const tstring& getPath() const;
		int32 getHeight() const;
		int32 getWidth() const;

	private:
		uint8 ReadPNG();
		void Load();

		int32 m_Width;
		int32 m_Height;

		Texture(const Texture& yRef);
		Texture(Texture&& yRef);
		Texture& operator= (const Texture& yRef);
		Texture& operator= (Texture&& yRef);
	};
}