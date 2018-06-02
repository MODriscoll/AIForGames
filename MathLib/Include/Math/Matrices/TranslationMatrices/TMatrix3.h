#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Matrix3;

class TMatrix3
{
public:

	// ----- FACTORY FUNCTIONS ----- \\

	// Constructs and translates all axes
	static Matrix3 Construct_Translate(float a_Value);
	static Matrix3 Construct_Translate(float a_X, float a_Y);

	// Constructs and translates one axis
	static Matrix3 Construct_Translate_X(float a_X);
	static Matrix3 Construct_Translate_Y(float a_Y);


	// ----- STATIC FUNCTIONS ----- \\

};

