#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Vector3.h"

class Matrix4
{
public:

	Matrix4();
	Matrix4(float a11, float a12, float a13, float a14,
			float a21, float a22, float a23, float a24,
			float a31, float a32, float a33, float a34,
			float a41, float a42, float a43, float a44);
	Matrix4(const Matrix4 &aRHS);

	float* operator[](int aRow);
	const float* const operator[](int aRow) const;
	operator const float*() const;
	operator float*();
	void operator=(const Matrix4 &aRHS);

	Matrix4 ToOpenGLMatrix() const;

	Matrix4 GetTranspose() const;
	Matrix4 GetInverse() const;

	Matrix4 Concatenate(const Matrix4 &aMatrix) const;
	
	void SetTranslationData(const Vector3 &aVector);
	Vector3 GetTranslationData() const;

	void MakeIdentity();
	void MakeTranslationMatrix(const Vector3 &aVec);
	void MakeTranslationMatrix(float aX, float aY, float aZ);
	
	void SetScale(const Vector3 &aVec);

	void RotateAroundXRad(float aRadian);
	void RotateAroundXDeg(float aDeg);

	void RotateAroundYRad(float aRadian);
	void RotateAroundYDeg(float aDeg);

	void RotateAroundZRad(float aRadian);
	void RotateAroundZDeg(float aDeg);

	static Matrix4 GenerateOrthogonalBaseFromAxis(const Vector3 &aAxis);

	static Matrix4 GenerateCoordinatesChangeMatrix
		(	const Vector3& aInitialAxis1,
			const Vector3& aInitialAxis2,
			const Vector3& aInitialAxis3,
			const Vector3& aInitialOrigin,
			const Vector3& aResultingAxis1,
			const Vector3& aResultingAxis2,
			const Vector3& aResultingAxis3,
			const Vector3& aResultingOrigin
			);

	Matrix4 operator+(const Matrix4 &aRHS) const;
	Matrix4 operator-(const Matrix4 &aRHS) const;
	Matrix4 operator-() const;
	Matrix4 operator*(const Matrix4 &aRHS) const;
	Matrix4 operator*(float aRHS) const;
	Vector3 operator*(const Vector3 &aRHS) const;
	Matrix4 operator/(float aRHS) const;

	Matrix4& operator+=(const Matrix4 &aRHS);
	Matrix4& operator-=(const Matrix4 &aRHS);
	Matrix4& operator*=(const Matrix4 &aRHS);
	Matrix4& operator*=(float aRHS);
	Matrix4& operator/=(float aRHS);

	bool operator==(const Matrix4 &aRHS);
	bool operator!=(const Matrix4 &aRHS);

protected:

	union
	{
		float mComponents[4][4];
		float _mComponents[16];
		struct 
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
	};

	bool mIdentity;
};

Matrix4 operator*(float aLHS, const Matrix4 &aRHS);

inline Matrix4 Matrix4::ToOpenGLMatrix() const
{
	return GetTranspose();
}

inline Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(	m11, m21, m31, m41,
					m12, m22, m32, m42,
					m13, m23, m33, m43,
					m14, m24, m34, m44);
}

inline Matrix4::operator const float*() const
{
	return _mComponents;
}

inline Matrix4::operator float*()
{
	return _mComponents;
}

inline float* Matrix4::operator[](int aRow)
{
	assert(aRow >= 0 && aRow < 4);
	return mComponents[aRow];
}

inline const float* const Matrix4::operator[](int aRow) const
{
	assert(aRow >= 0 && aRow < 4);
	return mComponents[aRow];
}

inline Matrix4 Matrix4::operator+(const Matrix4 &aRHS) const
{
	return Matrix4(	m11 + aRHS.m11, m12 + aRHS.m12, m13 + aRHS.m13, m14 + aRHS.m14,
					m21 + aRHS.m21, m22 + aRHS.m22, m23 + aRHS.m23, m24 + aRHS.m24,
					m31 + aRHS.m31, m32 + aRHS.m32, m33 + aRHS.m33, m34 + aRHS.m34,
					m41 + aRHS.m41, m42 + aRHS.m42, m43 + aRHS.m43, m44 + aRHS.m44);
}

inline Matrix4 Matrix4::operator-(const Matrix4 &aRHS) const
{
	return Matrix4(	m11 - aRHS.m11, m12 - aRHS.m12, m13 - aRHS.m13, m14 - aRHS.m14,
					m21 - aRHS.m21, m22 - aRHS.m22, m23 - aRHS.m23, m24 - aRHS.m24,
					m31 - aRHS.m31, m32 - aRHS.m32, m33 - aRHS.m33, m34 - aRHS.m34,
					m41 - aRHS.m41, m42 - aRHS.m42, m43 - aRHS.m43, m44 - aRHS.m44);
}

inline Matrix4 Matrix4::operator-() const
{
	return Matrix4(	-m11, -m12, -m13, -m14,
					-m21, -m22, -m23, -m24,
					-m31, -m32, -m33, -m34,
					-m41, -m42, -m43, -m44);
}

inline Matrix4 Matrix4::operator*(float aRHS) const
{
	return Matrix4( m11 * aRHS, m12 * aRHS, m13 * aRHS, m14 * aRHS,
					m21 * aRHS, m22 * aRHS, m23 * aRHS, m24 * aRHS,
					m31 * aRHS, m32 * aRHS, m33 * aRHS, m34 * aRHS,
					m41 * aRHS, m42 * aRHS, m43 * aRHS, m44 * aRHS);
}

inline Matrix4 Matrix4::operator/(float aRHS) const
{
	assert(aRHS != 0.0);
	return Matrix4( m11 / aRHS, m12 / aRHS, m13 / aRHS, m14 / aRHS,
					m21 / aRHS, m22 / aRHS, m23 / aRHS, m24 / aRHS,
					m31 / aRHS, m32 / aRHS, m33 / aRHS, m34 / aRHS,
					m41 / aRHS, m42 / aRHS, m43 / aRHS, m44 / aRHS);
}

inline Matrix4 operator*(float aLHS, const Matrix4 &aRHS)
{
	return aRHS * aLHS;
}

#endif //MATRIX4_H_
