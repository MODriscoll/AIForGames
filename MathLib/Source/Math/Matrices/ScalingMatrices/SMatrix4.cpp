#include "Math\Matrices\ScalingMatrices\SMatrix4.h"

#include "Math\Matrices\Matrix4.h"

// Consistent scaler constructor
Matrix4 SMatrix4::Construct_Scale(float a_Scale)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the scales to the requested size
	rmat[0][0] = a_Scale;
	rmat[1][1] = a_Scale;
	rmat[2][2] = a_Scale;

	// Return the scaled matrix
	return rmat;
}

// Floats representing scales constructor
Matrix4 SMatrix4::Construct_Scale(float a_X, float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the scales to the requested size
	rmat[0][0] = a_X;
	rmat[1][1] = a_Y;
	rmat[2][2] = a_Z;

	// Return the scaled matrix
	return rmat;
}

// Only scale the X axis
Matrix4 SMatrix4::Construct_Scale_X(float a_X)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the X scale to the requested size
	rmat[0][0] = a_X;

	// Return the scaled matrix
	return rmat;
}

// Only scale the Y axis
Matrix4 SMatrix4::Construct_Scale_Y(float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the Y scale to the requested size
	rmat[1][1] = a_Y;

	// Return the scaled matrix
	return rmat;
}

// Only scale the Z axis
Matrix4 SMatrix4::Construct_Scale_Z(float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the Z scale to the requested size
	rmat[2][2] = a_Z;

	// Return the scaled matrix
	return rmat;
}

// Only scale the X and Y axes
Matrix4 SMatrix4::Construct_Scale_XY(float a_X, float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the X and Y scales to the requested size
	rmat[0][0] = a_X;
	rmat[1][1] = a_Y;

	// Return the scaled matrix
	return rmat;
}

// Only scale the X and Z axes
Matrix4 SMatrix4::Construct_Scale_XZ(float a_X, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the X and Z scales to the requested size
	rmat[0][0] = a_X;
	rmat[2][2] = a_Z;

	// Return the scaled matrix
	return rmat;
}

// Only scale the Y and Z axes
Matrix4 SMatrix4::Construct_Scale_YZ(float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the Y and Z scales to the requested size
	rmat[1][1] = a_Y;
	rmat[2][2] = a_Z;

	// Return the scaled matrix
	return rmat;
}
