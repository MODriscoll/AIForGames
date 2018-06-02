#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Matrix4;

class SMatrix4
{
public:

	// ----- FACTORY FUNCTIONS ----- \\

	// Constructs and scales all axes
	static Matrix4 Construct_Scale(float a_Scale);
	static Matrix4 Construct_Scale(float a_X, float a_Y, float a_Z);

	// Constructs and scales one axis
	static Matrix4 Construct_Scale_X(float a_X);
	static Matrix4 Construct_Scale_Y(float a_Y);
	static Matrix4 Construct_Scale_Z(float a_Z);

	// Constructs and scales two axes
	static Matrix4 Construct_Scale_XY(float a_X, float a_Y);
	static Matrix4 Construct_Scale_XZ(float a_X, float a_Z);
	static Matrix4 Construct_Scale_YZ(float a_Y, float a_Z);


	// ----- STATIC FUNCTIONS ----- \\


};