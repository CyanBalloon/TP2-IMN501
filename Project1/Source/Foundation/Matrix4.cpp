#include "Matrix4.h"

#include <cmath>
#include <cstring>

#ifndef PI
#define PI 3.14159265358979323846f
#endif

Matrix4::Matrix4()
:	m11(1.0f),	m12(0.0f),	m13(0.0f),	m14(0.0f)
,	m21(0.0f),	m22(1.0f),	m23(0.0f),	m24(0.0f)
,	m31(0.0f),	m32(0.0f),	m33(1.0f),	m34(0.0f)
,	m41(0.0f),	m42(0.0f),	m43(0.0f),	m44(1.0f)
,	mIdentity(true)
{}

Matrix4::Matrix4(const Matrix4 &aRHS)
:	mIdentity(aRHS.mIdentity)
{
	memcpy(_mComponents,aRHS._mComponents,16*sizeof(float));
}

Matrix4::Matrix4(float a11, float a12, float a13, float a14, 
				 float a21, float a22, float a23, float a24, 
				 float a31, float a32, float a33, float a34, 
				 float a41, float a42, float a43, float a44)
 :	m11(a11),	m12(a12),	m13(a13),	m14(a14)
 ,	m21(a21),	m22(a22),	m23(a23),	m24(a24)
 ,	m31(a31),	m32(a32),	m33(a33),	m34(a34)
 ,	m41(a41),	m42(a42),	m43(a43),	m44(a44)
 ,	mIdentity(false)
{}

Matrix4 Matrix4::GetInverse() const
{
	//Inverse calculated with Kramer's method.

	float m00 = mComponents[0][0], m01 = mComponents[0][1], m02 = mComponents[0][2], m03 = mComponents[0][3];
	float m10 = mComponents[1][0], m11 = mComponents[1][1], m12 = mComponents[1][2], m13 = mComponents[1][3];
	float m20 = mComponents[2][0], m21 = mComponents[2][1], m22 = mComponents[2][2], m23 = mComponents[2][3];
	float m30 = mComponents[3][0], m31 = mComponents[3][1], m32 = mComponents[3][2], m33 = mComponents[3][3];

	float v0 = m20 * m31 - m21 * m30;
	float v1 = m20 * m32 - m22 * m30;
	float v2 = m20 * m33 - m23 * m30;
	float v3 = m21 * m32 - m22 * m31;
	float v4 = m21 * m33 - m23 * m31;
	float v5 = m22 * m33 - m23 * m32;

	float t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	float t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	float t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	float t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	float invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	float d00 = t00 * invDet;
	float d10 = t10 * invDet;
	float d20 = t20 * invDet;
	float d30 = t30 * invDet;

	float d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	float d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	float d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	float d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	float d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	float d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return Matrix4(
		d00, d01, d02, d03,
		d10, d11, d12, d13,
		d20, d21, d22, d23,
		d30, d31, d32, d33);
}

void Matrix4::operator=(const Matrix4 &aRHS)
{
	memcpy(_mComponents,aRHS._mComponents,16*sizeof(float));
	mIdentity = aRHS.mIdentity;
}

void Matrix4::SetTranslationData(const Vector3 &aVector)
{
	m14 = aVector.X();
	m24 = aVector.Y();
	m34 = aVector.Z();
	mIdentity = false;
}

Vector3 Matrix4::GetTranslationData() const
{
	return Vector3(m14,m24,m34);
}

void Matrix4::MakeIdentity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; m14 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f; m24 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f; m34 = 0.0f;
	m41 = 0.0f; m42 = 0.0f; m43 = 0.0f; m44 = 1.0f;

	mIdentity = true;
}

void Matrix4::MakeTranslationMatrix(const Vector3 &aVec)
{
	MakeIdentity();
	SetTranslationData(aVec);
}

void Matrix4::MakeTranslationMatrix(float aX, float aY, float aZ)
{
	MakeIdentity();
	SetTranslationData(Vector3(aX,aY,aZ));
}

void Matrix4::SetScale(const Vector3 &aVec)
{
	m11 = aVec.X();
	m22 = aVec.Y();
	m33 = aVec.Z();
	mIdentity = false;
}

void Matrix4::RotateAroundXRad(float aRadian)
{
	float PrecalcCos = cos(aRadian);
	float PrecalcSin = sin(aRadian);
	
	if(mIdentity)
	{
		m22 = PrecalcCos;
		m23 = -PrecalcSin;
		m32 = PrecalcSin;
		m33 = PrecalcCos;
	
		mIdentity = false;
	}
	else
	{
		//We cache these values since
		//they will be modified during the process.
		float tmpm12 = m12;
		float tmpm22 = m22;
		float tmpm32 = m32;
		float tmpm42 = m42;

		m12 = tmpm12*PrecalcCos + m13*PrecalcSin;
		m22 = tmpm22*PrecalcCos + m23*PrecalcSin;
		m32 = tmpm32*PrecalcCos + m33*PrecalcSin;
		m42 = tmpm42*PrecalcCos + m43*PrecalcSin;

		m13 = m13*PrecalcCos - tmpm12*PrecalcSin;
		m23 = m23*PrecalcCos - tmpm22*PrecalcSin;
		m33 = m33*PrecalcCos - tmpm32*PrecalcSin;
		m43 = m43*PrecalcCos - tmpm42*PrecalcSin;
	}
}

void Matrix4::RotateAroundXDeg(float aDeg)
{
	RotateAroundXRad(float(aDeg * PI)/180.0f);
}

void Matrix4::RotateAroundYRad(float aRadian)
{
	float PrecalcCos = cos(aRadian);
	float PrecalcSin = sin(aRadian);

	if(mIdentity)
	{
		m11 = PrecalcCos;
		m31 = -PrecalcSin;
		m13 = PrecalcSin;
		m33 = PrecalcCos;

		mIdentity = false;
	}
	else
	{
		float tmpm11 = m11;
		float tmpm21 = m21;
		float tmpm31 = m31;
		float tmpm41 = m41;

		m11 = tmpm11 * PrecalcCos - m13 * PrecalcSin;
		m21 = tmpm21 * PrecalcCos - m23 * PrecalcSin;
		m31 = tmpm31 * PrecalcCos - m33 * PrecalcSin;
		m41 = tmpm41 * PrecalcCos - m43 * PrecalcSin;

		m13 = tmpm11 * PrecalcSin + m13 * PrecalcCos;
		m23 = tmpm21 * PrecalcSin + m23 * PrecalcCos;
		m33 = tmpm31 * PrecalcSin + m33 * PrecalcCos;
		m43 = tmpm41 * PrecalcSin + m43 * PrecalcCos;
	}
}

void Matrix4::RotateAroundYDeg(float aDeg)
{
	RotateAroundYRad(float(aDeg * PI)/180.0f);
}

void Matrix4::RotateAroundZRad(float aRadian)
{
	float PrecalcCos = cos(aRadian);
	float PrecalcSin = sin(aRadian);

	if(mIdentity)
	{
		m11 = PrecalcCos;
		m21 = PrecalcSin;
		m12 = -PrecalcSin;
		m22 = PrecalcCos;

		mIdentity = false;
	}
	else
	{
		float tmpm11 = m11;
		float tmpm21 = m21;
		float tmpm31 = m31;
		float tmpm41 = m41;

		m11 = tmpm11 * PrecalcCos + m12 * PrecalcSin;
		m21 = tmpm21 * PrecalcCos + m22 * PrecalcSin;
		m31 = tmpm31 * PrecalcCos + m32 * PrecalcSin;
		m41 = tmpm41 * PrecalcCos + m42 * PrecalcSin;

		m12 = m12 * PrecalcCos - tmpm11 * PrecalcSin;
		m22 = m22 * PrecalcCos - tmpm21 * PrecalcSin;
		m32 = m32 * PrecalcCos - tmpm31 * PrecalcSin;
		m42 = m42 * PrecalcCos - tmpm41 * PrecalcSin;
	}
}

void Matrix4::RotateAroundZDeg(float aDeg)
{
	RotateAroundZRad(float(aDeg * PI)/180.0f);
}

Matrix4 Matrix4::GenerateOrthogonalBaseFromAxis(const Vector3 &aAxis)
{
	Vector3 FirstVector = aAxis.NormalisedCopy();
	Vector3 SecondVector;
	Vector3 ThirdVector;
	if(aAxis != Vector3::UnitX)
	{
		SecondVector = Vector3::UnitX;
	}
	else
	{
		SecondVector = Vector3::UnitY;
	}

	ThirdVector = FirstVector.CrossProduct(SecondVector).NormalisedCopy();
	SecondVector = FirstVector.CrossProduct(ThirdVector).NormalisedCopy();

	return Matrix4(		SecondVector.X(),	SecondVector.Y(),	SecondVector.Z(),	0,
						FirstVector.X(),	FirstVector.Y(),	FirstVector.Z(),	0,
						ThirdVector.X(),	ThirdVector.Y(),	ThirdVector.Z(),	0,
						0,					0,					0,					1);
}


Matrix4 Matrix4::GenerateCoordinatesChangeMatrix(const Vector3 &aInitialAxis1, 
										 const Vector3 &aInitialAxis2, 
										 const Vector3 &aInitialAxis3, 
										 const Vector3 &aInitialOrigin, 
										 const Vector3 &aResultingAxis1, 
										 const Vector3 &aResultingAxis2, 
										 const Vector3 &aResultingAxis3, 
										 const Vector3 &aResultingOrigin)
{
	Matrix4 FirstOrigin(1,0,0,aInitialOrigin.X(),
						0,1,0,aInitialOrigin.Y(),
						0,0,1,aInitialOrigin.Z(),
						0,0,0,1);

	Matrix4 FirstONB(	aInitialAxis1.X(),aInitialAxis2.X(),aInitialAxis3.X(),0,
						aInitialAxis1.Y(),aInitialAxis2.Y(),aInitialAxis3.Y(),0,
						aInitialAxis1.Z(),aInitialAxis2.Z(),aInitialAxis3.Z(),0,
						0,0,0,1);

	Matrix4 SecondOrigin(	1,0,0,-aResultingOrigin.X(),
							0,1,0,-aResultingOrigin.Y(),
							0,0,1,-aResultingOrigin.Z(),
							0,0,0,1);

	Matrix4 SecondONB(	aResultingAxis1.X(),aResultingAxis2.X(),aResultingAxis3.X(),0,
						aResultingAxis1.Y(),aResultingAxis2.Y(),aResultingAxis3.Y(),0,
						aResultingAxis1.Z(),aResultingAxis2.Z(),aResultingAxis3.Z(),0,
						0,0,0,1);

	return SecondONB * SecondOrigin * FirstOrigin * FirstONB;
}

Matrix4 Matrix4::operator*(const Matrix4 &aRHS) const
{
	if(mIdentity)
	{
		return aRHS;
	}
	else if (aRHS.mIdentity)
	{
		return *this;
	}
	else
	{
		Matrix4 r;
		r.mIdentity = false;

		r.mComponents[0][0] = mComponents[0][0] * aRHS.mComponents[0][0] + mComponents[0][1] * aRHS.mComponents[1][0] + mComponents[0][2] * aRHS.mComponents[2][0] + mComponents[0][3] * aRHS.mComponents[3][0];
		r.mComponents[0][1] = mComponents[0][0] * aRHS.mComponents[0][1] + mComponents[0][1] * aRHS.mComponents[1][1] + mComponents[0][2] * aRHS.mComponents[2][1] + mComponents[0][3] * aRHS.mComponents[3][1];
		r.mComponents[0][2] = mComponents[0][0] * aRHS.mComponents[0][2] + mComponents[0][1] * aRHS.mComponents[1][2] + mComponents[0][2] * aRHS.mComponents[2][2] + mComponents[0][3] * aRHS.mComponents[3][2];
		r.mComponents[0][3] = mComponents[0][0] * aRHS.mComponents[0][3] + mComponents[0][1] * aRHS.mComponents[1][3] + mComponents[0][2] * aRHS.mComponents[2][3] + mComponents[0][3] * aRHS.mComponents[3][3];

		r.mComponents[1][0] = mComponents[1][0] * aRHS.mComponents[0][0] + mComponents[1][1] * aRHS.mComponents[1][0] + mComponents[1][2] * aRHS.mComponents[2][0] + mComponents[1][3] * aRHS.mComponents[3][0];
		r.mComponents[1][1] = mComponents[1][0] * aRHS.mComponents[0][1] + mComponents[1][1] * aRHS.mComponents[1][1] + mComponents[1][2] * aRHS.mComponents[2][1] + mComponents[1][3] * aRHS.mComponents[3][1];
		r.mComponents[1][2] = mComponents[1][0] * aRHS.mComponents[0][2] + mComponents[1][1] * aRHS.mComponents[1][2] + mComponents[1][2] * aRHS.mComponents[2][2] + mComponents[1][3] * aRHS.mComponents[3][2];
		r.mComponents[1][3] = mComponents[1][0] * aRHS.mComponents[0][3] + mComponents[1][1] * aRHS.mComponents[1][3] + mComponents[1][2] * aRHS.mComponents[2][3] + mComponents[1][3] * aRHS.mComponents[3][3];

		r.mComponents[2][0] = mComponents[2][0] * aRHS.mComponents[0][0] + mComponents[2][1] * aRHS.mComponents[1][0] + mComponents[2][2] * aRHS.mComponents[2][0] + mComponents[2][3] * aRHS.mComponents[3][0];
		r.mComponents[2][1] = mComponents[2][0] * aRHS.mComponents[0][1] + mComponents[2][1] * aRHS.mComponents[1][1] + mComponents[2][2] * aRHS.mComponents[2][1] + mComponents[2][3] * aRHS.mComponents[3][1];
		r.mComponents[2][2] = mComponents[2][0] * aRHS.mComponents[0][2] + mComponents[2][1] * aRHS.mComponents[1][2] + mComponents[2][2] * aRHS.mComponents[2][2] + mComponents[2][3] * aRHS.mComponents[3][2];
		r.mComponents[2][3] = mComponents[2][0] * aRHS.mComponents[0][3] + mComponents[2][1] * aRHS.mComponents[1][3] + mComponents[2][2] * aRHS.mComponents[2][3] + mComponents[2][3] * aRHS.mComponents[3][3];

		r.mComponents[3][0] = mComponents[3][0] * aRHS.mComponents[0][0] + mComponents[3][1] * aRHS.mComponents[1][0] + mComponents[3][2] * aRHS.mComponents[2][0] + mComponents[3][3] * aRHS.mComponents[3][0];
		r.mComponents[3][1] = mComponents[3][0] * aRHS.mComponents[0][1] + mComponents[3][1] * aRHS.mComponents[1][1] + mComponents[3][2] * aRHS.mComponents[2][1] + mComponents[3][3] * aRHS.mComponents[3][1];
		r.mComponents[3][2] = mComponents[3][0] * aRHS.mComponents[0][2] + mComponents[3][1] * aRHS.mComponents[1][2] + mComponents[3][2] * aRHS.mComponents[2][2] + mComponents[3][3] * aRHS.mComponents[3][2];
		r.mComponents[3][3] = mComponents[3][0] * aRHS.mComponents[0][3] + mComponents[3][1] * aRHS.mComponents[1][3] + mComponents[3][2] * aRHS.mComponents[2][3] + mComponents[3][3] * aRHS.mComponents[3][3];

		return r;
	}
}

Vector3 Matrix4::operator*(const Vector3 &aRHS) const
{
	if(mIdentity)
	{
		return aRHS;
	}
	else
	{
		Vector3 r;

		float fInvW = 1.0f / ( mComponents[3][0] * aRHS.X() + mComponents[3][1] * aRHS.Y() + mComponents[3][2] * aRHS.Z() + mComponents[3][3] );
		
		r.X() = ( mComponents[0][0] * aRHS.X() + mComponents[0][1] * aRHS.Y() + mComponents[0][2] * aRHS.Z() + mComponents[0][3] ) * fInvW;
		r.Y() = ( mComponents[1][0] * aRHS.X() + mComponents[1][1] * aRHS.Y() + mComponents[1][2] * aRHS.Z() + mComponents[1][3] ) * fInvW;
		r.Z() = ( mComponents[2][0] * aRHS.X() + mComponents[2][1] * aRHS.Y() + mComponents[2][2] * aRHS.Z() + mComponents[2][3] ) * fInvW;
		
		return r;
	}
}

Matrix4& Matrix4::operator+=(const Matrix4 &aRHS)
{
	for(int i = 0; i < 16; ++i)
	{
		_mComponents[i] += aRHS._mComponents[i];
	}

	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4 &aRHS)
{
	for(int i = 0; i < 16; ++i)
	{
		_mComponents[i] -= aRHS._mComponents[i];
	}

	return *this;
}

Matrix4& Matrix4::operator *=(const Matrix4 &aRHS)
{
	if(mIdentity && !aRHS.mIdentity)
	{
		*this = aRHS;
	}
	else if(!mIdentity && !aRHS.mIdentity)
	{
		mComponents[0][0] = mComponents[0][0] * aRHS.mComponents[0][0] + mComponents[0][1] * aRHS.mComponents[1][0] + mComponents[0][2] * aRHS.mComponents[2][0] + mComponents[0][3] * aRHS.mComponents[3][0];
		mComponents[0][1] = mComponents[0][0] * aRHS.mComponents[0][1] + mComponents[0][1] * aRHS.mComponents[1][1] + mComponents[0][2] * aRHS.mComponents[2][1] + mComponents[0][3] * aRHS.mComponents[3][1];
		mComponents[0][2] = mComponents[0][0] * aRHS.mComponents[0][2] + mComponents[0][1] * aRHS.mComponents[1][2] + mComponents[0][2] * aRHS.mComponents[2][2] + mComponents[0][3] * aRHS.mComponents[3][2];
		mComponents[0][3] = mComponents[0][0] * aRHS.mComponents[0][3] + mComponents[0][1] * aRHS.mComponents[1][3] + mComponents[0][2] * aRHS.mComponents[2][3] + mComponents[0][3] * aRHS.mComponents[3][3];

		mComponents[1][0] = mComponents[1][0] * aRHS.mComponents[0][0] + mComponents[1][1] * aRHS.mComponents[1][0] + mComponents[1][2] * aRHS.mComponents[2][0] + mComponents[1][3] * aRHS.mComponents[3][0];
		mComponents[1][1] = mComponents[1][0] * aRHS.mComponents[0][1] + mComponents[1][1] * aRHS.mComponents[1][1] + mComponents[1][2] * aRHS.mComponents[2][1] + mComponents[1][3] * aRHS.mComponents[3][1];
		mComponents[1][2] = mComponents[1][0] * aRHS.mComponents[0][2] + mComponents[1][1] * aRHS.mComponents[1][2] + mComponents[1][2] * aRHS.mComponents[2][2] + mComponents[1][3] * aRHS.mComponents[3][2];
		mComponents[1][3] = mComponents[1][0] * aRHS.mComponents[0][3] + mComponents[1][1] * aRHS.mComponents[1][3] + mComponents[1][2] * aRHS.mComponents[2][3] + mComponents[1][3] * aRHS.mComponents[3][3];

		mComponents[2][0] = mComponents[2][0] * aRHS.mComponents[0][0] + mComponents[2][1] * aRHS.mComponents[1][0] + mComponents[2][2] * aRHS.mComponents[2][0] + mComponents[2][3] * aRHS.mComponents[3][0];
		mComponents[2][1] = mComponents[2][0] * aRHS.mComponents[0][1] + mComponents[2][1] * aRHS.mComponents[1][1] + mComponents[2][2] * aRHS.mComponents[2][1] + mComponents[2][3] * aRHS.mComponents[3][1];
		mComponents[2][2] = mComponents[2][0] * aRHS.mComponents[0][2] + mComponents[2][1] * aRHS.mComponents[1][2] + mComponents[2][2] * aRHS.mComponents[2][2] + mComponents[2][3] * aRHS.mComponents[3][2];
		mComponents[2][3] = mComponents[2][0] * aRHS.mComponents[0][3] + mComponents[2][1] * aRHS.mComponents[1][3] + mComponents[2][2] * aRHS.mComponents[2][3] + mComponents[2][3] * aRHS.mComponents[3][3];

		mComponents[3][0] = mComponents[3][0] * aRHS.mComponents[0][0] + mComponents[3][1] * aRHS.mComponents[1][0] + mComponents[3][2] * aRHS.mComponents[2][0] + mComponents[3][3] * aRHS.mComponents[3][0];
		mComponents[3][1] = mComponents[3][0] * aRHS.mComponents[0][1] + mComponents[3][1] * aRHS.mComponents[1][1] + mComponents[3][2] * aRHS.mComponents[2][1] + mComponents[3][3] * aRHS.mComponents[3][1];
		mComponents[3][2] = mComponents[3][0] * aRHS.mComponents[0][2] + mComponents[3][1] * aRHS.mComponents[1][2] + mComponents[3][2] * aRHS.mComponents[2][2] + mComponents[3][3] * aRHS.mComponents[3][2];
		mComponents[3][3] = mComponents[3][0] * aRHS.mComponents[0][3] + mComponents[3][1] * aRHS.mComponents[1][3] + mComponents[3][2] * aRHS.mComponents[2][3] + mComponents[3][3] * aRHS.mComponents[3][3];
	}

	return *this;
}

Matrix4& Matrix4::operator*=(float aRHS)
{
	for(int i = 0; i < 16; ++i)
	{
		_mComponents[i] *= aRHS;	
	}

	return *this;
}

Matrix4& Matrix4::operator/=(float aRHS)
{
	for(int i = 0; i < 16; ++i)
	{
		_mComponents[i] /= aRHS;	
	}

	return *this;
}
