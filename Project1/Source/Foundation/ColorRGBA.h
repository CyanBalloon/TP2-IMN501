#ifndef ColorRGBA_H_
#define ColorRGBA_H_

#include<cassert>

class ColorRGBA
{
public:
	ColorRGBA();
	ColorRGBA(const ColorRGBA &aColor);
	ColorRGBA(float aR, float aG, float aB, float aAlpha = 1.0f);

	//!@brief Will set color components to 0.0 if they're below 0.0 or 1.0 if they're above 1.0.
	void Clamp();

	//Member access
	operator const float*() const;
	operator float*();
	float operator[](int i) const;
	float& operator[](int i);
	float R() const;
	float& R();
	float G() const;
	float& G();
	float B() const;
	float& B();
	float Alpha() const;
	float& Alpha();

	//Assignement operator
	ColorRGBA& operator=(const ColorRGBA &aRHS);
	
	//Arithmetic operators
	ColorRGBA operator+(const ColorRGBA &aRHS) const;
	ColorRGBA operator-(const ColorRGBA &aRHS) const;
	ColorRGBA operator*(const ColorRGBA &aRHS) const;
	ColorRGBA operator*(float aRHS) const;
	ColorRGBA operator/(const ColorRGBA &aRHS) const;
	ColorRGBA operator/(float aRHS) const;

	//Arithmetic updates
	ColorRGBA& operator +=(const ColorRGBA &aRHS);
	ColorRGBA& operator -=(const ColorRGBA &aRHS);
	ColorRGBA& operator *=(const ColorRGBA &aRHS);
	ColorRGBA& operator *=(float aRHS);
	ColorRGBA& operator /=(const ColorRGBA &aRHS);
	ColorRGBA& operator /=(float aRHS);
	
	//Comparison operators
	bool operator==(const ColorRGBA &aRHS) const;
	bool operator!=(const ColorRGBA &aRHS) const;

	//Built-in colors
	static const ColorRGBA PureRed;
	static const ColorRGBA PureGreen;
	static const ColorRGBA PureBlue;
	static const ColorRGBA White;
	static const ColorRGBA Black;
	static const ColorRGBA Invalid;

protected:

	union
	{
		float mComponents[4];
		struct 
		{
			float mR;
			float mG;
			float mB;
			float mAlpha;
		};

	};
};

ColorRGBA operator*(float aLHS, ColorRGBA aRHS);

inline ColorRGBA::operator const float*() const
{
	return mComponents;
}

inline ColorRGBA::operator float*()
{
	return mComponents;
}

inline float ColorRGBA::operator[](int i) const
{
	assert(i >= 0 && i <= 3);
	return mComponents[i];
}

inline float& ColorRGBA::operator[](int i)
{
	assert(i >= 0 && i <= 3);
	return mComponents[i];
}

inline float& ColorRGBA::R()
{
	return mR;
}

inline float ColorRGBA::R() const
{
	return mR;
}

inline float& ColorRGBA::G()
{
	return mG;
}

inline float ColorRGBA::G() const
{
	return mG;
}

inline float& ColorRGBA::B()
{
	return mB;
}

inline float ColorRGBA::B() const
{
	return mB;
}

inline float ColorRGBA::Alpha() const
{
	return mAlpha;
}

inline float& ColorRGBA::Alpha()
{
	return mAlpha;
}

#endif //ColorRGBA_H_
