#pragma once

#include "Math\Vectors\Vector3.h"

#include "RotationMatrices\RMatrix3.h"
#include "ScalingMatrices\SMatrix3.h"
#include "TranslationMatrices\TMatrix3.h"

class Matrix3
{
public:

	// ----- VARIABLES ----- \\

	union
	{
		// Each individual variable struct
		struct { float
				 m_1x1, m_1x2, m_1x3,
				 m_2x1, m_2x2, m_2x3,
				 m_3x1, m_3x2, m_3x3;
			   };

		// Two dimensional array struct
		struct { float   m_dMatrix[3][3]; };

		// Flat ( one dimension ) array struct
		struct { float	 m_fMatrix[9]; };

		// Vector3 array struct
		struct { Vector3 m_vMatrix[3]; };
	};


	// ----- INITIALISER ----- \\

	Matrix3();
	Matrix3(float a_Value);
	Matrix3(float a_1x1, float a_1x2, float a_1x3,
			float a_2x1, float a_2x2, float a_2x3,
			float a_3x1, float a_3x2, float a_3x3);	
	Matrix3(const Matrix3& a_Copy);

	~Matrix3() = default;


	// ----- CALCULATIONS ----- \\

	void	Adjugate();					// Adjugate this matrix
	void	Confactor();				// Confact this matrix
	void	Inverse();					// Inverse this matrix
	void	Minor();					// Convert this matrix into a true minor
	void	Transpose();				// Transpose this matrix

	float	Determinant() const;		// Get the determinant of this matrix


	// ----- FUNCTIONS ----- \\

	Matrix3 GetRotateX(float rad) const;		// Get a X rotated version of this matrix
	Matrix3 GetRotateY(float rad) const;		// Get a Y rotated version of this matrix
	Matrix3 GetRotateZ(float rad) const;		// Get a Z rotated version of this matrix

	float	GetRotateX() const;					// Returns the radians of this matrixs X rotation
	float	GetRotateY() const;					// Returns the radians of this matrixs Y rotation
	float	GetRotateZ() const;					// Returns the radians of thix matrixs Z rotation

	Vector3	GetScale() const;					// Returns a vector containing this matrixs scales
	
	float	GetScaleX() const;					// Returns the scale of this matrixs X axis
	float	GetScaleY() const;					// Returns the scale of this matrixs Y axis
	float	GetScaleZ() const;					// Returns the scale of this matrixs Z axis

	Vector3 GetTranslation() const;				// Returns a vector containing this matrixs translation

	float	GetTranslationX() const;			// Returns the translation of this matrixs X axis
	float	GetTranslationY() const;			// Returns the translation of this matrixs Y axis
	float	GetTranslationZ() const;			// Returns the translation of this matrixs Z axis

	

	void	RotateX(float rad);					// Rotate this matrix around the X axis	
	void	RotateY(float rad);					// Rotate this matrix around the Y axis
	void	RotateZ(float rad);					// Rotate this matrix around the Z axis

	void	Translate(float a_X, float a_Y);	// Translate this matrix using two floats
	void	Translate(Vector2& a_Point);		// Translate this matrix using a vector2

	// ----- STATIC FUNCTIONS ----- \\

	static float	SubMatrixDeterminant(const Matrix3& a_m, unsigned int a_column, unsigned int a_row);
	static float	Dot(const Matrix3& a_m1, const Matrix3& a_m2, unsigned int a_m1_c, unsigned int a_m2_r);
	static Matrix3	Identity(float a_Value = 1.f);


	// ----- OPERATORS ----- \\


	Matrix3& operator = (const Matrix3& rhs);

	Matrix3 operator * (const Matrix3& rhs);
	Matrix3 operator * (const float rhs);

	Matrix3& operator *= (const Matrix3& rhs);
	Matrix3& operator *= (const float rhs);

	Vector3 operator * (const Vector3& rhs);

	void operator() (float a_1x1, float a_1x2, float a_1x3,
					 float a_2x1, float a_2x2, float a_2x3,
					 float a_3x1, float a_3x2, float a_3x3);
	void operator() (const Matrix3& rhs);

	explicit operator float*();

	Vector3& operator[] (int idx);
	const Vector3& operator[] (int idx) const;
};

static Matrix3 operator * (const Matrix3& lhs, const Matrix3& rhs) { return lhs * rhs; }