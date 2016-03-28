#ifndef RGBIMAGE_H_
#define RGBIMAGE_H_

#include <cstring>

#include "ColorRGB.h"

class RGBImage
{
public:

	RGBImage(unsigned int aWidth, unsigned int aHeight);
	RGBImage();
	virtual ~RGBImage();

	const ColorRGB operator()(unsigned int mXCoord, unsigned int mYCoord) const;
	ColorRGB& operator()(unsigned int mXCoord, unsigned int mYCoord);

	operator const ColorRGB *() const;
	operator ColorRGB *();

	void operator=(const RGBImage &aImg);

	ColorRGB GetPixel(unsigned int mX, unsigned int mY);
	void SetPixel(unsigned int mX, unsigned int mY, const ColorRGB &aColor);

	const ColorRGB* GetRasterData() const;
	ColorRGB* GetRasterData();
	void SetRasterData(const ColorRGB *aRaster);

	unsigned int GetWidth() const;
	void SetWidth(unsigned int aWidth);

	unsigned int GetHeight() const;
	void SetHeight(unsigned int aHeight);

	void FlipY();
	void FlipX();

	void Resize(unsigned int aWidth, unsigned int aHeight);

protected:

	void _ResetRaster();

	ColorRGB		*mRasterData;

	unsigned int	mWidth;
	unsigned int	mHeight;
};

inline const ColorRGB RGBImage::operator()(unsigned int mXCoord, unsigned int mYCoord) const
{
	return mRasterData[mYCoord * mWidth + mXCoord];
}

inline ColorRGB &RGBImage::operator()(unsigned int mXCoord, unsigned int mYCoord)
{
	return mRasterData[mYCoord * mWidth + mXCoord];
}

inline RGBImage::operator const ColorRGB*() const
{
	return mRasterData;
}

inline RGBImage::operator ColorRGB *()
{
	return mRasterData;
}

inline ColorRGB RGBImage::GetPixel(unsigned int mX, unsigned int mY)
{
	return mRasterData[mY * mWidth + mX];
}

inline void RGBImage::SetPixel(unsigned int mX, unsigned int mY, const ColorRGB &aColor)
{
	mRasterData[mY * mWidth + mX] = aColor;
}

inline unsigned int RGBImage::GetWidth() const
{
	return mWidth;
}

inline void RGBImage::SetWidth(unsigned int aWidth)
{
	mWidth = aWidth;
	_ResetRaster();
}

inline unsigned int RGBImage::GetHeight() const
{
	return mHeight;
}

inline void RGBImage::SetHeight(unsigned int aHeight)
{
	mHeight = aHeight;
	_ResetRaster();
}

inline const ColorRGB* RGBImage::GetRasterData() const
{
	return mRasterData;
}

inline ColorRGB* RGBImage::GetRasterData()
{
	return mRasterData;
}

inline void RGBImage::SetRasterData(const ColorRGB *aRaster)
{
	memcpy(mRasterData,aRaster,mWidth*mHeight*sizeof(ColorRGB));
}

inline void RGBImage::Resize(unsigned int aWidth, unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	_ResetRaster();
}


#endif //RGBIMAGE_H_
