#include "Math\Matrices\Matrix3.h"

#include "Math\Maths.h"
#include "Math\Vectors\Vector2.h"

//Initialise this Matrix3 as an identity matrix of one
Matrix3::Matrix3()
	: m_1x1(1.f), m_1x2(0.f), m_1x3(0.f),
	  m_2x1(0.f), m_2x2(1.f), m_2x3(0.f),
	  m_3x1(0.f), m_3x2(0.f), m_3x3(1.f) { }

//Initialise this Matrix3 as an identity matrix of the requested value
Matrix3::Matrix3(float a_Value)
	: m_1x1(a_Value), m_1x2(0.f), m_1x3(0.f),
	  m_2x1(0.f), m_2x2(a_Value), m_2x3(0.f),
	  m_3x1(0.f), m_3x2(0.f), m_3x3(a_Value) { }

//Initialise this Matrix3 by setting the value requested
Matrix3::Matrix3(float a_1x1, float a_1x2, float a_1x3,
				 float a_2x1, float a_2x2, float a_2x3,
				 float a_3x1, float a_3x2, float a_3x3)
	: m_1x1(a_1x1), m_1x2(a_1x2), m_1x3(a_1x3),
	  m_2x1(a_2x1), m_2x2(a_2x2), m_2x3(a_2x3),
	  m_3x1(a_3x1), m_3x2(a_3x2), m_3x3(a_3x3) { }

//Initialise the Matrix3 by copying the values of another
Matrix3::Matrix3(const Matrix3& a_Copy)
	: m_1x1(a_Copy.m_1x1), m_1x2(a_Copy.m_1x2), m_1x3(a_Copy.m_1x3),
	  m_2x1(a_Copy.m_2x1), m_2x2(a_Copy.m_2x2), m_2x3(a_Copy.m_2x3),
	  m_3x1(a_Copy.m_3x1), m_3x2(a_Copy.m_3x2), m_3x3(a_Copy.m_3x3) { }

//Adjugate this matrix
void Matrix3::Adjugate()
{
	//First convert the matrix into its confactor
	Confactor();

	//Transpose the confactor matrix
	Transpose();
}

//Convert this matrix into its confactor
void Matrix3::Confactor()
{
	//Cycle through the all values in this matrix
	for (int i = 0; i < 9; ++i)
	{
		//Assign this value accordingly
		if (i % 2 == 0)
			m_fMatrix[i] *= 1;
		else
			m_fMatrix[i] *= -1;
	}
}

//Inverse this matrix
void Matrix3::Inverse()
{
	//Get the determinant before inversing the matrix
	float idtm = 1 / Determinant();

	//Convert this matrix to a matrix of minors
	Minor();

	//Adjugate the matrix before mutliplying
	Adjugate();

	//Multiply the matrix by the determinant
	*this *= idtm;
}

//Convert this matrix into a true matrix of minors
void Matrix3::Minor()
{
	//Set the determinant of each submatrix ( matrix2 ) into this matrix
	*this = Matrix3(SubMatrixDeterminant(*this, 0, 0), SubMatrixDeterminant(*this, 0, 1), SubMatrixDeterminant(*this, 0, 2), 
					SubMatrixDeterminant(*this, 1, 0), SubMatrixDeterminant(*this, 1, 1), SubMatrixDeterminant(*this, 1, 2),
					SubMatrixDeterminant(*this, 2, 0), SubMatrixDeterminant(*this, 2, 1), SubMatrixDeterminant(*this, 2, 2));
}

//Transpose this matrix
void Matrix3::Transpose()
{
	//Convert the rows into columns
	*this = Matrix3(m_1x1, m_2x1, m_3x1,
					m_1x2, m_2x2, m_3x2,
					m_1x3, m_2x3, m_3x3);
}

//Calculate the determinant of this matrix
float Matrix3::Determinant() const
{
	return m_vMatrix[0][0] * SubMatrixDeterminant(*this, 0, 0) -
		   m_vMatrix[0][1] * SubMatrixDeterminant(*this, 0, 1) +
		   m_vMatrix[0][2] * SubMatrixDeterminant(*this, 0, 2);
}

//Get a X rotated version of this matrix
Matrix3 Matrix3::GetRotateX(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix3 rmat = *this;

	//Rotate the matrix
	rmat.RotateX(rad);

	//Return the rotated matrix
	return rmat;
}

//Get a Y rotated version of this matrix
Matrix3 Matrix3::GetRotateY(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix3 rmat = *this;

	//Rotate the matrix
	rmat.RotateY(rad);

	//Return the rotated matrix
	return rmat;
}

//Get a Z rotated version of this matrix
Matrix3 Matrix3::GetRotateZ(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix3 rmat = *this;

	//Rotate the matrix
	rmat.RotateZ(rad);

	//Return the rotated matrix
	return rmat;
}

//Get this matrixs X rotation in radians
float Matrix3::GetRotateX() const
{
	return atan2f(m_2x3, m_3x3);
}

//Get this matrixs Y rotation in radians
float Matrix3::GetRotateY() const
{
	return atan2f(-m_1x3, sqrtf(fpowf(m_2x3, 2) + fpowf(m_3x3, 2)));
}

//Get this matrixs Z rotation in radians
float Matrix3::GetRotateZ() const
{
	return atan2f(m_1x2, m_1x1);
}

//Get this matrixs scale as a vector 3
Vector3 Matrix3::GetScale() const
{
	//Create the vector to return
	Vector3 rvec;

	//Calculate each scale
	rvec.x = GetScaleX();
	rvec.y = GetScaleY();
	rvec.z = GetScaleZ();

	//Return the scale vector
	return rvec;
}

//Only get the scale of the X axis
float Matrix3::GetScaleX() const
{
	return sqrtf(fpowf(m_1x1, 2) + fpowf(m_1x2, 2));
}

//Only get the scale of the Y axis
float Matrix3::GetScaleY() const
{
	return sqrtf(fpowf(m_2x1, 2) + fpowf(m_2x2, 2));
}

//Only get the scale of the Z axis
float Matrix3::GetScaleZ() const
{
	return (m_3x1 + m_3x2 + m_3x3);
}

//Get the translation of this matrix
Vector3 Matrix3::GetTranslation() const
{
	return m_vMatrix[2];
}

//Only get the translation of the X axis
float Matrix3::GetTranslationX() const
{
	return m_3x1;
}

//Only get the translation of the Y axis
float Matrix3::GetTranslationY() const
{
	return m_3x2;
}

//Only get the translation of the Z axis
float Matrix3::GetTranslationZ() const
{
	return m_3x3;
}

//Rotate the x axis of this matrix
void Matrix3::RotateX(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_2x2 = cos(rad); m_3x2 = -sin(rad);
	m_2x3 = sin(rad); m_3x3 = cos(rad);
}

//Rotate the y axis of this matrix
void Matrix3::RotateY(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_1x1 = cos(rad);  m_3x1 = sin(rad);
	m_1x3 = -sin(rad); m_3x3 = cos(rad);
}

//Rotate the z axis of this matrix
void Matrix3::RotateZ(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_1x1 = cos(rad); m_2x1 = -sin(rad);
	m_1x2 = sin(rad); m_2x2 = cos(rad);
}

//Translate this matrix using two floats
void Matrix3::Translate(float a_X, float a_Y)
{
	//Increase the translation by the requested amount
	m_3x1 += a_X;
	m_3x2 += a_Y;
}

//Translate this matrix using a vector2
void Matrix3::Translate(Vector2& a_Point)
{
	//Increase the translation by the requested amount
	m_vMatrix[2] += (Vector3)a_Point;
}

//Find the determinant of a submatrix ( matrix2 ) in a matrix
float Matrix3::SubMatrixDeterminant(const Matrix3& a_m, unsigned int a_column, unsigned int a_row)
{
	unsigned int c1 = a_column > 0 ? 0 : 1;		//Set c1 to 0 if column is 1 or 2 ( else 1 )
	unsigned int c2 = a_column > 1 ? 1 : 2;		//Set c2 to 1 if column is 2 ( else 2 )

	unsigned int r1 = a_row > 0 ? 0 : 1;		//Set r1 to 0 if row is 1 or 2 ( else 1 )
	unsigned int r2 = a_row > 1 ? 1 : 2;		//Set r2 to 1 if row is 2 ( else 2 )

	//Calculate the determinant of these columns and rows
	return (a_m[c1][r1] * a_m[c2][r2]) -
		   (a_m[c1][r2] * a_m[c2][r1]);
}

//Find the dot product between a certain column and row of two matrices
float Matrix3::Dot(const Matrix3& a_m1, const Matrix3& a_m2, unsigned int a_m1_c, unsigned int a_m2_r)
{
	//Return the dot product between the column and row
	return a_m1[a_m1_c][0] * a_m2[0][a_m2_r] + 
		   a_m1[a_m1_c][1] * a_m2[1][a_m2_r] +
		   a_m1[a_m1_c][2] * a_m2[2][a_m2_r];
}

//Create an identity matrix using the given value
Matrix3 Matrix3::Identity(float a_Value)
{
	return Matrix3(a_Value);
}

//Equal operator
Matrix3& Matrix3::operator=(const Matrix3& rhs)
{
	m_1x1 = rhs.m_1x1; m_1x2 = rhs.m_1x2; m_1x3 = rhs.m_1x3;
	m_2x1 = rhs.m_2x1; m_2x2 = rhs.m_2x2; m_2x3 = rhs.m_2x3;
	m_3x1 = rhs.m_3x1; m_3x2 = rhs.m_3x2; m_3x3 = rhs.m_3x3;

	return *this;
}

//Multiplication operator
Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
	return Matrix3(Dot(rhs, *this, 0, 0), Dot(rhs, *this, 0, 1), Dot(rhs, *this, 0, 2),
				   Dot(rhs, *this, 1, 0), Dot(rhs, *this, 1, 1), Dot(rhs, *this, 1, 2),
				   Dot(rhs, *this, 2, 0), Dot(rhs, *this, 2, 1), Dot(rhs, *this, 2, 2));
}

//Float multiplication operator
Matrix3 Matrix3::operator*(const float rhs)
{
	return Matrix3(m_1x1 * rhs, m_1x2 * rhs, m_1x3 * rhs,
				   m_2x1 * rhs, m_2x2 * rhs, m_2x3 * rhs,
				   m_3x1 * rhs, m_3x2 * rhs, m_3x3 * rhs);
}

//Compound multiplication operator
Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Matrix3& Matrix3::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Vector3 multiplication operator
Vector3 Matrix3::operator*(const Vector3& rhs)
{
	return Vector3(m_1x1 * rhs.x + m_2x1 * rhs.y + m_3x1 * rhs.z,
				   m_1x2 * rhs.x + m_2x2 * rhs.y + m_3x2 * rhs.z,
				   m_1x3 * rhs.x + m_2x3 * rhs.y + m_3x3 * rhs.z);
}

//Float operator
void Matrix3::operator()(float a_1x1, float a_1x2, float a_1x3,
						 float a_2x1, float a_2x2, float a_2x3,
						 float a_3x1, float a_3x2, float a_3x3)
{
	m_1x1 = a_1x1; m_1x2 = a_1x2; m_1x3 = a_1x3;
	m_2x1 = a_2x1; m_2x2 = a_2x2; m_2x3 = a_2x3;
	m_3x1 = a_3x1; m_3x2 = a_3x2; m_3x3 = a_3x3;
}

//Matrix3 operator
void Matrix3::operator()(const Matrix3& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Matrix3::operator float*()
{
	return &m_fMatrix[0];
}

//Array operator
Vector3& Matrix3::operator[](int idx)
{
	return m_vMatrix[idx];
}

//Const array operator
const Vector3& Matrix3::operator[](int idx) const
{
	return m_vMatrix[idx];
}