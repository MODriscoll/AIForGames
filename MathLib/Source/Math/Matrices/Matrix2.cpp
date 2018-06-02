#include "Math\Matrices\Matrix2.h"

#include "Math\Maths.h"

//Initialise this Matrix2 as an identity matrix of one
Matrix2::Matrix2()
	: m_1x1(1.f), m_1x2(0.f),
	  m_2x1(0.f), m_2x2(1.f) { }

//Initialise this Matrix2 as an identity matrix of the requested value
Matrix2::Matrix2(float a_Value)
	: m_1x1(a_Value), m_1x2(0.f),
	  m_2x1(0.f), m_2x2(a_Value) { }

//Initialise this Matrix2 by setting the values requested
Matrix2::Matrix2(float a_1x1, float a_1x2,
				 float a_2x1, float a_2x2)
	: m_1x1(a_1x1), m_1x2(a_1x2),
	  m_2x1(a_2x1), m_2x2(a_2x2) { }

//Initialise the Matrix2 by copying the values of another
Matrix2::Matrix2(const Matrix2& a_Copy)
	: m_1x1(a_Copy.m_1x1), m_1x2(a_Copy.m_1x2),
	  m_2x1(a_Copy.m_2x1), m_2x2(a_Copy.m_2x2) { }

//Adjugate this matrix
void Matrix2::Adjugate()
{
	//First convert the matrix into its confactor
	Confactor();

	//Transpose the confactor matrix
	Transpose();
}

//Convert this matrix into its confactor
void Matrix2::Confactor()
{
	//Cycle through the all values in this matrix
	for (int i = 0; i < 4; ++i)
	{
		//Assign this value accordingly
		if (i % 2 == 0)
			m_fMatrix[i] *= 1;
		else
			m_fMatrix[i] *= -1;
	}
}

//Inverse this matrix
void Matrix2::Inverse()
{
	//Get the determinant before inversing the matrix
	float idtm = 1 / Determinant();

	//Inverse the matrix
	*this = Matrix2(m_dMatrix[1][1], -m_dMatrix[0][1], -m_dMatrix[1][0], m_dMatrix[0][0]);

	//Multiply the matrix by the determinant
	*this *= idtm;
}

//Transpose this matrix
void Matrix2::Transpose()
{
	//Convert the columns into rows
	*this = Matrix2(m_1x1, m_2x1,
					m_1x2, m_2x2);
}

//Calculate the determinant of this matrix
float Matrix2::Determinant() const
{
	return (m_vMatrix[0][0] * m_vMatrix[1][1]) -
		   (m_vMatrix[0][1] * m_vMatrix[1][0]);
}

//Get a rotated version of this matrix
Matrix2 Matrix2::GetRotate(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix2 rmat = *this;

	//Rotate the matrix
	rmat.Rotate(rad);

	//Return the rotated matrix
	return rmat;
}

// Get this matrixs rotation in radians
float Matrix2::GetRotate() const
{
	return atan2f(m_1x1, m_1x2);
}

//Rotate this matrix
void Matrix2::Rotate(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_vMatrix[0][0] = cos(rad); m_vMatrix[1][0] = -sin(rad);
	m_vMatrix[0][1] = sin(rad); m_vMatrix[1][1] = cos(rad);
}

//Find the dot product between a certain column and row of two matrices
float Matrix2::Dot(const Matrix2& a_m1, const Matrix2& a_m2, unsigned int a_m1_c, unsigned int a_m2_r)
{
	//Return the dot product between the column and row
	return a_m1[a_m1_c][0] * a_m2[0][a_m2_r] + 
		   a_m1[a_m1_c][1] * a_m2[1][a_m2_r];
}

//Create an identity matrix using the given value
Matrix2 Matrix2::Identity(float a_Value)
{
	return Matrix2(a_Value);
}

//Equal operator
Matrix2& Matrix2::operator=(const Matrix2& rhs)
{
	m_1x1 = rhs.m_1x1; m_1x2 = rhs.m_1x2;
	m_2x1 = rhs.m_2x1; m_2x2 = rhs.m_2x2;

	return *this;
}

//Multiplication operator
Matrix2 Matrix2::operator*(const Matrix2& rhs)
{
	return Matrix2(Dot(rhs, *this, 0, 0), Dot(rhs, *this, 0, 1),
				   Dot(rhs, *this, 1, 0), Dot(rhs, *this, 1, 1));
}

//Float multiplication operator
Matrix2 Matrix2::operator*(const float rhs)
{
	return Matrix2(m_1x1 * rhs, m_1x2 * rhs,
				   m_2x1 * rhs, m_2x2 * rhs);
}

//Compound multiplication operator
Matrix2& Matrix2::operator*=(const Matrix2& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Matrix2& Matrix2::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Vector2 multiplication operator
Vector2 Matrix2::operator*(const Vector2& rhs)
{
	return Vector2(m_1x1 * rhs.x + m_2x1 * rhs.y,
				   m_1x2 * rhs.x + m_2x2 * rhs.y);
}

//Float operator
void Matrix2::operator()(float a_1x1, float a_1x2,
						 float a_2x1, float a_2x2)
{
	m_1x1 = a_1x1; m_1x2 = a_1x2;
	m_2x1 = a_2x1; m_2x2 = a_2x2;
}

//Matrix2 operator
void Matrix2::operator()(const Matrix2& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Matrix2::operator float*()
{
	return &m_fMatrix[0];
}

//Array operator
Vector2& Matrix2::operator[](int idx)
{
	return m_vMatrix[idx];
}

//Const array operator
const Vector2& Matrix2::operator[](int idx) const
{
	return m_vMatrix[idx];
}