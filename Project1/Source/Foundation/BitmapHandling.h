#ifndef BITMAPHANDLING_H_
#define BITMAPHANDLING_H_

#include <string>
#include <cstdio>

#include "RGBImage.h"

using namespace std;

void SaveBmp(const string &aFileName,const RGBImage &aImage);
void LoadBmp(const string &aFileName, RGBImage &aImage);

struct BitmapFileHeader
{
	BitmapFileHeader()
		:	bfType(19778),	bfSize(0),	bfReserved1(0)
		,	bfReserved2(0),	bfOffBits(0)
	{}

	void Read(FILE* pFile)
	{
		fread(&bfType,sizeof(unsigned short),1,pFile);
		fread(&bfSize,sizeof(unsigned long),1,pFile);
		fread(&bfReserved1,sizeof(unsigned short),1,pFile);
		fread(&bfReserved2,sizeof(unsigned short),1,pFile);
		fread(&bfOffBits,sizeof(unsigned long),1,pFile);
	}

	void Write(FILE* pFile)
	{
		fwrite(&bfType,sizeof(unsigned short),1,pFile);
		fwrite(&bfSize,sizeof(unsigned long),1,pFile);
		fwrite(&bfReserved1,sizeof(unsigned short),1,pFile);
		fwrite(&bfReserved2,sizeof(unsigned short),1,pFile);
		fwrite(&bfOffBits,sizeof(unsigned long),1,pFile);
	}

	unsigned short  bfType;
	unsigned long   bfSize;
	unsigned short  bfReserved1;
	unsigned short  bfReserved2;
	unsigned long   bfOffBits;
} ;

struct BitmapInfoHeader
{
	BitmapInfoHeader()
		:	biSize(40),biWidth(0),biHeight(0),biPlanes(1),biBitCount(24)
		,	biCompression(0),	biSizeImage(0),	biXPelsPerMeters(0)
		,	biYPelsPerMeters(0), biClrUsed(0),	biClrImportant(0)
	{}

	//Read and Write are implemented independently since
	//the windows' BitmapInfoHeader uses platform specific
	//compiler byte alignement tricks that are hardly portable.

	void Read(FILE* pFile)
	{
		fread(&biSize,sizeof(unsigned long),1,pFile);
		fread(&biWidth,sizeof(long),1,pFile);
		fread(&biHeight,sizeof(long),1,pFile);
		fread(&biPlanes,sizeof(unsigned short),1,pFile);
		fread(&biBitCount,sizeof(unsigned short),1,pFile);
		fread(&biCompression,sizeof(unsigned long),1,pFile);
		fread(&biSizeImage,sizeof(unsigned long),1,pFile);
		fread(&biXPelsPerMeters,sizeof(long),1,pFile);
		fread(&biYPelsPerMeters,sizeof(long),1,pFile);
		fread(&biClrUsed,sizeof(unsigned long),1,pFile);
		fread(&biClrImportant,sizeof(unsigned long),1,pFile);
	}

	void Write(FILE* pFile)
	{
		fwrite(&biSize,sizeof(unsigned long),1,pFile);
		fwrite(&biWidth,sizeof(long),1,pFile);
		fwrite(&biHeight,sizeof(long),1,pFile);
		fwrite(&biPlanes,sizeof(unsigned short),1,pFile);
		fwrite(&biBitCount,sizeof(unsigned short),1,pFile);
		fwrite(&biCompression,sizeof(unsigned long),1,pFile);
		fwrite(&biSizeImage,sizeof(unsigned long),1,pFile);
		fwrite(&biXPelsPerMeters,sizeof(long),1,pFile);
		fwrite(&biYPelsPerMeters,sizeof(long),1,pFile);
		fwrite(&biClrUsed,sizeof(unsigned long),1,pFile);
		fwrite(&biClrImportant,sizeof(unsigned long),1,pFile);
	}

	unsigned long		biSize;
	long				biWidth;
	long				biHeight;
	unsigned short		biPlanes;
	unsigned short		biBitCount;
	unsigned long		biCompression;
	unsigned long		biSizeImage;
	long				biXPelsPerMeters;
	long				biYPelsPerMeters;
	unsigned long		biClrUsed;
	unsigned long		biClrImportant;
};

#endif //BITMAPHANDLING_H_
