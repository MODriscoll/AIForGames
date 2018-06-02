#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Vector2;
class Vector4;

class Vector3
{
public:

	// ----- VARIABLES ----- \\

	float x, y, z;


	// ----- INITIALISER ----- \\

	Vector3(float a_X = 0.f, float a_Y = 0.f, float a_Z = 0.f);
	Vector3(const Vector3& a_Copy);

	~Vector3() = default;


	// ----- CALCULATIONS ----- \\

	float	Magnitude() const;			//Get the magnitude of this vector

	void	Normalise();				//Normalise this vector

	// ----- FUNCTIONS ----- \\

	Vector3 GetNormalise() const;						//Gets a normalised version of this vector

	void	Set(float a_X, float a_Y, float a_Z);		//Set this vector to the given values


	// ----- STATIC FUNCTIONS ----- \\

	static Vector3	Cross(const Vector3& a_v1, const Vector3& a_v2);
	static Vector3	Displacement(const Vector3& a_v1, const Vector3& a_v2);
	static float	Dot(const Vector3& a_v1, const Vector3& a_v2);
	static Vector3	Lerp(const Vector3& a_start, const Vector3& a_end, float time);


	// ----- OPERATORS ----- \\

	bool operator == (const Vector3& rhs) const;
	bool operator != (const Vector3& rhs) const;

	Vector3& operator = (const Vector3& rhs);

	Vector3 operator + (const Vector3& rhs);
	Vector3 operator - (const Vector3& rhs);

	Vector3 operator * (const Vector3& rhs);
	Vector3 operator * (const float rhs);
	Vector3 operator / (const Vector3& rhs);
	Vector3 operator / (const float rhs);

	Vector3& operator += (const Vector3& rhs);
	Vector3& operator -= (const Vector3& rhs);

	Vector3& operator *= (const Vector3& rhs);
	Vector3& operator *= (const float rhs);
	Vector3& operator /= (const Vector3& rhs);
	Vector3& operator /= (const float rhs);

	Vector3& operator ++ ();
	Vector3& operator -- ();
	Vector3 operator ++ (int);
	Vector3 operator -- (int);

	void operator() (float a_X, float a_Y, float a_Z);
	void operator() (const Vector3& rhs);

	// Cast to float* has to
	// explicitly called
	explicit operator float*();

	// Cast to other vectors
	// will be implicitly called
	operator Vector2();
	operator Vector4();

	float& operator[] (int idx);
	const float& operator[] (int idx) const;
};

//Left-hand float multiplication operator
static Vector3 operator*(const float lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

//Left-hand float division operator
static Vector3 operator/(const float lhs, const Vector3& rhs)
{
	return Vector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
}