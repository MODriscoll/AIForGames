#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Matrix4;

class TMatrix4
{
public:

	// ----- FACTORY FUNCTIONS ----- \\

	// Constructs and translates all axes
	static Matrix4 Construct_Translate(float a_Value);
	static Matrix4 Construct_Translate(float a_X, float a_Y, float a_Z);

	// Constructs and translates one axis
	static Matrix4 Construct_Translate_X(float a_X);
	static Matrix4 Construct_Translate_Y(float a_Y);
	static Matrix4 Construct_Translate_Z(float a_Z);

	// Constructs and translates two axes
	static Matrix4 Construct_Translate_XY(float a_X, float a_Y);
	static Matrix4 Construct_Translate_XZ(float a_X, float a_Z);
	static Matrix4 Construct_Translate_YZ(float a_Y, float a_Z);


	// ----- STATIC FUNCTIONS ----- \\

};
