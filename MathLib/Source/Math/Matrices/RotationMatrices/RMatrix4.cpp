#include "Math\Matrices\RotationMatrices\RMatrix4.h"

#include "Math\Maths.h"
#include "Math\Matrices\Matrix4.h"

// Consistent angle constructor
Matrix4 RMatrix4::Construct_Rotate(float a_Rad)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the rotated axes values to be used to rotate the matrix
	float rcos = cosf(a_Rad);
	float rsin = sinf(a_Rad);

	float rcrs = rcos * rsin;
	float rsrs = rsin * rsin;

	// Perform the efficient rotation of all axes
	rmat[0][0] = rcos * rcos;
	rmat[0][1] = -rcos * rsin;
	rmat[0][2] = rsin;

	rmat[1][0] = rsrs * rcos + rcos * rsin;
	rmat[1][1] = -rsrs * rsin + rcos * rcos;
	rmat[1][2] = -rsin * rcos;

	rmat[2][0] = -rcrs * rcos + rsin * rsin;
	rmat[2][1] = rcrs * rsin + rsin * rcos;
	rmat[2][2] = rcos * rcos;

	// Return the rotated matrix
	return rmat;
}

// Floats representing axes constructor
Matrix4 RMatrix4::Construct_Rotate(float a_X, float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the rotated axes values to be used to rotate the matrix
	float xcos = cosf(a_X);
	float xsin = sinf(a_X);
	float ycos = cosf(a_Y);
	float ysin = sinf(a_Y);
	float zcos = cosf(a_Z);
	float zsin = sinf(a_Z);

	float xcys = xcos * ysin;
	float xsys = xsin * ysin;

	// Perform the efficient rotation of all axes
	rmat[0][0] = ycos * zcos;
	rmat[0][1] = -ycos * zsin;
	rmat[0][2] = ysin;

	rmat[1][0] = xsys * zcos + xcos * zsin;
	rmat[1][1] = -xsys * zsin + xcos * zcos;
	rmat[1][2] = -xsin * ycos;

	rmat[2][0] = -xcys * zcos + xsin * zsin;
	rmat[2][1] = xcys * zsin + xsin * zcos;
	rmat[2][2] = xcos * ycos;

	// Return the rotated matrix
	return rmat;
}

// X only rotation constructor
Matrix4 RMatrix4::Construct_Rotate_X(float a_X)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Rotate its X axis
	rmat.RotateX(a_X);

	// Return the rotated matrix
	return rmat;
}

// Y only rotation constructor
Matrix4 RMatrix4::Construct_Rotate_Y(float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Rotate its Y axis
	rmat.RotateY(a_Y);

	// Return the rotated matrix
	return rmat;
}

// Z only rotation constructor
Matrix4 RMatrix4::Construct_Rotate_Z(float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Rotate its Z axis
	rmat.RotateZ(a_Z);

	// Return the rotated matrix
	return rmat;
}

// X and Y rotation constructor
Matrix4 RMatrix4::Construct_Rotate_XY(float a_X, float a_Y)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the rotated axes values to be used to rotate the matrix
	float xcos = cosf(a_X);
	float xsin = sinf(a_X);
	float ycos = cosf(a_Y);
	float ysin = sinf(a_Y);

	float xcys = xcos * ysin;
	float xsys = xsin * ysin;

	// Perform the efficient rotation of the two axes
	rmat[0][0] = ycos;
	rmat[0][1] = -ycos;
	rmat[0][2] = ysin;

	rmat[1][0] = xsys + xcos;
	rmat[1][1] = -xsys + xcos;
	rmat[1][2] = -xsin * ycos;

	rmat[2][0] = -xcys + xsin;
	rmat[2][1] = xcys + xsin;
	rmat[2][2] = xcos * ycos;

	// Return the rotated matrix
	return rmat;
}

// X and Z rotation constructor
Matrix4 RMatrix4::Construct_Rotate_XZ(float a_X, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the rotated axes values to be used to rotate the matrix
	float xcos = cosf(a_X);
	float xsin = sinf(a_X);
	float zcos = cosf(a_Z);
	float zsin = sinf(a_Z);

	// Perform the efficient rotation of the two axes
	rmat[0][0] = zcos;
	rmat[0][1] = zsin;

	rmat[1][0] = xsin * zcos + xcos * zsin;
	rmat[1][1] = -xsin * zsin + xcos * zcos;
	rmat[1][2] = -xsin;

	rmat[2][0] = -xcos * zcos + xsin * zsin;
	rmat[2][1] = xcos * zsin + xsin * zcos;
	rmat[2][2] = xcos;

	// Return the rotated matrix
	return rmat;
}

// Y and Z rotation constructor
Matrix4 RMatrix4::Construct_Rotate_YZ(float a_Y, float a_Z)
{
	// Construct a default matrix
	Matrix4 rmat;

	// Set the rotated axes values to be used to rotate the matrix
	float ycos = cosf(a_Y);
	float ysin = sinf(a_Y);
	float zcos = cosf(a_Z);
	float zsin = sinf(a_Z);

	// Perform the efficient rotation of the two axes
	rmat[0][0] = ycos * zcos;
	rmat[0][1] = -ycos * zsin;
	rmat[0][2] = ysin;

	rmat[1][0] = ysin * zcos + zsin;
	rmat[1][1] = -ysin * zsin + zcos;
	rmat[1][2] = ycos;

	rmat[2][0] = -ysin * zcos + zsin;
	rmat[2][1] = ysin * zsin + zcos;
	rmat[2][2] = ycos;

	// Return the rotated matrix
	return rmat;
}
