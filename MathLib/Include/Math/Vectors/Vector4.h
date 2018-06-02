#pragma once

// ----- FORWARD DECLERATIONS ----- \\

class Vector2;
class Vector3;

class Vector4
{
public:

	// ----- VARIABLES ----- \\

	float x, y, z, w;


	// ----- INITIALISER ----- \\

	Vector4(float a_X = 0.f, float a_Y = 0.f, float a_Z = 0.f, float a_W = 0.f);
	Vector4(const Vector4& a_Copy);

	~Vector4() = default;


	// ----- CALCULATIONS ----- \\

	float	Magnitude() const;			//Get the magnitude of this vector

	void	Normalise();				//Normalise this vector

	// ----- FUNCTIONS ----- \\

	Vector4 GetNormalise() const;								//Gets a normalised version of this vector

	void	Set(float a_X, float a_Y, float a_Z, float a_W);	//Set this vector to the given values


	// ----- STATIC FUNCTIONS ----- \\

	static Vector4	Cross(const Vector4& a_v1, const Vector4& a_v2);
	static float	Dot(const Vector4& a_v1, const Vector4& a_v2);


	// ----- OPERATORS ----- \\

	bool operator == (const Vector4& rhs) const;
	bool operator != (const Vector4& rhs) const;

	Vector4& operator = (const Vector4& rhs);

	Vector4 operator + (const Vector4& rhs);
	Vector4 operator - (const Vector4& rhs);

	Vector4 operator * (const Vector4& rhs);
	Vector4 operator * (const float rhs);
	Vector4 operator / (const Vector4& rhs);
	Vector4 operator / (const float rhs);

	Vector4& operator += (const Vector4& rhs);
	Vector4& operator -= (const Vector4& rhs);

	Vector4& operator *= (const Vector4& rhs);
	Vector4& operator *= (const float rhs);
	Vector4& operator /= (const Vector4& rhs);
	Vector4& operator /= (const float rhs);

	Vector4& operator ++ ();
	Vector4& operator -- ();
	Vector4 operator ++ (int);
	Vector4 operator -- (int);

	void operator() (float a_X, float a_Y, float a_Z, float a_W);
	void operator() (const Vector4& rhs);

	// Cast to float* has to
	// explicitly called
	explicit operator float*();

	// Cast to other vectors
	// will be implicitly called
	operator Vector2();
	operator Vector3();

	float& operator[] (int idx);
	const float& operator[] (int idx) const;
};

//Left-hand float multiplication operator
static Vector4 operator*(const float lhs, const Vector4& rhs)
{
	return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}

//Left-hand float division operator
static Vector4 operator/(const float lhs, const Vector4& rhs)
{
	return Vector4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
}
