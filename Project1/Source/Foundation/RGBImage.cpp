#include "RGBImage.h"

RGBImage::RGBImage(unsigned int aWidth, unsigned int aHeight)
:	mWidth(aWidth)
,	mHeight(aHeight)
,	mRasterData(NULL)
{
	_ResetRaster();
}

RGBImage::RGBImage()
:	mWidth(1)
,	mHeight(1)
,	mRasterData(NULL)
{
	_ResetRaster();
}

void RGBImage::operator=(const RGBImage &aImg)
{
	if(mWidth != aImg.mWidth || mHeight != aImg.mHeight)
	{
		mWidth = aImg.mWidth;
		mHeight = aImg.mHeight;

		delete[] mRasterData;

		mRasterData = new ColorRGB[mWidth*mHeight];
		
	}

	SetRasterData(aImg.mRasterData);
}


void RGBImage::_ResetRaster()
{
	delete[] mRasterData;
	mRasterData = new ColorRGB[mWidth*mHeight];

	memset(mRasterData,0,mWidth*mHeight*sizeof(ColorRGB));
}

void RGBImage::FlipY()
{
	ColorRGB TmpColor;
	for(unsigned int x = 0; x < mWidth; ++x)
	{
		for(unsigned int y = 0; y < mHeight/2; ++y)
		{
			TmpColor = GetPixel(x,mHeight-y-1);

			SetPixel(x,mHeight-y-1,GetPixel(x,y));
			SetPixel(x,y,TmpColor);
		}
	}
}

void RGBImage::FlipX()
{
	ColorRGB TmpColor;
	for(unsigned int x = 0; x < mWidth/2; ++x)
	{
		for(unsigned int y = 0; y < mHeight; ++y)
		{
			TmpColor = GetPixel(mWidth - x - 1,y);

			SetPixel(mWidth - x - 1,y,GetPixel(x,y));
			SetPixel(x,y,TmpColor);
		}
	}
}

RGBImage::~RGBImage()
{
	if(mRasterData)
	{
		delete[] mRasterData;
		mRasterData = NULL;
	}
}
