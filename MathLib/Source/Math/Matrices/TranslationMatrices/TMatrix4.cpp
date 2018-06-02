#include "Math\Matrices\TranslationMatrices\TMatrix4.h"

#include "Math\Matrices\Matrix4.h"

// Consistent translate constructor
Matrix4 TMatrix4::Construct_Translate(float a_Value)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the value to the requested position
	rmat[3][0] = a_Value;
	rmat[3][1] = a_Value;
	rmat[3][2] = a_Value;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Floats representing axes constructor
Matrix4 TMatrix4::Construct_Translate(float a_X, float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the value to the requested position
	rmat[3][0] = a_X;
	rmat[3][1] = a_Y;
	rmat[3][2] = a_Z;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Only translate X axis constructor
Matrix4 TMatrix4::Construct_Translate_X(float a_X)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set only the X value to the requested position
	rmat[3][0] = a_X;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Only translate Y axis constructor
Matrix4 TMatrix4::Construct_Translate_Y(float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set only the Y value to the requested position
	rmat[3][1] = a_Y;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Only translate Z axis constructor
Matrix4 TMatrix4::Construct_Translate_Z(float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set only the Z value to the requested position
	rmat[3][2] = a_Z;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Translate X and Y axes constructor
Matrix4 TMatrix4::Construct_Translate_XY(float a_X, float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the X and Y values to the requested position
	rmat[3][0] = a_X;
	rmat[3][1] = a_Y;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Translate X and Z axes constructor
Matrix4 TMatrix4::Construct_Translate_XZ(float a_X, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the X and Z values to the requested position
	rmat[3][0] = a_X;
	rmat[3][2] = a_Z;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Translate Y and Z axes constructor
Matrix4 TMatrix4::Construct_Translate_YZ(float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the Y and Z values to the requested position
	rmat[3][1] = a_Y;
	rmat[3][2] = a_Z;
	rmat[3][3] = 1.f;

	// Return the translated matrix
	return rmat;
}
