#ifndef PCX_HANDLING_H_
#define PCX_HANDLING_H_

#include <string>
#include <cstdio>

#include "RGBImage.h"

using namespace std;

void LoadPCX(const string &ao_FileName, RGBImage &ao_Image);

struct PCXHeader
{
	PCXHeader(){};

	void Read(FILE* apo_File)
	{
		fread(&mu8_Manufacturer,sizeof(unsigned char),1,apo_File);
		fread(&mu8_Version,sizeof(unsigned char),1,apo_File);
		fread(&mu8_Encoding,sizeof(unsigned char),1,apo_File);
		fread(&mu8_BitsPerPixel,sizeof(unsigned char),1,apo_File);

		fread(&mu16_X,sizeof(unsigned short),1,apo_File);
		fread(&mu16_Y,sizeof(unsigned short),1,apo_File);
		fread(&mu16_Width,sizeof(unsigned short),1,apo_File);
		fread(&mu16_Height,sizeof(unsigned short),1,apo_File);
		fread(&mu16_HorDPI,sizeof(unsigned short),1,apo_File);
		fread(&mu16_VertDPI,sizeof(unsigned short),1,apo_File);

		fread(&mtu8_ColorMapSettings,sizeof(unsigned char),48,apo_File);
		fread(&mu8_ReservedShouldBeZero,sizeof(unsigned char),1,apo_File);
		fread(&mu8_NbColorPlanes,sizeof(unsigned char),1,apo_File);

		fread(&mu16_BytesPerScanLine,sizeof(unsigned short),1,apo_File);
		fread(&mu16_PaletteType,sizeof(unsigned short),1,apo_File);
		fread(&mu16_HorSize,sizeof(unsigned short),1,apo_File);
		fread(&mu16_VertSize,sizeof(unsigned short),1,apo_File);

		fread(&mtu8_CareyPricePads,sizeof(unsigned char),54,apo_File);

	}

	unsigned char	mu8_Manufacturer;
	unsigned char	mu8_Version;
	unsigned char	mu8_Encoding;
	unsigned char	mu8_BitsPerPixel;

	unsigned short	mu16_X;
	unsigned short	mu16_Y;
	unsigned short	mu16_Width;
	unsigned short	mu16_Height;
	unsigned short	mu16_HorDPI;
	unsigned short	mu16_VertDPI;

	unsigned char	mtu8_ColorMapSettings[48];
	unsigned char	mu8_ReservedShouldBeZero;
	unsigned char	mu8_NbColorPlanes;
	
	unsigned short	mu16_BytesPerScanLine;
	unsigned short	mu16_PaletteType;
	unsigned short	mu16_HorSize;
	unsigned short	mu16_VertSize;

	unsigned char	mtu8_CareyPricePads[54]; //Padding bytes
};


#endif //PCX_HANDLING_H_
