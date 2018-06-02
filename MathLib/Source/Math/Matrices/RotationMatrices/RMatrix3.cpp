#include "Math\Matrices\RotationMatrices\RMatrix3.h"

#include "Math\Maths.h"
#include "Math\Matrices\Matrix3.h"

// Consistent angle constructor
Matrix3 RMatrix3::Construct_Rotate(float a_Rad)
{
	// Construct a default matrix
	Matrix3 rmat;

	// Rotate the matrix using the giving radians
	rmat.RotateZ(a_Rad);

	// Return the rotated matrix
	return rmat;
}