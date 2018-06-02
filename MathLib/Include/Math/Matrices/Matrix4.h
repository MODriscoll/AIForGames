#pragma once

#include "Math\Vectors\Vector4.h"

class Matrix4
{
public:

	// ----- VARIABLES ----- \\

	union
	{
		// Each individual variable struct
		struct { float
				 m_1x1, m_1x2, m_1x3, m_1x4,
				 m_2x1, m_2x2, m_2x3, m_2x4,
				 m_3x1, m_3x2, m_3x3, m_3x4,
				 m_4x1, m_4x2, m_4x3, m_4x4;
		};

		// Two dimensional array struct
		struct { float   m_dMatrix[4][4]; };

		// Flat ( one dimension ) array struct
		struct { float	 m_fMatrix[16]; };

		// Vector4 array struct
		struct { Vector4 m_vMatrix[4]; };
	};


	// ----- INITIALISER ----- \\

	Matrix4();
	Matrix4(float a_Value);
	Matrix4(float a_1x1, float a_1x2, float a_1x3, float a_1x4,
			float a_2x1, float a_2x2, float a_2x3, float a_2x4,
			float a_3x1, float a_3x2, float a_3x3, float a_3x4,
			float a_4x1, float a_4x2, float a_4x3, float a_4x4);
	Matrix4(const Matrix4& a_Copy);

	~Matrix4() = default;


	// ----- CALCULATIONS ----- \\

	void	Adjugate();					// Adjugate this matrix
	void	Confactor();				// Confact this matrix
	void	Inverse();					// Inverse this matrix
	void	Minor();					// Convert this matrix into a true minor
	void	Transpose();				// Transpose this matrix

	float	Determinant() const;		// Get the determinant

	// ----- FUNCTIONS ----- \\

	Matrix4 GetRotateX(float rad) const;					// Get a X rotated version of this matrix
	Matrix4 GetRotateY(float rad) const;					// Get a Y rotated version of this matrix
	Matrix4 GetRotateZ(float rad) const;					// Get a Z rotated version of this matrix

	void	RotateX(float rad);								// Rotate this matrix around the X axis	
	void	RotateY(float rad);								// Rotate this matrix around the Y axis
	void	RotateZ(float rad);								// Rotate this matrix around the Z axis

	void	Translate(float a_X, float a_Y, float a_Z);		// Translate this matrix using two floats
	void	Translate(Vector3& a_Point);					// Translate this matrix using a vector3


	// ----- STATIC FUNCTIONS ----- \\

	static float	SubMatrixDeterminant(const Matrix4& a_m, unsigned int a_column, unsigned int a_row);
	static float	Dot(const Matrix4& a_m1, const Matrix4& a_m2, unsigned int a_m1_c, unsigned int a_m2_r);
	static Matrix4	Identity(float a_Value = 1.f);


	// ----- OPERATORS ----- \\


	Matrix4& operator = (const Matrix4& rhs);

	Matrix4 operator * (const Matrix4& rhs);
	Matrix4 operator * (const float rhs);

	Matrix4& operator *= (const Matrix4& rhs);
	Matrix4& operator *= (const float rhs);

	Vector4 operator * (const Vector4& rhs);

	void operator() (float a_1x1, float a_1x2, float a_1x3, float a_1x4,
					 float a_2x1, float a_2x2, float a_2x3, float a_2x4,
					 float a_3x1, float a_3x2, float a_3x3, float a_3x4,
					 float a_4x1, float a_4x2, float a_4x3, float a_4x4);
	void operator() (const Matrix4& rhs);

	explicit operator float*();

	Vector4& operator[] (int idx);
	const Vector4& operator[] (int idx) const;
};