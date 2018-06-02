#include "Math\Matrices\ScalingMatrices\SMatrix3.h"

#include "Math\Matrices\Matrix3.h"

// Consistent scaler constructor
Matrix3 SMatrix3::Construct_Scale(float a_Scale)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the scales to the requested size
	rmat[0][0] = a_Scale;
	rmat[1][1] = a_Scale;

	// Return the scaled matrix
	return rmat;
}

// Floats representing scales constructor
Matrix3 SMatrix3::Construct_Scale(float a_X, float a_Y)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the scales to the requested size
	rmat[0][0] = a_X;
	rmat[1][1] = a_Y;

	// Return the scaled matrix
	return rmat;
}

// Only scale the X axis
Matrix3 SMatrix3::Construct_Scale_X(float a_X)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the X scale to the requested size
	rmat[0][0] = a_X;

	// Return the scaled matrix
	return rmat;
}

// Only scale the Y axis
Matrix3 SMatrix3::Construct_Scale_Y(float a_Y)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Set the Y scale to the requested size
	rmat[1][1] = a_Y;

	// Return the scaled matrix
	return rmat;
}