#include "Math\Matrices\TranslationMatrices\TMatrix3.h"

#include "Math\Matrices\Matrix3.h"

// Consistent translate constructor
Matrix3 TMatrix3::Construct_Translate(float a_Value)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the value to the requested position
	rmat[2][0] = a_Value;
	rmat[2][1] = a_Value;
	rmat[2][2] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Floats representing axes constructor
Matrix3 TMatrix3::Construct_Translate(float a_X, float a_Y)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the value to the requested position
	rmat[2][0] = a_X;
	rmat[2][1] = a_Y;
	rmat[2][2] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Only translate X axis constructor
Matrix3 TMatrix3::Construct_Translate_X(float a_X)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set only the X value to the requested position
	rmat[2][0] = a_X;
	rmat[2][2] = 1.f;

	// Return the translated matrix
	return rmat;
}

// Only translate Y axis constructor
Matrix3 TMatrix3::Construct_Translate_Y(float a_Y)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set only the Y value to the requested position
	rmat[2][1] = a_Y;
	rmat[2][2] = 1.f;

	// Return the translated matrix
	return rmat;
}