#pragma once
#include "Resource.h"


namespace DS
{
	class PNGImage : public Resource
	{
	public:
		PNGImage(int8 * buffer, tsize len);
		virtual ~PNGImage();

		int32 getWidth() const;
		int32 getHeight() const;
		int32 getChannel() const;
		const int8 * getBuffer() const;

	private:
		int32 m_Width;
		int32 m_Height;
		int32 m_Channel;

		int8* m_Buffer;
	};
}