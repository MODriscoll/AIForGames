#pragma once

#include "Math\Vectors\Vector2.h"

class Matrix2
{
public:

	// ----- VARIABLES ----- \\

	union
	{
		// Each individual variable struct
		struct { float
				 m_1x1, m_1x2,
				 m_2x1, m_2x2;
			   };

		// Two dimensional array struct
		struct { float   m_dMatrix[2][2]; };

		// Flat ( one dimension ) array struct
		struct { float	 m_fMatrix[4]; };

		// Vector2 array struct
		struct { Vector2 m_vMatrix[2]; };
	};


	// ----- INITIALISER ----- \\

	Matrix2();
	Matrix2(float a_Value);
	Matrix2(float a_1x1, float a_1x2, 
			float a_2x1, float a_2x2);
	Matrix2(const Matrix2& a_Copy);

	~Matrix2() = default;


	// ----- CALCULATIONS ----- \\

	void	Adjugate();					// Adjugate this matrix
	void	Confactor();				// Confact this matrix
	void	Inverse();					// Inverse this matrix
	void	Transpose();				// Transpose this matrix

	float	Determinant() const;		// Get the determinant of this matrix


	// ----- FUNCTIONS ----- \\

	Matrix2 GetRotate(float rad) const;		// Get a rotated version of this matrix
	float	GetRotate() const;				// Returns the radians of thix matrixs rotation

	void	Rotate(float rad);				// Rotate this matrix

	// ----- STATIC FUNCTIONS ----- \\

	static float	Dot(const Matrix2& a_m1, const Matrix2& a_m2, unsigned int a_m1_c, unsigned int a_m2_r);
	static Matrix2	Identity(float a_Value = 1.f);


	// ----- OPERATORS ----- \\

	
	Matrix2& operator = (const Matrix2& rhs);

	Matrix2 operator * (const Matrix2& rhs);
	Matrix2 operator * (const float rhs);

	Matrix2& operator *= (const Matrix2& rhs);
	Matrix2& operator *= (const float rhs);

	Vector2 operator * (const Vector2& rhs);

	void operator() (float a_1x1, float a_1x2,
					 float a_2x1, float a_2x2);
	void operator() (const Matrix2& rhs);

	explicit operator float*();

	Vector2& operator[] (int idx);
	const Vector2& operator[] (int idx) const;
};