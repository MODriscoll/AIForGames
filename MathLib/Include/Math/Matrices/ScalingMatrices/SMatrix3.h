#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Matrix3;

class SMatrix3
{
public:

	// ----- FACTORY FUNCTIONS ----- \\

	// Constructs and scales all axes
	static Matrix3 Construct_Scale(float a_Scale);
	static Matrix3 Construct_Scale(float a_X, float a_Y);

	// Constructs and scales one axis
	static Matrix3 Construct_Scale_X(float a_X);
	static Matrix3 Construct_Scale_Y(float a_Y);


	// ----- STATIC FUNCTIONS ----- \\


};
