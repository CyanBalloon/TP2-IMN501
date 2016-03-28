#include "PcxHandling.h"

void LoadPCX(const string &ao_FileName, RGBImage &ao_Image)
{
	FILE* po_File = fopen(ao_FileName.c_str(),"rb");

	PCXHeader	o_Header;

	o_Header.Read(po_File);

	if(	o_Header.mu8_Manufacturer	!= 10	||
		o_Header.mu8_Version		!= 5	||
		o_Header.mu8_Encoding		!= 1	||
		o_Header.mu8_BitsPerPixel	!= 8	)

	{
		fprintf(stdout,"Only version 5 PCX encoded with 8 bits per pixels are supported.\n");
		fclose(po_File);
		return;
	}

	o_Header.mu16_Width =	o_Header.mu16_Width -	o_Header.mu16_X	+ 1;
	o_Header.mu16_Height =	o_Header.mu16_Height -	o_Header.mu16_Y	+ 1;

	ao_Image.Resize(o_Header.mu16_Width,o_Header.mu16_Height);

	int s32_CurrentPos = ftell(po_File);
	fseek(po_File,0,SEEK_END);
	int s32_FileEnd = ftell(po_File);
	fseek(po_File,s32_CurrentPos,SEEK_SET);

	//Faut peut être faire +1 ici, à vérifier
	int s32_BufferSize = s32_FileEnd - s32_CurrentPos + 1;

	char* pts8_Buffer = new char[s32_BufferSize];
	fread(pts8_Buffer,sizeof(char),s32_BufferSize,po_File);
	char* ps8_BufferPtr = pts8_Buffer;

	unsigned char* ptu8_PalettedData = new unsigned char[o_Header.mu16_Width * o_Header.mu16_Height];

	int s32_Idx = 0;
	unsigned char u8_c;
	int s32_NbRepeat;
	while(s32_Idx < (o_Header.mu16_Width * o_Header.mu16_Height))
	{
		if( (u8_c = *(ps8_BufferPtr++)) > 0xbf)
		{
			s32_NbRepeat = 0x3f & u8_c;
			u8_c = *(ps8_BufferPtr++);

			for(int i = 0; i < s32_NbRepeat; ++i)
			{
				ptu8_PalettedData[s32_Idx++] = u8_c;
			}
		}
		else
		{
			ptu8_PalettedData[s32_Idx++] = u8_c;
		}
	}

	//La palette es trouve 769 bytes avant la fin de l'image.
	unsigned char* pu8_PalettePtr = (unsigned char*)(&pts8_Buffer[s32_BufferSize - 769]);
	unsigned char*  pu8_PaletteRasterPtr = ptu8_PalettedData;

	for(int y = 0; y < o_Header.mu16_Height; ++y)
	{
		for(int x = 0; x < o_Header.mu16_Width; ++x)
		{
			int s32_Offset = *(pu8_PaletteRasterPtr) * 3;
			pu8_PaletteRasterPtr++;

			ColorRGB o_TmpColor;
			o_TmpColor.R() = pu8_PalettePtr[s32_Offset+0]/255.0f; 
			o_TmpColor.G() = pu8_PalettePtr[s32_Offset+1]/255.0f; 
			o_TmpColor.B() = pu8_PalettePtr[s32_Offset+2]/255.0f; 
		
			ao_Image.SetPixel(x,y,o_TmpColor);
		}
	}
	delete[] ptu8_PalettedData; ptu8_PalettedData = NULL;
	delete[] pts8_Buffer; pts8_Buffer = NULL;

	fclose(po_File);

}


