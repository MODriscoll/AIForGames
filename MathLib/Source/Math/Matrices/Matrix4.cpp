#include "Math\Matrices\Matrix4.h"

#include "Math\Maths.h"
#include "Math\Vectors\Vector3.h"

//Initialise this Matrix4 as an identity matrix of one
Matrix4::Matrix4()
	: m_1x1(1.f), m_1x2(0.f), m_1x3(0.f), m_1x4(0.f), 
	  m_2x1(0.f), m_2x2(1.f), m_2x3(0.f), m_2x4(0.f), 
	  m_3x1(0.f), m_3x2(0.f), m_3x3(1.f), m_3x4(0.f), 
	  m_4x1(0.f), m_4x2(0.f), m_4x3(0.f), m_4x4(1.f) { }

//Initialise this Matrix4 as an identity matrix of the requested value
Matrix4::Matrix4(float a_Value)
	: m_1x1(a_Value), m_1x2(0.f), m_1x3(0.f), m_1x4(0.f),
	  m_2x1(0.f), m_2x2(a_Value), m_2x3(0.f), m_2x4(0.f),
	  m_3x1(0.f), m_3x2(0.f), m_3x3(a_Value), m_3x4(0.f),
	  m_4x1(0.f), m_4x2(0.f), m_4x3(0.f), m_4x4(a_Value) { }

//Initialise this Matrix4 by setting the value requested
Matrix4::Matrix4(float a_1x1, float a_1x2, float a_1x3, float a_1x4,
				 float a_2x1, float a_2x2, float a_2x3, float a_2x4,
				 float a_3x1, float a_3x2, float a_3x3, float a_3x4,
				 float a_4x1, float a_4x2, float a_4x3, float a_4x4)
	: m_1x1(a_1x1), m_1x2(a_1x2), m_1x3(a_1x3), m_1x4(a_1x4),
	  m_2x1(a_2x1), m_2x2(a_2x2), m_2x3(a_2x3), m_2x4(a_2x4),
	  m_3x1(a_3x1), m_3x2(a_3x2), m_3x3(a_3x3), m_3x4(a_3x4),
	  m_4x1(a_4x1), m_4x2(a_4x2), m_4x3(a_4x3), m_4x4(a_4x4) { }

//Initialise the Matrix4 by copying the values of another
Matrix4::Matrix4(const Matrix4& a_Copy)
	: m_1x1(a_Copy.m_1x1), m_1x2(a_Copy.m_1x2), m_1x3(a_Copy.m_1x3), m_1x4(a_Copy.m_1x4),
	  m_2x1(a_Copy.m_2x1), m_2x2(a_Copy.m_2x2), m_2x3(a_Copy.m_2x3), m_2x4(a_Copy.m_2x4),
	  m_3x1(a_Copy.m_3x1), m_3x2(a_Copy.m_3x2), m_3x3(a_Copy.m_3x3), m_3x4(a_Copy.m_3x4), 
	  m_4x1(a_Copy.m_4x1), m_4x2(a_Copy.m_4x2), m_4x3(a_Copy.m_4x3), m_4x4(a_Copy.m_4x4) { }

//Adjugate this matrix
void Matrix4::Adjugate()
{
	//First convert the matrix into its confactor
	Confactor();

	//Transpose the confactor matrix
	Transpose();
}

//Convert this matrix into its confactor
void Matrix4::Confactor()
{
	//Cycle through the all values in this matrix
	for (int i = 0; i < 16; ++i)
	{
		//Assign this value accordingly
		if (i % 2 == 0)
			m_fMatrix[i] *= 1;
		else
			m_fMatrix[i] *= -1;
	}
}

//Inverse this matrix
void Matrix4::Inverse()
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
void Matrix4::Minor()
{
	//Set the determinant of each submatrix ( matrix3 ) into this matrix
	/**this = Matrix4((m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 2, 3) - m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 1, 3) + m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 1, 2)),
				    (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 2, 3) - m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 0, 3) + m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 0, 2)),
				    (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 1, 3) - m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 0, 3) + m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 0, 1)),
				    (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 1, 2) - m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 0, 2) + m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 0, 1)),

					(m_dMatrix[0][1] * dtmn2f(m_dMatrix, 2, 3, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 2, 3, 1, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 2, 3, 1, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 2, 3, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 2, 3, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 2, 3, 0, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 2, 3, 1, 3) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 2, 3, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 2, 3, 0, 1)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 2, 3, 1, 2) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 2, 3, 0, 2) + m_dMatrix[0][2] * dtmn2f(m_dMatrix, 2, 3, 0, 1)),

					(m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 3, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 3, 1, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 3, 1, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 3, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 3, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 3, 0, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 3, 1, 3) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 3, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 3, 0, 1)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 3, 1, 2) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 3, 0, 2) + m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 3, 0, 1)),

					(m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 2, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 2, 1, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 2, 1, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 2, 2, 3) - m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 2, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 2, 0, 2)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 2, 1, 3) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 2, 0, 3) + m_dMatrix[0][3] * dtmn2f(m_dMatrix, 1, 2, 0, 1)),
					(m_dMatrix[0][0] * dtmn2f(m_dMatrix, 1, 2, 1, 2) - m_dMatrix[0][1] * dtmn2f(m_dMatrix, 1, 2, 0, 2) + m_dMatrix[0][2] * dtmn2f(m_dMatrix, 1, 2, 0, 1)));*/

	*this = Matrix4(SubMatrixDeterminant(*this, 0, 0), SubMatrixDeterminant(*this, 0, 1), SubMatrixDeterminant(*this, 0, 2), SubMatrixDeterminant(*this, 0, 3),
					SubMatrixDeterminant(*this, 1, 0), SubMatrixDeterminant(*this, 1, 1), SubMatrixDeterminant(*this, 1, 2), SubMatrixDeterminant(*this, 1, 3),
					SubMatrixDeterminant(*this, 2, 0), SubMatrixDeterminant(*this, 2, 1), SubMatrixDeterminant(*this, 2, 2), SubMatrixDeterminant(*this, 2, 3),
					SubMatrixDeterminant(*this, 3, 0), SubMatrixDeterminant(*this, 3, 1), SubMatrixDeterminant(*this, 3, 2), SubMatrixDeterminant(*this, 3, 3));
}

//Transpose this matrix
void Matrix4::Transpose()
{
	//Convert the rows into columns
	*this = Matrix4(m_1x1, m_2x1, m_3x1, m_4x1,
					m_1x2, m_2x2, m_3x2, m_4x2,
					m_1x3, m_2x3, m_3x3, m_4x3,
					m_1x4, m_2x4, m_3x4, m_4x4);
}

//Calculate the determinant of this matrix
float Matrix4::Determinant() const
{
	/*return m_dMatrix[0][0] * (m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 2, 3) -
						      m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 1, 3) +
						      m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 1, 2)) -

		   m_dMatrix[0][1] * (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 2, 3) -
						      m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 0, 3) +
						      m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 0, 2)) +

		   m_dMatrix[0][2] * (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 1, 3) -
						      m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 0, 3) +
						      m_dMatrix[1][3] * dtmn2f(m_dMatrix, 2, 3, 0, 1)) -

		   m_dMatrix[0][3] * (m_dMatrix[1][0] * dtmn2f(m_dMatrix, 2, 3, 1, 2) -
						      m_dMatrix[1][1] * dtmn2f(m_dMatrix, 2, 3, 0, 2) +
						      m_dMatrix[1][2] * dtmn2f(m_dMatrix, 2, 3, 0, 1));*/

	return m_vMatrix[0][0] * SubMatrixDeterminant(*this, 0, 0) - 
		   m_vMatrix[0][1] * SubMatrixDeterminant(*this, 0, 1) +
		   m_vMatrix[0][2] * SubMatrixDeterminant(*this, 0, 2) -
		   m_vMatrix[0][3] * SubMatrixDeterminant(*this, 0, 3);
}

//Get a X rotated version of this matrix
Matrix4 Matrix4::GetRotateX(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix4 rmat = *this;

	//Rotate the matrix
	rmat.RotateX(rad);

	//Return the rotated matrix
	return rmat;
}

//Get a Y rotated version of this matrix
Matrix4 Matrix4::GetRotateY(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix4 rmat = *this;

	//Rotate the matrix
	rmat.RotateY(rad);

	//Return the rotated matrix
	return rmat;
}

//Get a Z rotated version of this matrix
Matrix4 Matrix4::GetRotateZ(float rad) const
{
	//Create the matrix to return and set it as this matrix
	Matrix4 rmat = *this;

	//Rotate the matrix
	rmat.RotateZ(rad);

	//Return the rotated matrix
	return rmat;
}

//Rotate the x axis of this matrix
void Matrix4::RotateX(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_vMatrix[1][1] = cos(rad);	m_vMatrix[2][1] = -sin(rad);
	m_vMatrix[1][2] = sin(rad); m_vMatrix[2][2] = cos(rad);
}

//Rotate the y axis of this matrix
void Matrix4::RotateY(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_vMatrix[0][0] = cos(rad);  m_vMatrix[2][0] = sin(rad);
	m_vMatrix[0][2] = -sin(rad); m_vMatrix[2][2] = cos(rad);
}

//Rotate the z axis of this matrix
void Matrix4::RotateZ(float rad)
{
	//Caluclate the rotation of this matrix using sin and cos
	m_vMatrix[0][0] = cos(rad); m_vMatrix[1][0] = -sin(rad);
	m_vMatrix[0][1] = sin(rad); m_vMatrix[1][1] = cos(rad);
}

//Translate this matrix using three floats
void Matrix4::Translate(float a_X, float a_Y, float a_Z)
{
	//Increase the translation by the requested amount
	m_vMatrix[3][0] += a_X;
	m_vMatrix[3][1] += a_Y;
	m_vMatrix[3][2] += a_Z;
}

//Translate this matrix using a vector3
void Matrix4::Translate(Vector3& a_Point)
{
	//Increase the translation by the requested amount
	m_vMatrix[3][0] += a_Point.x;
	m_vMatrix[3][1] += a_Point.y;
	m_vMatrix[3][2] += a_Point.z;
}

//Find the determinant of a submatrix ( matrix3 ) in a matrix
float Matrix4::SubMatrixDeterminant(const Matrix4& a_m, unsigned int a_column, unsigned int a_row)
{
	unsigned int c = a_column > 0 ? 0 : 1;		//Set c to 0 if column is greater than 0 ( else 1 )

	unsigned int r1 = a_row > 0 ? 0 : 1;		//Set r1 to 0 if row is greater than 0 ( else 1 )
	unsigned int r2 = a_row > 1 ? 1 : 2;		//Set r2 to 1 if row is greater than 1 ( else 2 )
	unsigned int r3 = a_row > 2 ? 2 : 3;		//Set r3 to 2 if row is greater than 2 ( else 3 )

	unsigned int sc1 = a_column > 1 ? 1 : 2;	//Set sc1 to 1 if column is greater than 1 ( else 2 )
	unsigned int sc2 = a_column > 2 ? 2 : 3;	//Set sc2 to 2 if column is greater than 2 ( else 3 )

	unsigned int sr1 = a_row < 2 ? 2 : 1;		//Set sr1 to 2 if row is less than 2 ( else 1 )
	unsigned int sr2 = a_row < 3 ? 3 : 2;		//Set sr2 to 3 if row is less than 3 ( else 2 )
	unsigned int sr3 = a_row < 1 ? 1 : 0;		//Set sr3 to 1 if row is less than 1 ( else 0 )

	//Calculate the determinant of these columns and rows
	return (a_m[c][r1] * ((a_m[sc1][sr1] * a_m[sc2][sr2]) - (a_m[sc1][sr2] * a_m[sc2][sc1]))) -
		   (a_m[c][r2] * ((a_m[sc1][sr3] * a_m[sc2][sr2]) - (a_m[sc1][sr2] * a_m[sc2][sr3]))) +
		   (a_m[c][r3] * ((a_m[sc1][sr3] * a_m[sc2][sr1]) - (a_m[sc1][sr1] * a_m[sc2][sr3])));
}

//Find the dot product between a certain column and row of two matrices
float Matrix4::Dot(const Matrix4& a_m1, const Matrix4& a_m2, unsigned int a_m1_c, unsigned int a_m2_r)
{
	//Return the dot product between the column and row
	return a_m1[a_m1_c][0] * a_m2[0][a_m2_r] +
		   a_m1[a_m1_c][1] * a_m2[1][a_m2_r] +
		   a_m1[a_m1_c][2] * a_m2[2][a_m2_r] +
		   a_m1[a_m1_c][3] * a_m2[3][a_m2_r];
}

//Create an identity matrix using the given value
Matrix4 Matrix4::Identity(float a_Value)
{
	return Matrix4(a_Value);
}

//Equal operator
Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
	m_1x1 = rhs.m_1x1; m_1x2 = rhs.m_1x2; m_1x3 = rhs.m_1x3; m_1x4 = rhs.m_1x4;
	m_2x1 = rhs.m_2x1; m_2x2 = rhs.m_2x2; m_2x3 = rhs.m_2x3; m_2x4 = rhs.m_2x4;
	m_3x1 = rhs.m_3x1; m_3x2 = rhs.m_3x2; m_3x3 = rhs.m_3x3; m_3x4 = rhs.m_3x4;
	m_4x1 = rhs.m_4x1; m_4x2 = rhs.m_4x2; m_4x3 = rhs.m_4x3; m_4x4 = rhs.m_4x4;

	return *this;
}

//Multiplication operator
Matrix4 Matrix4::operator*(const Matrix4& rhs)
{
	return Matrix4(Dot(rhs, *this, 0, 0), Dot(rhs, *this, 0, 1), Dot(rhs, *this, 0, 2), Dot(rhs, *this, 0, 3),
				   Dot(rhs, *this, 1, 0), Dot(rhs, *this, 1, 1), Dot(rhs, *this, 1, 2), Dot(rhs, *this, 1, 3),
				   Dot(rhs, *this, 2, 0), Dot(rhs, *this, 2, 1), Dot(rhs, *this, 2, 2), Dot(rhs, *this, 2, 3),
				   Dot(rhs, *this, 3, 0), Dot(rhs, *this, 3, 1), Dot(rhs, *this, 3, 2), Dot(rhs, *this, 3, 3));
}

//Float multiplication operator
Matrix4 Matrix4::operator*(const float rhs)
{
	return Matrix4(m_1x1 * rhs, m_1x2 * rhs, m_1x3 * rhs, m_1x4 * rhs,
				   m_2x1 * rhs, m_2x2 * rhs, m_2x3 * rhs, m_2x4 * rhs,
				   m_3x1 * rhs, m_3x2 * rhs, m_3x3 * rhs, m_3x4 * rhs,
				   m_4x1 * rhs, m_4x2 * rhs, m_4x3 * rhs, m_4x4 * rhs);
}

//Compound multiplication operator
Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	return *this = *this * rhs;
}

//Float compound multiplication operator
Matrix4& Matrix4::operator*=(const float rhs)
{
	return *this = *this * rhs;
}

//Vector4 multiplication operator
Vector4 Matrix4::operator*(const Vector4& rhs)
{
	return Vector4(m_1x1 * rhs.x + m_2x1 * rhs.y + m_3x1 * rhs.z + m_4x1 * rhs.w,
				   m_1x2 * rhs.x + m_2x2 * rhs.y + m_3x2 * rhs.z + m_4x2 * rhs.w,
				   m_1x3 * rhs.x + m_2x3 * rhs.y + m_3x3 * rhs.z + m_4x3 * rhs.w,
				   m_1x4 * rhs.x + m_2x4 * rhs.y + m_3x4 * rhs.z + m_4x4 * rhs.w);
}

//Float operator
void Matrix4::operator()(float a_1x1, float a_1x2, float a_1x3, float a_1x4,
						 float a_2x1, float a_2x2, float a_2x3, float a_2x4,
						 float a_3x1, float a_3x2, float a_3x3, float a_3x4,
						 float a_4x1, float a_4x2, float a_4x3, float a_4x4)
{
	m_1x1 = a_1x1; m_1x2 = a_1x2; m_1x3 = a_1x3; m_1x4 = a_1x4;
	m_2x1 = a_2x1; m_2x2 = a_2x2; m_2x3 = a_2x3; m_2x4 = a_2x4;
	m_3x1 = a_3x1; m_3x2 = a_3x2; m_3x3 = a_3x3; m_3x4 = a_3x4;
	m_4x1 = a_4x1; m_4x2 = a_4x2; m_4x3 = a_4x3; m_4x4 = a_4x4;
}

//Matrix4 operator
void Matrix4::operator()(const Matrix4& rhs)
{
	*this = rhs;
}

//Float pointer conversion operator
Matrix4::operator float*()
{
	return &m_fMatrix[0];
}

//Array operator
Vector4& Matrix4::operator[](int idx)
{
	return m_vMatrix[idx];
}

//Const array operator
const Vector4& Matrix4::operator[](int idx) const
{
	return m_vMatrix[idx];
}
