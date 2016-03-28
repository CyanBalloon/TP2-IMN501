#include "ColorRGBA.h"

const ColorRGBA ColorRGBA::PureRed(1.0f,0.0f,0.0f,1.0f);
const ColorRGBA ColorRGBA::PureGreen(0.0f,1.0f,0.0f,1.0f);
const ColorRGBA ColorRGBA::PureBlue(0.0f,0.0f,1.0f,1.0f);
const ColorRGBA ColorRGBA::White(1.0f,1.0f,1.0f,1.0f);
const ColorRGBA ColorRGBA::Black(0.0f,0.0f,0.0f,1.0f);
const ColorRGBA ColorRGBA::Invalid(-1.0f,-1.0f,-1.0f,1.0f);

ColorRGBA::ColorRGBA()
:	mR(0.0f)
,	mG(0.0f)
,	mB(0.0f)
,	mAlpha(0.0f)
{}

ColorRGBA::ColorRGBA(const ColorRGBA &aColor)
:	mR(aColor.mR)
,	mG(aColor.mG)
,	mB(aColor.mB)
,	mAlpha(aColor.mAlpha)
{}

ColorRGBA::ColorRGBA(float aR, float aG, float aB, float aAlpha)
:	mR(aR)
,	mG(aG)
,	mB(aB)
,	mAlpha(aAlpha)
{}

void ColorRGBA::Clamp()
{
	for(int i = 0; i < 4; ++i)
	{
		if(mComponents[i] < 0.0f)
		{
			mComponents[i] = 0.0f;
		}
		else if(mComponents[i] > 1.0f)
		{
			mComponents[i] = 1.0f;
		}
	}
}

ColorRGBA& ColorRGBA::operator=(const ColorRGBA &aRHS)
{
	mR = aRHS.mR;
	mG = aRHS.mG;
	mB = aRHS.mB;
	mAlpha = aRHS.mAlpha;

	return *this;
}

ColorRGBA ColorRGBA::operator+(const ColorRGBA &aRHS) const
{
	return ColorRGBA	(	mR + aRHS.mR,
						mG + aRHS.mG,
						mB + aRHS.mB,
						mAlpha + aRHS.mAlpha
					);
}

ColorRGBA ColorRGBA::operator-(const ColorRGBA &aRHS) const
{
	return ColorRGBA	(	mR - aRHS.mR,
						mG - aRHS.mG,
						mB - aRHS.mB,
						mAlpha - aRHS.mAlpha
		);
}

ColorRGBA ColorRGBA::operator*(const ColorRGBA &aRHS) const
{
	return ColorRGBA	(	mR * aRHS.mR,
						mG * aRHS.mG,
						mB * aRHS.mB,
						mAlpha * aRHS.mAlpha
		);
}

ColorRGBA ColorRGBA::operator*(float aRHS) const
{
	return ColorRGBA	(	mR * aRHS,
						mG * aRHS,
						mB * aRHS,
						mAlpha * aRHS
		);	
}

ColorRGBA ColorRGBA::operator/(const ColorRGBA &aRHS) const
{
	return ColorRGBA	(	mR / aRHS.mR,
						mG / aRHS.mG,
						mB / aRHS.mB,
						mAlpha * aRHS.mAlpha
		);
}

ColorRGBA ColorRGBA::operator/( float aRHS) const
{
	assert(aRHS != 0.0f);
	return ColorRGBA	(	mR / aRHS,
						mG / aRHS,
						mB / aRHS,
						mAlpha / aRHS
		);
}

ColorRGBA& ColorRGBA::operator +=(const ColorRGBA &aRHS)
{
	mR += aRHS.mR;
	mG += aRHS.mG;
	mB += aRHS.mB;
	mAlpha += aRHS.mAlpha;

	return *this;
}

ColorRGBA& ColorRGBA::operator -=(const ColorRGBA &aRHS)
{
	mR -= aRHS.mR;
	mG -= aRHS.mG;
	mB -= aRHS.mB;
	mAlpha += aRHS.mAlpha;

	return *this;
}

ColorRGBA& ColorRGBA::operator *=(const ColorRGBA &aRHS)
{
	mR *= aRHS.mR;
	mG *= aRHS.mG;
	mB *= aRHS.mB;
	mAlpha *= aRHS.mAlpha;

	return *this;
}

ColorRGBA& ColorRGBA::operator *=(float aRHS)
{
	mR *= aRHS;
	mG *= aRHS;
	mB *= aRHS;
	mAlpha *= aRHS;

	return *this;
}

ColorRGBA& ColorRGBA::operator /=(const ColorRGBA &aRHS)
{
	mR /= aRHS.mR;
	mG /= aRHS.mG;
	mB /= aRHS.mB;
	mAlpha /= aRHS.mAlpha;

	return *this;
}

ColorRGBA& ColorRGBA::operator /=(float aRHS)
{
	assert(aRHS != 0.0f);
	mR /= aRHS;
	mG /= aRHS;
	mB /= aRHS;
	mAlpha /= aRHS;

	return *this;
}

bool ColorRGBA::operator==(const ColorRGBA &aRHS) const
{
	return	mR == aRHS.mR &&
			mG == aRHS.mG &&
			mB == aRHS.mB &&
			mAlpha == aRHS.mAlpha;
}

bool ColorRGBA::operator!=(const ColorRGBA &aRHS) const
{
	return	mR != aRHS.mR	||
		mG != aRHS.mG		||
		mB != aRHS.mB		||
		mAlpha != aRHS.mAlpha;
}

ColorRGBA operator*(float aLHS, ColorRGBA aRHS)
{
	return ColorRGBA(	aLHS * aRHS.R(),
						aLHS * aRHS.G(),
						aLHS * aRHS.B(),
						aLHS * aRHS.Alpha()
					);
}
