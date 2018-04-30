#include "../Defines.h"
#include "PNGImage.h"
#include "../Utils/Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "../STB/stb_image.h"


namespace DS
{
	PNGImage::PNGImage(int8 * buffer, tsize len) :
		Resource(buffer, len)
	{
		m_Buffer = reinterpret_cast<int8 *>(stbi_load_from_memory(
					reinterpret_cast<unsigned char*>(buffer),
					static_cast<int>(len),
					&m_Width,
					&m_Height,
					&m_Channel,
					0));
		if (m_Buffer != NULL)
		{
			LOG(LogLevel::Debug, "PNGImage 로드 성공");
		}
	}

	PNGImage::~PNGImage()
	{
		STBI_FREE(m_Buffer);
	}

	int32 PNGImage::getWidth() const
	{
		return m_Width;
	}

	int32 PNGImage::getHeight() const
	{
		return m_Height;
	}

	int32 PNGImage::getChannel() const
	{
		return m_Channel;
	}

	const int8 * PNGImage::getBuffer() const
	{
		return m_Buffer;
	}
}