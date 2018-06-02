#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Matrix4;

class RMatrix4
{
public:

	// ----- FACTORY FUNCTIONS ----- \\

	// Constructs and rotates all axes
	static Matrix4 Construct_Rotate(float a_Rad);
	static Matrix4 Construct_Rotate(float a_X, float a_Y, float a_Z);

	// Constructs and rotates one axis
	static Matrix4 Construct_Rotate_X(float a_X);
	static Matrix4 Construct_Rotate_Y(float a_Y);
	static Matrix4 Construct_Rotate_Z(float a_Z);

	// Constructs and rotates two axes
	static Matrix4 Construct_Rotate_XY(float a_X, float a_Y);
	static Matrix4 Construct_Rotate_XZ(float a_X, float a_Z);
	static Matrix4 Construct_Rotate_YZ(float a_Y, float a_Z);


	// ----- STATIC FUNCTIONS ----- \\

};