#include "BitmapHandling.h"

void SaveBmp(const string &aFileName,const RGBImage &aImage)
{
	FILE* pFile = fopen(aFileName.c_str(),"wb+");
	
	BitmapFileHeader oFileHeader;
	BitmapInfoHeader oInfoHeader;

	oInfoHeader.biWidth =		aImage.GetWidth();
	oInfoHeader.biHeight =		aImage.GetHeight();

	//We compute stride sizes. A stride must be a factor
	//of 4.
	int StrideSize = oInfoHeader.biWidth * 3;
	if((oInfoHeader.biWidth*3)%4)
	{
		StrideSize += 4-((oInfoHeader.biWidth*3)%4);
	}

	//Only 24 bit mot is encoded (1 char per color components)
	//other modes require a palette, which would be a big more
	//complicated here.
	oInfoHeader.biBitCount =	24;
	oInfoHeader.biSizeImage =	StrideSize * oInfoHeader.biHeight;
	
	//Offset & size. (File header = 14 bytes, File info = 40 bytes)
	oFileHeader.bfOffBits = 54;
	oFileHeader.bfSize = 54 + sizeof(char) * StrideSize * oInfoHeader.biHeight;

	unsigned char * pBuffer = new unsigned char[StrideSize];

	//Write header information in the bmp file.
	oFileHeader.Write(pFile);
	oInfoHeader.Write(pFile);

	//Write raster data in the bmp file.
	//The y axis is inverted in bmp files, this is why we're
	//copying lines backward.
	for(int i = oInfoHeader.biHeight-1 ;i >=0; --i)
	{
		for(int j = 0; j < oInfoHeader.biWidth; ++j)
		{
			ColorRGB PixelColor = aImage.GetRasterData()[i*oInfoHeader.biWidth + j];
			PixelColor.Clamp();

			pBuffer[j*3] =		(unsigned char)(PixelColor.B()*255);
			pBuffer[j*3+1] =	(unsigned char)(PixelColor.G()*255);
			pBuffer[j*3+2] =	(unsigned char)(PixelColor.R()*255);
		}
		fwrite(pBuffer,StrideSize,1,pFile);
	}

	delete[] pBuffer;

	fclose(pFile);
}

void LoadBmp(const string &aFileName, RGBImage &aImage)
{
	FILE* pFile = fopen(aFileName.c_str(),"rb+");

	BitmapFileHeader oFileHeader;
	BitmapInfoHeader oInfoHeader;

	//Read header information
	oFileHeader.Read(pFile);
	oInfoHeader.Read(pFile);

	if(oInfoHeader.biBitCount != 24)
	{
		fprintf(stdout,"Bitmaps with bit count different than 24 are not supported.\n");
		fclose(pFile);
		return;
	}

	aImage.Resize(oInfoHeader.biWidth,oInfoHeader.biHeight);

	int StrideSize = (oFileHeader.bfSize-54)/(oInfoHeader.biHeight*sizeof(char));

	unsigned char *tBuffer = new unsigned char[StrideSize];

	for(int i = 0; i < oInfoHeader.biHeight; ++i)
	{
		fread(tBuffer,StrideSize,1,pFile);
		for(int j = 0; j < oInfoHeader.biWidth; ++j)
		{
			aImage.GetRasterData()[(aImage.GetHeight()-i-1)*aImage.GetWidth()+j] = ColorRGB(tBuffer[3*j+2]/255.0f,tBuffer[3*j+1]/255.0f, tBuffer[3*j]/255.0f);
		}
	}

	fclose(pFile);
	delete[] tBuffer;
}
		
