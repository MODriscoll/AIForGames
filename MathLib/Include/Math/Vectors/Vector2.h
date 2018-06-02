#pragma once

#ifndef Michaels_Vector2
#define Michaels_Vector2

// ----- FORWARD DECLERATIONS ----- \\

class Vector3;
class Vector4;

class Vector2
{
public:

	// ----- VARIABLES ----- \\

	float x, y;


	// ----- INITIALISER ----- \\

	Vector2(float a_X = 0.f, float a_Y = 0.f);
	Vector2(const Vector2& a_Copy) = default;
	Vector2(Vector2&& a_Move) = default;

	~Vector2() = default;


	// ----- CALCULATIONS ----- \\

	float	Magnitude() const;							// Get the magnitude of this vector
	float	Radians() const;							// Get the direction of this vector in radians
	float	Squared() const;							// Get the distance squared of this vector

	void	Negate();									// Negate this vector
	void	Normalise();								// Normalise this vector
	void	Perpendicular();							// Convert this vector into a perpendicular of itself
	void	Positivize();								// Converts each axis to positive values

	Vector2 Projection(const Vector2& rhs) const;		// Get the projection vector of this vector onto another
	float ScalarProjection(const Vector2& rhs) const;	// Get the scalar projection of this vector onto another

	// ----- FUNCTIONS ----- \\

	Vector2 GetNegate() const;										// Gets a negated version of this vector
	Vector2 GetNormalise() const;									// Gets a normalised version of this vector
	Vector2 GetPerpendicular() const;								// Generates a vector perpendicular to this vector
	Vector2 GetPositivize() const;									// Gets a positivized version of this vector

	void	Clamp(const Vector2& a_min, const Vector2& a_max);		// Clamps this vector between two given vectors					
	void	Set(float a_X, float a_Y);								// Set this vector to the given values
	void	Truncate(float a_magnitude);							// Truncates this vector between 0 and given magnitude


	// ----- STATIC FUNCTIONS ----- \\

	static Vector2	Bezier(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, float time);
	static Vector2	Bezier(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, const Vector2& a_p4, float time);
	static Vector2	Cardinal(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_p3, float alpha, float time);
	static float	CrossZ(const Vector2& a_v1, const Vector2& a_v2);
	static Vector2	Direction(float rad);
	static Vector2	Displacement(const Vector2& a_v1, const Vector2& a_v2);	
	static float	Distance(const Vector2& a_p1, const Vector2& a_p2);
	static float	Dot(const Vector2& a_v1, const Vector2& a_v2);
	static Vector2	Hermite(const Vector2& a_p1, const Vector2& a_p2, const Vector2& a_t1, const Vector2& a_t2, float time);
	static Vector2	Lerp(const Vector2& a_start, const Vector2& a_end, float time);
	static Vector2	RLerp(const Vector2* const a_points, size_t a_size, float time);
	static Vector2  TripleProduct(const Vector2& a_v1, const Vector2& a_v2, const Vector2& a_v3);


	// ----- OPERATORS ----- \\

	bool operator == (const Vector2& rhs) const;
	bool operator != (const Vector2& rhs) const;

	Vector2& operator = (const Vector2& rhs) = default;
	Vector2& operator = (Vector2&& rhs) = default;

	Vector2 operator + (const Vector2& rhs) const;
	Vector2 operator - (const Vector2& rhs) const;

	Vector2 operator + () const;
	Vector2 operator - () const;

	Vector2 operator * (const Vector2& rhs) const;
	Vector2 operator * (const float rhs) const;
	Vector2 operator / (const Vector2& rhs) const;
	Vector2 operator / (const float rhs) const;
	Vector2 operator % (const Vector2& rhs) const;
	Vector2 operator % (const float rhs) const;

	Vector2& operator += (const Vector2& rhs);
	Vector2& operator -= (const Vector2& rhs);

	Vector2& operator *= (const Vector2& rhs);
	Vector2& operator *= (const float rhs);
	Vector2& operator /= (const Vector2& rhs);
	Vector2& operator /= (const float rhs);
	Vector2& operator %= (const Vector2& rhs);
	Vector2& operator %= (const float rhs);

	Vector2& operator ++ ();
	Vector2& operator -- ();
	Vector2 operator ++ (int);
	Vector2 operator -- (int);

	void operator() (float a_X, float a_Y);
	void operator() (const Vector2& rhs);

	explicit operator float*();

	operator Vector3();
	operator Vector4();

	float& operator[] (int idx);
	const float& operator[] (int idx) const;
};

//Left-hand float multiplication operator
static Vector2 operator*(const float lhs, const Vector2& rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

//Left-hand float division operator
static Vector2 operator/(const float lhs, const Vector2& rhs)
{
	return Vector2(lhs / rhs.x, lhs / rhs.y);
}

#endif // Michaels_Vector2